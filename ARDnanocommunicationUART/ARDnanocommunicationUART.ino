
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10); // RX, TX//connection on 9
String incdata = "";
int r, g, b;

#define Rpin 6
#define Gpin 10
#define Bpin 11
#define delayLEDS 50
#define audiosensorPin A0
float d = 1;
float audiosensorValue = 0, filteredSignal = 0,
      filteredSignalValues[] = {4.7 * d, 4.4 * d, 4.2 * d, 3.9 * d, 3.6 * d, 3.3 * d, 2.9 * d, 2.5 * d, 2.1 * d }; //9 items
float point[5] = {5, 4.2, 3.2, 2.6, 2};
bool musicled = false;
float musicledbrightness = 0;


////devices NOTE relay module is inverted so 0, is on and 1 in off
#define focuslight A2
#define tubelight A3
#define studylight 7
#define roomlight 8
#define fan A4
#define audioamp 12

#define legfan 3
int legfanspeed = 0;
#define callswitch A1 //on lcd board
bool callswitchstatus = false;
bool switchledtoggle = false;
long switchledtimer;

#include <FastLED.h>
FASTLED_USING_NAMESPACE
#define DATA_PIN 4
#define NUM_LEDS 280
CRGB leds[NUM_LEDS];
#define FRAMES_PER_SECOND  60

bool flashylight=false;
void setup() {
  pinMode(focuslight, OUTPUT);
  pinMode(tubelight, OUTPUT);
  pinMode(studylight, OUTPUT);
  pinMode(roomlight, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(audioamp, OUTPUT);
  pinMode(Rpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  pinMode(legfan, OUTPUT);
  pinMode(callswitch, INPUT_PULLUP);
  digitalWrite(callswitch, 1);
  digitalWrite(tubelight, 1);
  digitalWrite(roomlight, 1);
  digitalWrite(focuslight, 1);
  digitalWrite(fan, 1);
  digitalWrite(audioamp, 1);
  digitalWrite(studylight, 1);
  digitalWrite(Gpin, 0);
  Serial.begin(9600);
  mySerial.begin(9600);
  FastLED.setBrightness(255);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  
  //pinMode(10, OUTPUT);
  //analogWrite(10, 128);
    
}
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void loop() {
  checkfordata();
  checkforswitch();
  if (incdata != "") {
    Serial.println(incdata);
    checkfordatamatch();
  }
  if (musicled) {
    musicLEDfunction();
  }
  if(flashylight){
  custommusiclightsalgo();
  }
  Serial.println("uu");
}
void checkfordata() {
  while (mySerial.available()) {
    char c = mySerial.read();
    incdata += c;
    delay(2);
  }
}
void checkfordatamatch() {
  if (!(incdata.indexOf("clr") == -1)) {
    normalledstrip();
  }
  else if (!(incdata.indexOf("legfan") == -1)) {
    incdata.remove(0, 6);
    legfanspeed = incdata.toInt();
    analogWrite(legfan, legfanspeed);
  }
  else if (!(incdata.indexOf("mled") == -1)) {
    incdata.remove(0, 4);
    musicledbrightness = incdata.toInt();
    musicledbrightness = musicledbrightness / 255.0;
    Serial.println(musicledbrightness);
    if (musicledbrightness != 0) {
      musicled = true;
    }
    else {
      musicled = false;
      RGBColor(0, 0, 0);
    }
  }
  else {
    if (incdata == "D1T") {
      Serial.println("Relay 1 On");
      digitalWrite(fan, 0);
    }
    else if (incdata == "D1F") {
      Serial.println("Relay 1 Off");
      digitalWrite(fan, 1);
    }
    if (incdata == "D2T") {
      Serial.println("Relay 2 On");
      digitalWrite(tubelight, 0);
    }
    else if (incdata == "D2F") {
      Serial.println("Relay 2 Off");
      digitalWrite(tubelight, 1);
    }
    if (incdata == "D3T") {
      Serial.println("Relay 3 On");
      digitalWrite(roomlight, 0);
    }
    else if (incdata == "D3F") {
      Serial.println("Relay 3 Off");
      digitalWrite(roomlight, 1);
    }
    if (incdata == "D4T") {
      Serial.println("Relay 4 On");
      digitalWrite(focuslight, 0);
    }
    else if (incdata == "D4F") {
      Serial.println("Relay 4 Off");
      digitalWrite(focuslight, 1);
    }
    if (incdata == "D5T") {
      Serial.println("Relay 5 On");
      digitalWrite(studylight, 0);
    }
    else if (incdata == "D5F") {
      Serial.println("Relay 5 Off");
      digitalWrite(studylight, 1);
    }
    if (incdata == "D6T") {
      Serial.println("Relay 6 On");
      musicled = true;
    }
    else if (incdata == "D6F") {
      Serial.println("Relay 6 Off");
      musicled = false;
      RGBColor(0, 0, 0);
    }
    if (incdata == "D7T") {
      Serial.println("Relay 7 On");
    }
    else if (incdata == "D7F") {
      Serial.println("Relay 7 Off");
    }
    if (incdata == "D8T") {
      Serial.println("Relay 8 On");
      digitalWrite(audioamp, 0);
    }
    else if (incdata == "D8F") {
      Serial.println("Relay 8 Off");
      digitalWrite(audioamp, 1);
    }
    if (incdata == "D9T") {
      Serial.println("Relay 9 On");
      flashylight=true;
    }
    else if (incdata == "D9F") {
      Serial.println("Relay 9 Off");
      flashylight=false;
    }












  }
  incdata = "";
}
void normalledstrip() {
  musicled = false;
  musicledbrightness = 1;
  incdata.remove(0, 3);
  Serial.println(incdata);
  String temp;
  int index;
  temp = incdata;
  index = temp.indexOf("|");
  temp.remove(index, temp.length() - index);
  r = temp.toInt();
  incdata.remove(0, index + 1);
  temp = incdata;
  index = temp.indexOf("|");
  temp.remove(index, temp.length() - index);
  g = temp.toInt();
  incdata.remove(0, index + 1);
  b = incdata.toInt();
  Serial.print("Red:");
  Serial.println(r);
  Serial.print("Green:");
  Serial.println(g);
  Serial.print("Blue:");
  Serial.println(b);
  Serial.println();
  RGBColor(r, g, b);
}
void musicLEDfunction() {

  audiosensorValue = (float) analogRead(audiosensorPin) * (5.0 / 1024.0);
  FilterSignal(audiosensorValue);
  if(flashylight){
  custommusiclightsalgo();
  }
  else{
    CompareSignalFiltered(filteredSignal);
  }
}

void FilterSignal(float sensorSignal) {

  filteredSignal = (0.945 * filteredSignal) + (0.0549 * sensorSignal);
}

void CompareSignalFiltered(float filteredSignal) {

  if (filteredSignal > filteredSignalValues[0]) {
    RGBColor(0, 0, 255);
    //Serial.println("Blue");
  } else if (filteredSignal <= filteredSignalValues[0] && filteredSignal > filteredSignalValues[1]) {
    //Serial.println("Azure");
    RGBColor(0, 255, 255);
  } else if (filteredSignal <= filteredSignalValues[1] && filteredSignal > filteredSignalValues[2]) {
    RGBColor(0, 127, 255);
    //Serial.println("Cyan");
  } else if (filteredSignal <= filteredSignalValues[2] && filteredSignal > filteredSignalValues[3]) {
    RGBColor(0, 255, 127);
    //Serial.println("Aqua marine");
  } else if (filteredSignal <= filteredSignalValues[3] && filteredSignal > filteredSignalValues[4]) {
    RGBColor(0, 255, 0);
    //Serial.println("Green");
  } else if (filteredSignal <= filteredSignalValues[4] && filteredSignal > filteredSignalValues[5]) {
    RGBColor(255, 255, 0);
    //Serial.println("Yellow");
  } else if (filteredSignal <= filteredSignalValues[5] && filteredSignal > filteredSignalValues[6]) {
    RGBColor(255, 0, 255);
    //Serial.println("Magenta");
  } else if (filteredSignal <= filteredSignalValues[6] && filteredSignal > filteredSignalValues[7]) {
    RGBColor(255, 0, 127);
    //Serial.println("Rose");
  } else if (filteredSignal <= filteredSignalValues[7] && filteredSignal > filteredSignalValues[8]) {
    RGBColor(255, 127, 0);
    //Serial.println("Orange");
  } else if (filteredSignal <= filteredSignalValues[8]) {
    RGBColor(255, 0, 0);
    //Serial.println("Red");
  } else {
    RGBColor(0, 0, 255);
    //Serial.println("Default: Blue");
  }
}

void RGBColor(int Rcolor, int Gcolor, int Bcolor) {
  int redd = Rcolor * musicledbrightness;
  int greenn = Gcolor * musicledbrightness;
  int bluee = Bcolor * musicledbrightness;
  analogWrite(Rpin, redd);
  analogWrite(Gpin, greenn);
  analogWrite(Bpin, bluee);
  for(int x=0;x<NUM_LEDS;x++){
     leds[x].r = redd; 
    leds[x].g = greenn; 
    leds[x].b = bluee;
}
  FastLED.show();
  delay(delayLEDS);
}
// void custommusiclightsalgo() {
//   int red;
//   int green;
//   int blue;
//   if (filteredSignal > point[2]) {
//     blue = (filteredSignal - point[2]) / (point[0] - point[2]) * 255;

//   }
//   else {
//     blue = 0;
//   }
//   if (filteredSignal < point[1] && filteredSignal > point[3]) {
//     green = (filteredSignal - point[3]) / (point[1] - point[3]) * 255;

//   }
//   else {
//     green = 0;
//   }
//   if (filteredSignal < point[2] && filteredSignal > point[4]) {
//     red = (filteredSignal - point[4]) / (point[2] - point[4]) * 255;

//   }
//   else {
//     red = 0;
//   }
//   if (filteredSignal < point[4]) {
//     red = 255;
//   }
//   Serial.print("Red:");
//   Serial.print(red);
//   Serial.print("\tGreen:");
//   Serial.print(green);
//   Serial.print("\tBlue:");
//   Serial.println(blue);
//   Serial.println();
//   RGBColor(red, green, blue);
// }
void custommusiclightsalgo() {
gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}



void checkforswitch() {
  //Serial.println(digitalRead(callswitch));
  if (digitalRead(callswitch) == 0) {
    callswitchstatus = !callswitchstatus;
    //Serial.print("switch toggle");
    delay(500);
  }

  if (millis() - switchledtimer > 500) {
    switchledtimer=millis();
    if (callswitchstatus) {
      switchledtoggle = !switchledtoggle;
      if (switchledtoggle) {
        flashylight=!flashylight;
        leds[0] = CRGB::Red;
        FastLED.show();
      }
      else {
        for(int dot = 0; dot < NUM_LEDS; dot++) { 
    leds[dot] = CRGB::Black;
  }
        FastLED.show();
      }
    }
    else {
      leds[0] = CRGB::Black;
      FastLED.show();
    }
  }
  else {

  }
}
