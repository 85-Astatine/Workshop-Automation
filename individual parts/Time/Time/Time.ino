#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TimeLib.h>


const char *ssid     = "Amit";
const char *password = "amit@123";

WiFiUDP ntpUDP;


NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", 19800, 60000);


String  second_, minute_, hour_, day_, month_,year_;
String monstr,daystr;
unsigned long unix_epoch;
int last_second;



void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting.");
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  
  timeClient.begin();
  Serial.println("connected");
}


void loop() {

     serialprinttime();
getsec();
serialprinttime();
  if (last_second != second_.toInt()) {
    gettime();
    addzero();//should be after convert mon and day
    serialprinttime();
    last_second=second_.toInt();
  }
  //delay(500);
  serialprinttime();
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
void addzero(){
  if(second_.toInt()<=9){
    second_="0"+second_;
  }
  if(minute_.toInt()<=9){
    minute_="0"+minute_;
  }
   if(hour_.toInt()<=9){
    hour_="0"+hour_;
  }
  if(day_.toInt()<=9){
    day_="0"+day_;
  }
   if(month_.toInt()<=9){
    month_="0"+month_;
  }
   
}
void serialprinttime(){
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
void getsec(){
  timeClient.update();
  unix_epoch = timeClient.getEpochTime();
  second_ = String(second(unix_epoch));
}
void gettime(){
    minute_ = String(minute(unix_epoch));
    hour_   = String(hour(unix_epoch));
    day_    = String(day(unix_epoch));
    month_  = String(month(unix_epoch));
    year_   = String(year(unix_epoch));
    monstr = convertmon();
    daystr = convertday();
}
