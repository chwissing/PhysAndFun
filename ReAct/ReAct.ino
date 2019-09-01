/*

 ReAct

 Uses an LCD via LiquidCrystal to display

 Once an LED gets off after random time, press button as quickly as possible as possibel to measure reaction time
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

For LiquidCrystal check:

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//#define ledPin  LED_BUILTIN                 // LED connected to digital pin 13
#define ledPin 8
#define StopPin 6                  // via button
#define WAITING 0
#define REACTION 1

int imode;
long RandomAt;
long now;

void setup() {
  Serial.begin(115200);
  //Get some noise from unconnected analog input
  randomSeed(analogRead(0));
  pinMode(StopPin, INPUT);
  digitalWrite(StopPin, HIGH);
  Serial.print("ReAct 1.0\n");
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("ReAct V1.1");
  lcd.setCursor(0,1);
  lcd.print("CW Aug 2018");
  pinMode(ledPin, OUTPUT);         // sets the digital pin as output
  digitalWrite(ledPin, LOW);
  delay(1000);
  imode=WAITING;
}

void ReactionTest(long t_start){
  long t_react;
  while(digitalRead(StopPin)==HIGH)
    ;;
  now=millis();
  t_react=now-t_start;
  Serial.print("Reaction: ");
  Serial.print(t_react);
  Serial.println(" ms");
  lcd.clear();
  lcd.print("t [ms]: ");
  //lcd.setCursor(6,0);
  lcd.print(t_react);
}

void loop() {
  if (imode==WAITING){  
     Serial.println("Press button");
     lcd.setCursor(0,1);
     lcd.print("Press Button   ");
     while(digitalRead(StopPin)==HIGH){    
       now=millis();
       RandomAt=now+random(2,10)*1000;
       delay(10);
     }
     lcd.clear();
     lcd.print("Reaction Test   ");
     lcd.setCursor(0,1);
     lcd.print("                ");
     imode=REACTION;
     digitalWrite(ledPin, HIGH);
  }
  now=millis();
  if ( now > RandomAt){
    Serial.print("ReAct Test start!\n");
    digitalWrite(ledPin, LOW);
    now=millis();
    ReactionTest(now);
    imode=WAITING;
    delay(500);
  }  
}
