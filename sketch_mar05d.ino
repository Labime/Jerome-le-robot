#include <SPI.h>
#include <RFID.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


RFID RFID(9, 10);
int const mot1a = 3 ;
int const mot1b = 10 ;
int const mot2a = 6 ;
int const mot2b = 5 ;
const int L1 = 2;
const int L2 = 5;
int UID[5] = {};
int MASTERKEY[5] = {211, 41, 191, 36, 97};
int KEY[5] = {198, 183, 77, 26, 38};
int STOP[5] = {214, 30, 137, 30, 95};

LiquidCrystal_I2C lcd(0x27, 20, 4);

bool statut = 1;

void setup()
{
  lcd.init();
  lcd.print("Salut");
  Serial.begin(9600);
  SPI.begin();
  RFID.init();
  pinMode(L1, OUTPUT);
  pinMode(mot1a,OUTPUT) ;    
  pinMode(mot1b,OUTPUT) ; 
  pinMode(mot2a,OUTPUT) ;   
  pinMode(mot2b,OUTPUT) ;

}

void loop()
{
lcd.backlight();
lcd.setCursor(0, 0);
  
  if (RFID.isCard()) {


    if (RFID.readCardSerial())
    {
      Serial.print("L'UID est: ");
      for (int i = 0; i <= 4; i++)
      {
        UID[i] = RFID.serNum[i];
         Serial.print(UID[i],DEC);
          Serial.print(".");
      }
      Serial.println("");
    }


    if (UID[0] == MASTERKEY[0]   
        && UID[1] == MASTERKEY[1]   
        && UID[2] == MASTERKEY[2]   
        && UID[3] == MASTERKEY[3]   
        && UID[4] == MASTERKEY[4])  
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Je recul");
      digitalWrite(mot1a,LOW) ; 
      digitalWrite(mot1b,HIGH) ;
      delay(5000) ;
    }
    else
    {
      digitalWrite(L1, LOW);
      
    }

 if (UID[0] == KEY[0]   
        && UID[1] == KEY[1]   
        && UID[2] == KEY[2]   
        && UID[3] == KEY[3]   
        && UID[4] == KEY[4])  
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("J'avance");
      digitalWrite(mot1a,HIGH) ;
      digitalWrite(mot1b,LOW) ;
      delay(5000) ; 
    }
    else
    {
      digitalWrite(L2, LOW);

    }
    
 if (UID[0] == STOP[0]   
        && UID[1] == STOP[1]   
        && UID[2] == STOP[2]   
        && UID[3] == STOP[3]   
        && UID[4] == STOP[4])  
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Je m'arrete");
      digitalWrite(mot1a,LOW) ;
      digitalWrite(mot1b,LOW) ;
      delay(5000) ; 
    }
    else
    {
      digitalWrite(L2, LOW);

    }
    
    RFID.halt();
  }
  delay(100);
}

