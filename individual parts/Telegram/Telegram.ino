



#include <WiFi.h>         
#include <HTTPClient.h>   

const char* ssid = "Amit";           
const char* password =  "amit@123";    

String userid = "aayushbhansali"; 

String url;                            
void setup() 
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);              // Try to connect with the given SSID and PSS
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {  // Wait until WiFi is connected
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to the WiFi network"); // Print wifi connect message

  
  message_to_tele("Welcome....");  
  call_to_tele("This is a robot calling you to inform you about something urgent that is happening");
}
int x=0;
void loop()
{
  message_to_tele(String(x));
  Serial.println(x);
  x++;
  delay(1000);
}

void  message_to_tele(String message)       {
  //adding all number, your api key, your message into one complete url
  url = "https://api.callmebot.com/text.php?user=@" + userid + "&text="+ urlencode(message);
//https://api.callmebot.com/text.php?user=@myusername&text=This+is+a+test+from+CallMeBot
  postData(); // calling postData to run the above-generated url once so that you will receive a message.
}
void call_to_tele(String message){
    url = "http://api.callmebot.com/start.php?user=@"+ userid + "&text=" +urlencode(message)+"&lang=en-GB-Standard-B&rpt=2&cc=missed";
    
postData();
}

void postData()     {
  int httpCode;     // variable used to get the responce http code after calling api
  HTTPClient http;  // Declare object of class HTTPClient
  http.begin(url);  // begin the HTTPClient object with generated url
  httpCode = http.POST(url); // Finaly Post the URL with this function and it will store the http code
  if (httpCode == 200)      // Check if the responce http code is 200
  {
    Serial.println("Sent ok."); // print message sent ok message
  }
  else                      // if response HTTP code is not 200 it means there is some error.
  {
    Serial.println("Error."); // print error message.
  }
  http.end();          // After calling API end the HTTP client object.
}

String urlencode(String str) {
    String encodedString="";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i =0; i < str.length(); i++){
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
        //encodedString+=code2;
      }
      yield();
    }
    return encodedString;
}
