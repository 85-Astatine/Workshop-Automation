int prevval=0;
int thresh=150;
bool rain;
int spikecounter=0;
long start;
long persec;
bool sensorcheck=false;
#define ledpin1 22
#define ledpin2 23


//15 k pullup and 150 ohm for led
void setup() {
  // put your setup code here, to run once:
pinMode(4,INPUT_PULLUP);
pinMode(ledpin1,OUTPUT);
pinMode(ledpin2,OUTPUT);
Serial.begin(115200);
prevval=analogRead(4);
}

void loop() {
  // put your main code here, to run repeatedly:
/*

int x;

for(int a=0;a<100;a++){
  x+=analogRead(4);
}
x=x/100;
Serial.println(x);
*/
refreshspikepermin();
if(millis()-persec>500){
  sensorcheck=!sensorcheck;
  led(sensorcheck);
  persec=millis();
  delay(5);
}
if(sensorcheck){
  checkrain();
}

if(spikecounter>5){
  Serial.println("RAINING");
  rain=true;
}
else{
  rain=false;
}
}


void  refreshspikepermin(){
  if(millis()-start>60*1000){
    spikecounter=0;
    start=millis();
  }
}
void checkrain(){
  int val=analogRead(4);
int derivative=prevval-val;
if(derivative>thresh){
  spikecounter++;
  Serial.println(spikecounter);
}
//Serial.println(derivative);
delay(20);
prevval=val;
}
void led(bool val){
  if(val){
    digitalWrite(ledpin1,1);
    digitalWrite(ledpin2,1);
  }
  else{
    digitalWrite(ledpin1,0);
    digitalWrite(ledpin2,0);
  }
}
