#define DISP_PIN 6
#define NEXT_PIN 8
#define BUZZER_PIN 7
#define G0 10
#define R0 11
#define G1 12
#define R1 13
#define G2 4
#define R2 5
#define G3 2
#define R3 3
#define WHITE_LED A4
#define SLOTS 4
#define MAX_ITEMS 8
typedef struct { uint16_t batch; char name[14]; uint32_t expiry; int8_t slot; uint8_t active; } Item;
static Item items[MAX_ITEMS];
static int8_t slotItem[SLOTS];
static int8_t heapArr[MAX_ITEMS];
static int8_t heapPos[MAX_ITEMS];
static uint8_t heapN = 0;
static uint8_t itemCount = 0;
static int8_t cdll_next[SLOTS];
static int8_t cdll_prev[SLOTS];
static uint8_t cdll_in[SLOTS];
static int8_t cdll_head = -1;
static char inBuf[96];
static uint8_t inPos = 0;
static inline uint32_t toTS(const char *s){
  uint16_t y = (s[0]-'0')*1000 + (s[1]-'0')*100 + (s[2]-'0')*10 + (s[3]-'0');
  uint8_t mo = (s[5]-'0')*10 + (s[6]-'0');
  uint8_t d  = (s[8]-'0')*10 + (s[9]-'0');
  return 1600000000UL + (uint32_t)(y - 2000) * 365UL * 86400UL + (uint32_t)(mo - 1) * 31UL * 86400UL + (uint32_t)(d - 1) * 86400UL;
}
static inline uint32_t nowPseudo(void){ return (millis()/1000UL) + 1600000000UL; }
static inline uint32_t keyu(uint8_t i){ return items[i].expiry; }
/* heap */
static void hswap(uint8_t a,uint8_t b){ int8_t t=heapArr[a]; heapArr[a]=heapArr[b]; heapArr[b]=t; heapPos[heapArr[a]]=a; heapPos[heapArr[b]]=b; }
static void heapUp(uint8_t i){ while(i){ uint8_t p=(i-1)/2; if (keyu(heapArr[i])>=keyu(heapArr[p])) break; hswap(i,p); i=p; } }
static void heapDown(uint8_t i){ for(;;){ uint8_t l=2*i+1,r=2*i+2,s=i; if (l<heapN && keyu(heapArr[l])<keyu(heapArr[s])) s=l; if (r<heapN && keyu(heapArr[r])<keyu(heapArr[s])) s=r; if (s==i) break; hswap(i,s); i=s; } }
static void heapPush(int8_t idx){ heapArr[heapN]=idx; heapPos[idx]=heapN; heapUp(heapN); heapN++; }
static void heapRemove(int8_t idx){ int8_t p=heapPos[idx]; if (p<0) return; heapN--; heapArr[p]=heapArr[heapN]; heapPos[heapArr[p]]=p; heapPos[idx]=-1; heapDown(p); heapUp(p); }
/* CDLL for slots */
static void cdll_init(void){ for(int8_t i=0;i<SLOTS;i++){ cdll_in[i]=0; cdll_next[i]=cdll_prev[i]=-1; } cdll_head=-1; }
static void cdll_insert(int8_t s){ if (s<0||s>=SLOTS) return; if (cdll_in[s]) return; if (cdll_head==-1){ cdll_head=s; cdll_next[s]=s; cdll_prev[s]=s; cdll_in[s]=1; return; } int8_t t=cdll_prev[cdll_head]; cdll_next[t]=s; cdll_prev[s]=t; cdll_next[s]=cdll_head; cdll_prev[cdll_head]=s; cdll_in[s]=1; }
static void cdll_remove(int8_t s){ if (s<0||s>=SLOTS) return; if (!cdll_in[s]) return; if (cdll_next[s]==s){ cdll_in[s]=0; cdll_head=-1; cdll_next[s]=cdll_prev[s]=-1; return; } int8_t p=cdll_prev[s], n=cdll_next[s]; cdll_next[p]=n; cdll_prev[n]=p; if (cdll_head==s) cdll_head=n; cdll_in[s]=0; cdll_next[s]=cdll_prev[s]=-1; }
static int8_t cdll_find_exp(uint32_t e){ if (cdll_head==-1) return -1; int8_t cur=cdll_head; do{ int8_t mi = slotItem[cur]; if (mi>=0 && items[mi].active && items[mi].expiry==e) return cur; cur = cdll_next[cur]; } while(cur!=cdll_head); return -1; }
static int8_t cdll_advance(void){ if (cdll_head==-1) return -1; cdll_head = cdll_next[cdll_head]; return cdll_head; }
/* core */
static int8_t freeSlot(void){ for(int8_t i=0;i<SLOTS;i++) if (slotItem[i]==-1) return i; return -1; }
static void printList(void){
  Serial.println(F("---- LIST ----"));
  uint32_t now = nowPseudo();
  if (itemCount==0){ Serial.println(F("No stored items.")); return; }
  for(uint8_t i=0;i<itemCount;i++){
    Serial.print(i); Serial.print(F(": B=")); Serial.print(items[i].batch);
    Serial.print(F(" S=")); Serial.print(items[i].slot);
    Serial.print(F(" A=")); Serial.print(items[i].active);
    Serial.print(F(" D="));
    if (!items[i].active){ Serial.println(F("N/A")); continue; }
    if (items[i].expiry <= now){ Serial.println(F("EXPIRED")); continue; }
    Serial.println((items[i].expiry - now) / 86400UL);
  }
}
/* Force-alert: make current top expire soon (now + 10s) */
static void doForceAlert(void){
  if (heapN == 0) { Serial.println(F("No items to force.")); return; }
  int8_t topIdx = heapArr[0];
  items[topIdx].expiry = nowPseudo() + 10; // 10 seconds until expiry
  Serial.print(F("FORCEALERT applied to batch ")); Serial.println(items[topIdx].batch);
}
/* parse manual serial medicine input or LIST/BEEP/FORCEALERT */
static void parseLine(const char *line){
  if (!line) return;
  if (strncmp(line,"LIST",4)==0){ printList(); return; }
  if (strncmp(line,"BEEP",4)==0){ tone(BUZZER_PIN,1500,200); return; }
  if (strncmp(line,"FORCEALERT",10)==0){ doForceAlert(); return; }
  if (itemCount >= MAX_ITEMS){ Serial.println(F("Storage full")); return; }
  char t[96]; char exp[12]=""; char nm[14]=""; int batch=-1;
  strncpy(t,line,sizeof(t)-1); t[sizeof(t)-1]=0;
  char *tok = strtok(t,";");
  while(tok){
    if (!strncmp(tok,"BATCH:",6)) batch=atoi(tok+6);
    else if (!strncmp(tok,"EXP:",4)) strncpy(exp,tok+4,11);
    else if (!strncmp(tok,"NAME:",5)) strncpy(nm,tok+5,sizeof(nm)-1);
    tok=strtok(NULL,";");
  }
  if (batch<0 || strlen(exp)<10){ Serial.println(F("Invalid medicine input")); return; }
  int8_t id = itemCount++;
  items[id].batch=(uint16_t)batch;
  strncpy(items[id].name,nm,sizeof(items[id].name)-1);
  items[id].expiry=toTS(exp);
  items[id].active=1;
  items[id].slot=freeSlot();
  if (items[id].slot>=0){ slotItem[ items[id].slot ] = id; cdll_insert(items[id].slot); }
  else Serial.println(F("No free slot"));
  heapPos[id]=-1; heapPush(id);
  Serial.print(F("Added: ")); Serial.print(batch); Serial.print(F(" Slot: ")); Serial.println(items[id].slot);
}
static int8_t choose_top(void){ if (heapN==0) return -1; int8_t top=heapArr[0]; uint32_t e=items[top].expiry; int8_t s = cdll_find_exp(e); if (s>=0) return slotItem[s]; return top; }
static void updateLEDs(void){
  digitalWrite(G0,LOW); digitalWrite(R0,LOW);
  digitalWrite(G1,LOW); digitalWrite(R1,LOW);
  digitalWrite(G2,LOW); digitalWrite(R2,LOW);
  digitalWrite(G3,LOW); digitalWrite(R3,LOW);
  digitalWrite(WHITE_LED,HIGH);
  if (slotItem[0]!=-1) digitalWrite(G0,HIGH);
  if (slotItem[1]!=-1) digitalWrite(G1,HIGH);
  if (slotItem[2]!=-1) digitalWrite(G2,HIGH);
  if (slotItem[3]!=-1) digitalWrite(G3,HIGH);
  if (heapN>0){
    int8_t mi = choose_top();
    if (mi>=0){
      int8_t s = items[mi].slot;
      if (s==0) digitalWrite(R0,HIGH);
      else if (s==1) digitalWrite(R1,HIGH);
      else if (s==2) digitalWrite(R2,HIGH);
      else if (s==3) digitalWrite(R3,HIGH);
    }
  }
}
/* setup & loop */
void setup(){
  Serial.begin(115200);
  pinMode(DISP_PIN, INPUT_PULLUP);
  pinMode(NEXT_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(G0,OUTPUT); pinMode(R0,OUTPUT);
  pinMode(G1,OUTPUT); pinMode(R1,OUTPUT);
  pinMode(G2,OUTPUT); pinMode(R2,OUTPUT);
  pinMode(G3,OUTPUT); pinMode(R3,OUTPUT);
  pinMode(WHITE_LED,OUTPUT); digitalWrite(WHITE_LED,HIGH);
  for(int8_t i=0;i<SLOTS;i++) slotItem[i]=-1;
  for(int8_t i=0;i<MAX_ITEMS;i++) heapPos[i]=-1;
  cdll_init();
  Serial.println(F("SMSES 4-slot system ready. Enter medicine details or type LIST/BEEP/FORCEALERT"));
}
void loop(){
  while(Serial.available()){
    char c=(char)Serial.read();
    if (c=='\r') continue;
    if (c=='\n' || inPos >= (int)sizeof(inBuf)-2){ inBuf[inPos]=0; if (inPos>0) parseLine(inBuf); inPos=0; }
    else if (inPos < (int)sizeof(inBuf)-1) inBuf[inPos++]=c;
  }
  /* NEXT button */
  static unsigned long lastN=0;
  if (digitalRead(NEXT_PIN)==LOW){
    if (millis()-lastN>180){ lastN=millis(); int8_t h=cdll_advance(); if (h>=0){ tone(BUZZER_PIN,1200,70); Serial.print(F("NEXT->")); Serial.println(h); } }
    while(digitalRead(NEXT_PIN)==LOW) delay(5);
  }
  /* DISPENSE */
  static unsigned long lastD=0;
  if (digitalRead(DISP_PIN)==LOW){
    if (millis()-lastD>220){
      lastD=millis();
      if (heapN>0){
        int8_t mi=choose_top();
        if (mi>=0){
          int8_t s=items[mi].slot;
          if (s>=0){ slotItem[s]=-1; cdll_remove(s); }
          items[mi].active=0; items[mi].slot=-1;
          heapRemove(mi);
          tone(BUZZER_PIN,1500,110);
          Serial.print(F("Dispensed: ")); Serial.println(items[mi].batch);
        }
      } else { tone(BUZZER_PIN,800,110); Serial.println(F("No items.")); }
    }
    while(digitalRead(DISP_PIN)==LOW) delay(5);
  }
  /* near-expiry beep (demo) */
  if (heapN>0){
    int8_t t = heapArr[0];
    uint32_t e = items[t].expiry;
    uint32_t now = nowPseudo();
    if (e <= now + 24UL*3600UL) tone(BUZZER_PIN,1800,30);
  }
  updateLEDs();
}
