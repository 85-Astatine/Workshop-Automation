#include <WiFi.h>
#include <Espalexa.h>
Espalexa espalexa;


// define the GPIO connected with Relays and switches

#define wifiLed    2   //D2

// WiFi Credentials
const char* ssid = "Amit";
const char* password = "amit@123";

// device names
String Device_1_Name = "Fan";
String Device_2_Name = "Tube Light";
String Device_3_Name = "Room Light";//Bulb near ceiling
String Device_4_Name = "Focus Light";//60 watt light
String Device_5_Name = "Study light";
String Device_6_Name = "Extension";
String Device_7_Name = "Plug Point";
String Device_8_Name = "Music System";
String Device_9_Name = "Bluetooth Music System";
String Color_Device_1_Name = "Ambient Lights";
// prototypes
boolean connectWifi();
int r,g,b;
//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void fourthLightChanged(uint8_t brightness);
void fifthLightChanged(uint8_t brightness);
void sixthLightChanged(uint8_t brightness);
void senventhLightChanged(uint8_t brightness);
void eighthLightChanged(uint8_t brightness);
void ninthLightChanged(uint8_t brightness);
void colorLightChanged(uint8_t brightness, uint32_t rgb);




boolean wifiConnected = false;

//our callback functions
void firstLightChanged(uint8_t brightness){
  //Control the device
  if (brightness == 255)
  {

    Serial.println("Device1 ON");
  }
  else
  {

    Serial.println("Device1 OFF");
  }
}
void secondLightChanged(uint8_t brightness){
  //Control the device
  if (brightness == 255)
  {

    Serial.println("Device2 ON");
  }
  else
  {

    Serial.println("Device2 OFF");
  }
}
void thirdLightChanged(uint8_t brightness){
  //Control the device
  if (brightness == 255)
  {

    Serial.println("Device3 ON");
  }
  else
  {

    Serial.println("Device3 OFF");
  }
}
void fourthLightChanged(uint8_t brightness){
  //Control the device
  if (brightness == 255)
  {

    Serial.println("Device4 ON");
  }
  else
  {

    Serial.println("Device4 OFF");
  }
}
void fifthLightChanged(uint8_t brightness){
  //Control the device
  if (brightness == 255)
  {

    Serial.println("Device5 ON");
  }
  else
  {

    Serial.println("Device1 OFF");
  }
}
void sixthLightChanged(uint8_t brightness){
  //Control the device
  if (brightness == 255)
  {

    Serial.println("Device6 ON");
  }
  else
  {

    Serial.println("Device6 OFF");
  }
}
void seventhLightChanged(uint8_t brightness){
  //Control the device
  if (brightness == 255)
  {

    Serial.println("Device7 ON");
  }
  else
  {

    Serial.println("Device7 OFF");
  }
}
void eighthLightChanged(uint8_t brightness){
  //Control the device
  if (brightness == 255)
  {
    Serial.println("Device8 ON");
  }
  else
  {
    Serial.println("Device8 OFF");
  }
}
void ninthLightChanged(uint8_t brightness){
  //Control the device
  if (brightness == 255)
  {
    Serial.println("Device8 ON");
  }
  else
  {
    Serial.println("Device8 OFF");
  }
}
void colorLightChanged(uint8_t brightness, uint32_t rgb) {
  //do what you need to do here, for example control RGB LED strip
  Serial.print("Brightness: ");
  Serial.print(brightness);
  Serial.print(", Red: ");
  Serial.print((rgb >> 16) & 0xFF); //get red component
  Serial.print(", Green: ");
  Serial.print((rgb >>  8) & 0xFF); //get green
  Serial.print(", Blue: ");
  Serial.println(rgb & 0xFF); //get blue
float hell = brightness / 255.0;
r=((rgb >> 16) & 0xFF)*hell;
g=((rgb >>  8) & 0xFF)*hell;
b=(rgb & 0xFF)*hell;

}

// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}

void addDevices() {
  // Define your devices here.
  espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off
  espalexa.addDevice(Device_2_Name, secondLightChanged);
  espalexa.addDevice(Device_3_Name, thirdLightChanged);
  espalexa.addDevice(Device_4_Name, fourthLightChanged);
  espalexa.addDevice(Device_5_Name, fifthLightChanged);
  espalexa.addDevice(Device_6_Name, sixthLightChanged);
  espalexa.addDevice(Device_7_Name, seventhLightChanged);
  espalexa.addDevice(Device_8_Name, eighthLightChanged);
  espalexa.addDevice(Device_9_Name, ninthLightChanged);
  espalexa.addDevice(Color_Device_1_Name, colorLightChanged);
  espalexa.begin();
}

void setup()
{
  Serial.begin(115200);


  pinMode(wifiLed, OUTPUT);



  //During Starting all Relays should TURN OFF
wifiConnected = connectWifi();
  if (wifiConnected)
  {
    addDevices();
  }




  // Initialise wifi connection
  
  else
  {
    Serial.println("Cannot connect to WiFi. So in Manual Mode");
    delay(1000);
  }
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    //Serial.print("WiFi Not Connected ");
    digitalWrite(wifiLed, LOW); //Turn off WiFi LED
  }
  else
  {
    //Serial.print("WiFi Connected  ");
    digitalWrite(wifiLed, HIGH);
    //Manual Switch Control
    //WiFi Control
    if (wifiConnected) {
      espalexa.loop();
      delay(1);
    }
    else {
      wifiConnected = connectWifi(); // Initialise wifi connection
      if (wifiConnected) {
        addDevices();
      }
    }
  }
}
