#include <LiquidCrystal.h>

const int pingPin = 6; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 5; // Echo Pin of Ultrasonic Sensor
long duration;
int distanceCm;
int oldValue = 0 , newValue = 0;

//PIR sensor
#define pirPin 7
int LEDblue = 4;
int PIRValue = 0;

//Gas Sensor
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
int Gas = 3;

void setup()
{
  Serial.begin(9600); // Starting Serial Terminal

  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //PIR Sensor
  pinMode(pirPin, INPUT);
  pinMode(LEDblue, OUTPUT);

  //gas sensor
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("Gas Detected :");
  pinMode(Gas , INPUT);
}

void loop()
{ 
  //Ultrasonic Sensor
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.0340 / 2;
  newValue = distanceCm;
  if(newValue != oldValue)
  {
    Serial.print(distanceCm);
    Serial.print("|");
    oldValue = newValue;
  }
  else{
    Serial.print(distanceCm);
    Serial.print("|");
  }

  //Gas Sensor
  {if(digitalRead(Gas) == HIGH){
    lcd.setCursor(14,0);
    lcd.print("Yes");
    Serial.print("Yes ");
    Serial.print("|");
  }
  else{
    lcd.setCursor(14,0);
    lcd.print("No ");
    Serial.print("No ");
    Serial.print("|");
  }}

  //PIR Sensor
  {if(digitalRead(pirPin) == HIGH){       
      PIRValue = 1;
      digitalWrite(LEDblue, HIGH);
      Serial.print("Motion-detected ");
      Serial.print("|");
  }
  else{   
      PIRValue = 0;         
      digitalWrite(LEDblue, LOW);           
      Serial.print("Motion-ended ");
      Serial.print("|");
    }
  }

  delay(5000);
  system("cls");
}
