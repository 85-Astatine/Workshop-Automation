
//use voltage divider with esp32,not tested with it tho

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A0,INPUT);
pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(A0)){
  Serial.println("Motion Detected");
  digitalWrite(13,1);
}
else{
  digitalWrite(13,0);
}
}
