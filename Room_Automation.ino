#include "SPI.h"
#include "TFT_eSPI.h"
#include "Free_Fonts.h" // Include the header file attached to this sketch
#include "images.h"
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);
long start;
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF//white//white//white//white//white//white
#define bgcolor BLUE
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TimeLib.h>
const char *ssid     = "Airtel_HappyHome";
const char *password = "amit@123";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", 19800, 60000);

String  second_, minute_, hour_, day_, month_, year_;
String monstr, daystr;
unsigned long unix_epoch;
int last_second, last_minute, last_hour, last_day;
bool seccolon = false, timeoffset = false, am = false;
long epoch_birth = 1103729220, epoch_myage;//1103729220
String hour_myage, minute_myage, day_myage, month_myage, year_myage;
String hour_myage_s, minute_myage_s, day_myage_s, month_myage_s, year_myage_s;
//#define TFT_BLACK       0x0000      /*   0,   0,   0 */
//#define TFT_NAVY        0x000F      /*   0,   0, 128 */
//#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
//#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
//#define TFT_MAROON      0x7800      /* 128,   0,   0 */
//#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
//#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
//#define TFT_LIGHTGREY   0xD69A      /* 211, 211, 211 */
//#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
//#define TFT_BLUE        0x001F      /*   0,   0, 255 */
//#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
//#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
//#define TFT_RED         0xF800      /* 255,   0,   0 */
//#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
//#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
//#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
//#define TFT_ORANGE      0xFDA0      /* 255, 180,   0 */
//#define TFT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
//#define TFT_PINK        0xFE19      /* 255, 192, 203 */ //Lighter pink, was 0xFC9F
//#define TFT_BROWN       0x9A60      /* 150,  75,   0 */
//#define TFT_GOLD        0xFEA0      /* 255, 215,   0 */
//#define TFT_SILVER      0xC618      /* 192, 192, 192 */
//#define TFT_SKYBLUE     0x867D      /* 135, 206, 235 */
//#define TFT_VIOLET      0x915C      /* 180,  46, 226 */
/*
  #define TFT_CS   33  // Chip select control pin (library pulls permanently low
  #define TFT_DC   18  // Data Command control pin - must use a pin in the range 0-31
  #define TFT_RST  32  // Reset pin, toggles on startup
  //#define TOUCH_CS 22
  #define TFT_WR    4  // Write strobe control pin - must use a pin in the range 0-31
  #define TFT_RD    2  // Read strobe control pin
  #define TFT_D0   12  // Must use pins in the range 0-31 for the data bus
  #define TFT_D1   13  // so a single register write sets/clears all bits.
  #define TFT_D2   26  // Pins can be randomly assigned, this does not affect
  #define TFT_D3   25  // TFT screen update performance.
  #define TFT_D4   21
  #define TFT_D5   5
  #define TFT_D6   27
  #define TFT_D7   14
*/
/////for nano yellow:lcd brightness orange:dht11 red:wb2812led brown:push button black:mini speaker
#include "DHT.h"
#define DHTPIN 19
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define tempupdatetime 5//in sec
int mintemp = 10, maxtemp = 50;
long start_temperature;
float temprature;
int humidity;


#include <Espalexa.h>
Espalexa espalexa;
String Device_1_Name = "Fan";
String Device_2_Name = "Tube Light";
String Device_3_Name = "Room Light";//Bulb near ceiling
String Device_4_Name = "Focus Light";//60 watt light
String Device_5_Name = "Study light";
String Device_6_Name = "Music light";
String Device_7_Name = "Leg fan";
String Device_8_Name = "Music System";
String Device_9_Name = "flashy light";
String Color_Device_1_Name = "Ambient Lights";
// prototypes
boolean connectWifi();
int r, g, b;
boolean wifiConnected = false;
#define wifiledred 23
#define wifiledgreen 22
long wifiledtimer;
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



#define RXD2 16///no use
#define TXD2 17
void setup() {
  // put your setup code here, to run once:
  delay(1000);
  dht.begin();
  tft.init();
  pinMode(wifiledred,OUTPUT);
    pinMode(wifiledgreen,OUTPUT);
digitalWrite(wifiledred,1);
digitalWrite(wifiledgreen,1);

  tft.setRotation(3);
  //spr.createSprite(300, 300);
  tft.fillScreen(BLACK);
  tft.fillRectHGradient(0, 0, 480, 320, TFT_SKYBLUE, TFT_SKYBLUE);
  tft.setTextSize(4);
  tft.setCursor(100, 150);
  tft.println("Connecting...");
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting.");
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  while ( WiFi.status() != WL_CONNECTED ) {
    digitalWrite(wifiledred,0);
    digitalWrite(wifiledgreen,1);
    delay(500);
    Serial.print(".");
  }
  Serial.println("Room auto connected");
  
  Serial2.println("connected");
  digitalWrite(wifiledred,1);
    digitalWrite(wifiledgreen,0);
  timeClient.begin();
  //addDevices();
  tft.fillScreen(bgcolor);

  //tft.fillRect(400, 115, 75, 90, bgcolor);
  //drawimage2(75, 90, 400, 115);
  initializealexa();

}
void loop() {
  // put your main code here, to run repeatedly:
wifiled();
  showdisplay();

  showtemp();

  //drawimage1/2
  alexacontrol();
  //serialprinttime();











  //refreshrate(0);

}




void refreshrate(long del) {
  Serial.print((micros() - start - 1000 * del));
  Serial.println("μs");
  start = micros();
  delay(del);
}
void displayheader() {
  tft.setTextSize(1);
  tft.setFreeFont(FSBI24);
  tft.setTextColor(TFT_YELLOW);
  tft.drawString("Welcome Sir", 10, 10, GFXFF);
}
void displaydatetime() { ////
  tft.setTextSize(1);
  tft.setFreeFont(FSB18);
  tft.setTextColor(TFT_YELLOW);
  String temp;
  year_.remove(0);
  year_.remove(0);
  temp = monstr + " " + day_ + " '" + year_ + ", " + daystr;
  tft.drawString(temp, 15, 70, GFXFF); //"Aug 3 2022, Mon"

  tft.setTextColor(TFT_YELLOW);
  tft.setTextFont(7);
  tft.setTextSize(3);
  if (hour_.toInt() == 0) {
    hour_ = "12";
  }
  convert12hourclock();
  if (hour_.toInt() > 9) {
    tft.setCursor(-25, 125);
  } else {
    tft.setCursor(-25 + 90, 125);
  }
  temp = "Hours:" + hour_;
  Serial.println(temp);

  if (second_.toInt() % 2 == 0) {
    seccolon = false;
  } else {
    seccolon = true;
  }
  if (seccolon) {
    temp = hour_ + ":" + minute_;
  }
  else {
    temp = hour_ + " " + minute_;
  }
  tft.print(temp);
  tft.setCursor(400, 215);
  tft.setTextSize(0);
  if (am) {
    tft.setTextColor(0xFFFF); //0xFBE0:ORANGE ,0x2FE0:GREEN
  } else {
    tft.setTextColor(0x0000);
  }
  temp = second_;
  tft.println(temp);
}
void drawimage1(int x, int y, int offx, int offy) {
  tft.fillRect(400, 115, 75, 90, RED);
  long imgtime = micros();
  long curx, cury;
  for (int cury = 1; cury <= y; cury++) {
    for (int curx = 1; curx <= x; curx++) {
      tft.drawPixel(curx + offx, cury + offy, myimage1[(cury - 1)*x + curx - 1]);
    }
  }
  Serial.println(micros() - imgtime);
}
void drawimage2(int x, int y, int offx, int offy) {
  tft.fillRect(400, 115, 75, 90, RED);
  long imgtime = micros();
  long curx, cury;
  for (int cury = 1; cury <= y; cury++) {
    for (int curx = 1; curx <= x; curx++) {
      tft.drawPixel(curx + offx, cury + offy, myimage2[(cury - 1)*x + curx - 1]);
    }
  }
  Serial.println(micros() - imgtime);
}
String convertmon() {
  switch (month_.toInt()) {
    case 1:
      return "Jan";
      break;
    case 2:
      return "Feb";
      break;
    case 3:
      return "Mar";
      break;
    case 4:
      return "Apl";
      break;
    case 5:
      return "May";
      break;
    case 6:
      return "Jun";
      break;
    case 7:
      return "Jal";
      break;
    case 8:
      return "Aug";
      break;
    case 9:
      return "Sep";
      break;
    case 10:
      return "Oct";
      break;
    case 11:
      return "Nov";
      break;
    case 12:
      return "Dec";
      break;

  }
}
String convertday() {
  switch (timeClient.getDay()) {
    case 1:
      return "Mon";
      break;
    case 2:
      return "Tue";
      break;
    case 3:
      return "Wed";
      break;
    case 4:
      return "Thu";
      break;
    case 5:
      return "Fri";
      break;
    case 6:
      return "Sat";
      break;
    case 0:
      return "Sun";
      break;
  }
}
void addzero() {
  if (second_.toInt() <= 9) {
    second_ = "0" + second_;
  }
  if (minute_.toInt() <= 9) {
    minute_ = "0" + minute_;
  }
  if (hour_.toInt() <= 9) {
    hour_ = "" + hour_;
    timeoffset = true;
  }
  else {
    timeoffset = false;
  }
  if (day_.toInt() <= 9) {
    day_ = "0" + day_;
  }
  if (month_.toInt() <= 9) {
    month_ = "0" + month_;
  }
}
void convert12hourclock() {
  if (hour_.toInt() > 12) {
    int temp = hour_.toInt() - 12;
    hour_ = String(temp);
    am = false;

  }
  else {
    am = true;
  }
}
void serialprinttime() {
  Serial.print(hour_);
  Serial.print(":");
  Serial.print(minute_);
  Serial.print(":");
  Serial.println(second_);
  Serial.print(monstr);
  Serial.print(",");
  Serial.println(daystr);
  Serial.print(day_);
  Serial.print("/");
  Serial.print(month_);
  Serial.print("/");
  Serial.println(year_);
}
void getsec() {
  timeClient.update();
  unix_epoch = timeClient.getEpochTime();
  second_ = String(second(unix_epoch));
}
void gettime() {

  minute_ = String(minute(unix_epoch));
  hour_   = String(hour(unix_epoch));
  day_    = String(day(unix_epoch));
  month_  = String(month(unix_epoch));
  year_   = String(year(unix_epoch));

  monstr = convertmon();

  daystr = convertday();
}
void cleardisplaysecond() {
  //tft.fillRect(0, 120, 400-3, 320, BLUE);
  tft.fillRect(395, 205 + 3, 90, 80, bgcolor);
  tft.fillRect(165, 160, 30, 80, bgcolor);
}
void cleardisplayminute() {
  tft.fillRect(100, 120, 300 - 3, 170, bgcolor);

}
void cleardisplayhour() {
  tft.fillRect(0, 120, 400 - 3, 170, bgcolor);
}
void cleardisplayparts() {
  cleardisplaysecond();
  if (last_day != day_.toInt()) {
    //rebuild all items
    tft.fillScreen(bgcolor);
    //drawimage2(75, 90, 400, 115);
    displayheader();
    last_day = day_.toInt();
  }
  if (last_minute != minute_.toInt()) {
    cleardisplayminute();
    timeonearth();
    last_minute = minute_.toInt();
  }
  if (last_hour != hour_.toInt()) {
    cleardisplayhour();
    last_hour = hour_.toInt();
  }
}
void showdisplay() {
  getsec();

  if (last_second != second_.toInt()) {

    gettime();

    addzero();//should be after convert mon and day

    serialprinttime();
    //tft.fillRect(400, 115, 75, 90, RED);
    cleardisplayparts();
    displaydatetime();
    //drawimage1(75,75,400,120);//x y of image then x y of position
    //drawimage2(75,90,400,115);
    last_second = second_.toInt();
  }
}


void showtemp() {

  if (millis() - start_temperature > tempupdatetime * 1000) {
    gettemp();
    if (!(isnan(humidity) || isnan(temprature))) {
      //Serial.println("good values");
      displaytemp();
    }
    start_temperature = millis();

  }

}
void gettemp() {
  humidity = dht.readHumidity();
  temprature = dht.readTemperature();
}
void displaytemp() {
  cleartemp();
  tft.setTextSize(1);
  tft.setFreeFont(FSB18);//12
  tft.setTextColor(TFT_YELLOW);
  String temp;
  String tempraturespecial = String(temprature);
  tempraturespecial.remove(4);
  temp = "Temp:";
  tft.drawString(temp, 285, 15, GFXFF);
  if (temprature > (mintemp + maxtemp) / 2) {
    tft.setTextColor(map(temprature, (mintemp + maxtemp) / 2, maxtemp, tft.color565(255, 255, 255), tft.color565(255, 0, 0)));
  }
  else {
    tft.setTextColor(map(temprature, mintemp, (mintemp + maxtemp) / 2, tft.color565(0, 0, 255), tft.color565(255, 255, 255)));
  }
  temp = tempraturespecial + "C";
  tft.drawString(temp, 385, 15, GFXFF);
  tft.setTextSize(1);
  tft.setFreeFont(FSB18);//12
  tft.setTextColor(TFT_YELLOW);
  temp = "Humid:";
  tft.drawString(temp, 285, 50, GFXFF);
  tft.setTextColor(map(humidity, 0, 100, TFT_GREEN, TFT_RED));
  if (humidity > 50) {
    tft.setTextColor(map(humidity, 50, 100, tft.color565(255, 255, 255), tft.color565(255, 0, 0)));
  }
  else if (humidity > 5) {
    tft.setTextColor(map(humidity, 0, 50, tft.color565(0, 255, 0), tft.color565(255, 255, 255)));
  }
  else {
    tft.setTextColor(TFT_RED);
  }

  temp = String(humidity) + "%";
  tft.drawString(temp, 410, 50, GFXFF);
}
void cleartemp() {
  tft.fillRoundRect(276, 1, 202, 87, 5, tft.color565(51, 50, 45)); //bgcolor
  for (int a = 0; a < 5; a++) {
    tft.drawRoundRect(276 + a, 1 + a, 203 - a, 88 - a, 5, RED);
  }
}
void timeonearth() {
  epoch_myage = unix_epoch - epoch_birth;

  minute_myage = String(minute(epoch_myage));
  hour_myage   = String(hour(epoch_myage));
  day_myage   = String(day(epoch_myage));
  month_myage  = String(month(epoch_myage));
  year_myage  = String(year(epoch_myage) - 1970);
  Serial.println(minute_myage);
  tft.fillRect(0, 290, 480, 30, WHITE);
  tft.setTextSize(1);
  tft.setFreeFont(FSB9);//12,9
  tft.setTextColor(TFT_PURPLE);
  String temp;
  adds_timeonearth();
  year_myage_s = year_myage + "Yrs";
  temp = "Time On Earth: " + year_myage_s + " " + month_myage_s + " " + day_myage_s + " " + hour_myage_s + " " + minute_myage_s;
  Serial.println(temp);
  tft.drawString(temp, 5, 295, GFXFF);
}
void adds_timeonearth() {
  if (minute_myage.toInt() == 0) {
    minute_myage_s = "";
  }
  else if (minute_myage.toInt() == 1) {
    minute_myage_s = minute_myage + "Min";
  }
  else {
    minute_myage_s = minute_myage + "Mins";
  }
  //////////
  if (hour_myage.toInt() == 0) {
    hour_myage_s = "";
  }
  else if (hour_myage.toInt() == 1) {
    hour_myage_s = hour_myage + "Hr";
  }
  else {
    hour_myage_s = hour_myage + "Hrs";
  }
  /////////
  if (day_myage.toInt() == 0) {
    day_myage_s = "";
  }
  else if (day_myage.toInt() == 1) {
    day_myage_s = day_myage + "Day";
  }
  else {
    day_myage_s = day_myage + "Days";
  }
  //////////
  if (month_myage.toInt() == 0) {
    month_myage_s = "";
  }
  else if (month_myage.toInt() == 1) {
    month_myage_s = month_myage + "Month";
  }
  else {
    month_myage_s = month_myage + "Months";
  }
  //////////
}



void alexacontrol() {
  //Serial.println("alexa trying");
  if (WiFi.status() == WL_CONNECTED) {
    if (wifiConnected) {
      espalexa.loop();
      //Serial.println("alexa looping");
    }
    else {
      wifiConnected = connectWifi(); // Initialise wifi connection
      if (wifiConnected) {
        //Serial.println("alexa adding device");
        addDevices();
      }
    }
  }
}
void initializealexa() {
  wifiConnected = connectWifi();
  if (wifiConnected) {
    addDevices();
  }
  while (!wifiConnected)
  {
    addDevices();
    wifiConnected = connectWifi();
    //Serial.println("unable to add devices");
  }
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

//our callback functions
void firstLightChanged(uint8_t brightness) {
  //Control the device
  if (brightness == 255)
  {

    Serial.println("Device1 ON");
    Serial2.print("D1T");
  }
  else
  {

    Serial.println("Device1 OFF");
    Serial2.print("D1F");
  }
}
void secondLightChanged(uint8_t brightness) {
  //Control the device
  if (brightness == 255)
  {

    Serial.println("Device2 ON");
    Serial2.print("D2T");
  }
  else
  {

    Serial.println("Device2 OFF");
    Serial2.print("D2F");
  }
}
void thirdLightChanged(uint8_t brightness) {
  //Control the device
  if (brightness == 255)
  {

    Serial.println("Device3 ON");
    Serial2.print("D3T");
  }
  else
  {

    Serial.println("Device3 OFF");
    Serial2.print("D3F");
  }
}
void fourthLightChanged(uint8_t brightness) {
  //Control the device
  if (brightness == 255)
  {

    Serial.println("Device4 ON");
    Serial2.print("D4T");
  }
  else
  {

    Serial.println("Device4 OFF");
    Serial2.print("D4F");
  }
}
void fifthLightChanged(uint8_t brightness) {
  //Control the device
  if (brightness == 255)
  {

    Serial.println("Device5 ON");
    Serial2.print("D5T");
  }
  else
  {

    Serial.println("Device1 OFF");
    Serial2.print("D5F");
  }
}
void sixthLightChanged(uint8_t brightness) {
  //Control the device
   String temp;
  temp="mled"+String(brightness);
  Serial2.print(temp);
  
}
void seventhLightChanged(uint8_t brightness) {
  //Control the device
  String temp;
  temp="legfan"+String(brightness);
  Serial2.print(temp);
  
  
}
void eighthLightChanged(uint8_t brightness) {
  //Control the device
  if (brightness == 255)
  {
    Serial.println("Device8 ON");
    Serial2.print("D8T");
    drawimage1(75, 75, 400, 120);
  }
  else
  {
    Serial.println("Device8 OFF");
    Serial2.print("D8F");
    tft.fillRect(400, 115, 80, 95, bgcolor);
  }
}
void ninthLightChanged(uint8_t brightness) {
  //Control the device
  if (brightness == 255)
  {
    Serial.println("Device9 ON");
    Serial2.print("D9T");
    drawimage2(75, 90, 400, 115);
  }
  else
  {
    Serial.println("Device9 OFF");
    Serial2.print("D9F");
    tft.fillRect(400, 115, 80, 95, bgcolor);
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
  r = ((rgb >> 16) & 0xFF) * hell;
  g = ((rgb >>  8) & 0xFF) * hell;
  b = (rgb & 0xFF) * hell;
  String temp;
  temp = "clr" + String(r) + "|" + String(g) + "|" + String(b);

  Serial2.print(temp);
  /*
    Serial2.print("Brightness: ");
    Serial2.print(brightness);
    Serial2.print(", Red: ");
    Serial2.print(r); //get red component
    Serial2.print(", Green: ");
    Serial2.print(g); //get green
    Serial2.print(", Blue: ");
    Serial2.println(b); //get blue
  */
}
void wifiled(){
  if(millis()-wifiledtimer>2000){
  if ( WiFi.status() != WL_CONNECTED ) {
    digitalWrite(wifiledred,0);
    digitalWrite(wifiledgreen,1);
    
  }
  else{
    digitalWrite(wifiledred,1);
    digitalWrite(wifiledgreen,0);
  }
}
}
