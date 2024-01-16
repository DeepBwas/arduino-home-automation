//Deep Biswas
//August 16th 2023
//Description: Final Project
//Sensors Arduino


#include <LiquidCrystal.h> //Adding LCD Library
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //LCD Pin initialization
int distanceThreshold = 0; //Variable to store distance from US Sensor
int cm = 0; //Variable to store distance in cm
int inches = 0; //Variable to store distance in inch
int releNO = 13; //Relay pin initialization
int inputPir = 8; //PIR sensor pin initialization
int val = 0; //Variable to store a value
int LDR; //Variable to store light sensor data
int sensorLDR = A0; //Light sensor pin initialization
int const PINO_SGAS = A1; //Gas sensor pin initialization

//UltraSonic sensor pin initialization
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT); 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup() {
  lcd.begin(16, 2); //LCD Setup
  pinMode(releNO, OUTPUT); //Relay as OUTPUT
  pinMode(inputPir, INPUT); //PIR as INPUT
  pinMode(sensorLDR, INPUT); //Light sensor as INPUT
  Serial.begin(9600); //Serial Monitor Setup
}

void loop() {
  //Function to display distance in CM
  distanceThreshold = 350;
  cm = 0.01723 * readUltrasonicDistance(7, 6);
  inches = (cm / 2.54);
  
  lcd.setCursor(0,0);
  lcd.print("D:");
  lcd.print(cm);
  lcd.print("cm");
  delay(10);
  
  //Function to turn on the light automatically using LDR and PIR
    val = digitalRead(inputPir);
  LDR = analogRead(sensorLDR);
  Serial.println(LDR);
  if(LDR < 600)
  {
    if(val == HIGH)
    {
      digitalWrite(releNO, HIGH);
      lcd.setCursor(0,1);
  lcd.print("L: On ");
      delay(10000);
  }
    else{
      digitalWrite(releNO, LOW);lcd.setCursor(0,1);
  lcd.print("L: Off");
      delay(300);
  }
}
  else{ digitalWrite (releNO, LOW);
  Serial.println(LDR);
  delay(500);
  }
  //Gas sensor input Display using gas sensor
  int color = analogRead(PINO_SGAS);
  
  lcd.setCursor(8,0);
  if(color <= 85){
    lcd.print("G:Low ");
  } else if(color <= 120){
    lcd.print("G:Med ");
  } else if(color <= 200){
    lcd.print("G:High");
  } else if(color <= 300){
    lcd.print("G:Ext ");
  }
  
  delay(250); //To debounce.
}