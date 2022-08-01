#include <LiquidCrystal.h>
#include <Keypad.h>
#include <EEPROM.h>

LiquidCrystal lcd {A0, 12, 11, 10, 9 , 8 };

char Keymap[4][4] = {
  {'7', '8', '9', 'A'},
  {'4', '5', '6', 'B'},
  {'1', '2', '3', 'C'},
  {'*', '0', '#', 'D'},
};

byte rowPins[4] = {7, 6, 5, 4};
byte colPins[4] = {3, 2, 1, 0};

Keypad myKeypad = Keypad(makeKeymap(Keymap), rowPins, colPins, 4 , 4);


char password[4] = {'1', '2', '3', '6'};
char userpress[4];
char keypressed;



void setup() {
    pinMode(13, OUTPUT);
 digitalWrite(13, LOW);

  if (EEPROM.read(4) == 0) {
    for (int i = 0; i <= 3; i++) {
      EEPROM.write(i, password[i]);
    }
   
  }
 EEPROM.write(4, (EEPROM.read(3) + 1));
  lcd.begin(16, 2);
  lcd.clear();

  lcd.print("Welcome, Press *");

}

void loop() {


  keypressed = myKeypad.getKey();


  if (keypressed != NO_KEY)
  {
    if (keypressed == '*') {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter Password: ");
      lcd.setCursor(1, 1);
      get_password();
    byte match_value = check_password();
   
      if ( match_value == 4) {
        lcd.clear();
        lcd.setCursor(0,0);
       lcd.print("DOOR OPEND");
        digitalWrite(13, HIGH);
        delay(5000);
        digitalWrite(13, LOW);
          lcd.print("DOOR CLOSED");
      }else{
            lcd.clear();
        lcd.setCursor(0,0);
          lcd.print("PASSWORD INVALID");
 
             
        }
    }

  }
}





void get_password() {
  boolean a = 1;
  byte keycount = 0;

  while (a) {
    keypressed = myKeypad.getKey();
    if (keypressed != NO_KEY) {
      userpress[keycount] = keypressed;
      lcd.print("*");
      keycount ++;
      if (keycount == 4) {
        a = 0;
      }

    }

  }

}


byte check_password()
{

  byte b = 0;
  for (int i = 0; i <= 3; i++)
  {
    char eprom = EEPROM.read(i);
    if (userpress[i] == eprom) {
      b++;

    }
    return b;
  }

}
