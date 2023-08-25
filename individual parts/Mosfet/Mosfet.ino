/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Fade
*/

int led = 3;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  
  
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  for(int x=0;x<256;x++){
    analogWrite(led,x);
    Serial.println(x);
    delayMicroseconds(100);
  }
  //analogWrite(led,255);
  //delay(1500);
  for(int x=256;x>=0;x--){
    analogWrite(led,x);
    Serial.println(x);
    delayMicroseconds(100);
  }
}
