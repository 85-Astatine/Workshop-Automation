#define RXD2 16
#define TXD2 17
//PIN 16 AKA RX CAN BE USED AS A NORMAL DIGITAL PIN

////https://randomnerdtutorials.com/esp-now-two-way-communication-esp32/


void setup() {
  //Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pinMode(RXD2,OUTPUT);
}

void loop() {
  Serial2.println("welcome");
  digitalWrite(RXD2,LOW);
  delay(500);
Serial2.println("welcome");
  digitalWrite(RXD2,HIGH);
  delay(500);

}
