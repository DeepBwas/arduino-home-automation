//Deep Biswas
//August 16th 2023
//Description: Final Project
//Locker Arduino


#include <IRremote.h> //Library for IR Remote
#include <Servo.h> //Library for Serv0
#include <LiquidCrystal.h> //Libarry for LCD

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //LCD Pin initialization
#define IR_RECEIVE_PIN 8 //IR sensor pin initialization
Servo myservo; //Servo initialization
int value; //Variable to store a value
int numberValue; //Variable to store a numbervalue
bool Locked = true; //Variable to store lock position
String enteredPassword = ""; //String to store password

// Mapping IR remote values to numbers
#define BUTTON_0 12
#define BUTTON_1 16
#define BUTTON_2 17
#define BUTTON_3 18
#define BUTTON_4 20
#define BUTTON_5 21
#define BUTTON_6 22
#define BUTTON_7 24
#define BUTTON_8 25
#define BUTTON_9 26

void setup()
{
  lcd.begin(16, 2); //LCD Setup
  Serial.begin(9600); //Serial Monitor setup
  IrReceiver.begin(IR_RECEIVE_PIN); //IR setup
  myservo.attach(13); //Servo pin setup
  lcd.clear(); //Additional setup to display message
  lcd.setCursor(4, 0);
  lcd.print("WELCOME");
  lcd.setCursor(2, 1);
  lcd.print("Press Power B.");
}

void loop() {
  // Checking if an IR signal is received
  if (IrReceiver.decode()) {
    value = IrReceiver.decodedIRData.command;
    Serial.print("IR Value: ");
    Serial.println(numberValue);

    // Power Button press to enter Password Mode
    if (value == 0 && Locked) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter Password");
      enteredPassword = "";
      while (enteredPassword.length() < 8) {
        if (IrReceiver.decode()) {
          int numberValue = IrReceiver.decodedIRData.command;
          if (numberValue == BUTTON_9 || numberValue == BUTTON_8 ||
              numberValue == BUTTON_7 || numberValue == BUTTON_6 ||
              numberValue == BUTTON_5 || numberValue == BUTTON_4 ||
              numberValue == BUTTON_3 || numberValue == BUTTON_2 ||
              numberValue == BUTTON_1 || numberValue == BUTTON_0) {
            lcd.setCursor(enteredPassword.length(), 1);
            lcd.print("*");
            enteredPassword += String(numberValue);
          }
          IrReceiver.resume();
        }
      }

      // Check the entered password
      if (enteredPassword == "18171612") { // Correct password sequence (3, 2, 1, 0)
        Locked = false;
        lcd.clear();
        lcd.print("Welcome Home!");
        myservo.write(0);
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Door will lock");
        lcd.setCursor(0, 1);
        lcd.print("in 3 seconds");
        delay(3000);
      } else {
        lcd.clear();
        lcd.print("Incorrect!");
        delay(1000);
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("WELCOME");
        lcd.setCursor(2, 1);
        lcd.print("Press Power B.");
      }
    }

    // Automatic Lock Door Mode
    if (value == 0 && !Locked) {
      lcd.clear();
      lcd.print("Door Locked");
      Locked = true;
      myservo.write(90);
      delay(1000);
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("WELCOME");
      lcd.setCursor(2, 1);
      lcd.print("Press Power B.");
    }

    IrReceiver.resume();
  }
}