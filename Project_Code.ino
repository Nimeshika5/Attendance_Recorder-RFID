#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10 
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); 

byte card_ID[4]; 

byte s1[4] = {0x86, 0x00, 0x3D, 0x29};
byte s2[4] = {0x60, 0x73, 0x13, 0x71};
byte s3[4] = {0xC7, 0x44, 0xE3, 0xE0};
byte s4[4] = {0xC0, 0xD9, 0x71, 0xAE};
byte s5[4] = {0xE0, 0x13, 0xBD, 0xD4};

int NumbCard[5];
int j=0;        

int const RedLed=6;
int const GreenLed=5;

String Name, Number;

void setup() 
{
  Serial.begin(9600); 
  SPI.begin();  
  mfrc522.PCD_Init(); 
  
  Serial.println("CLEARSHEET");            
  Serial.println("LABEL,Date,Time,Student Name,Register Number");

  pinMode(RedLed,OUTPUT);
  pinMode(GreenLed,OUTPUT);

}
    
void loop() 
{
   if ( ! mfrc522.PICC_IsNewCardPresent()) 
   {
      return;
   }
 if ( ! mfrc522.PICC_ReadCardSerial()) 
 {
    return;
 }
 
 for (byte i = 0; i < mfrc522.uid.size; i++) 
 {
      card_ID[1]=mfrc522.uid.uidByte[1];
      card_ID[2]=mfrc522.uid.uidByte[2];
      card_ID[3]=mfrc522.uid.uidByte[3];
      card_ID[4]=mfrc522.uid.uidByte[4];
     

       if(card_ID[1]==s1[1] && card_ID[2]==s1[2] && card_ID[3]==s1[3] && card_ID[4]==s1[4])
       {
           Name="Student A";
           Number="20BPS1115";
           j=0;

      }
      else if(card_ID[1]==s2[1] && card_ID[2]==s2[2] && card_ID[3]==s2[3] && card_ID[4]==s2[4])
      {
          Name="Student B";
          Number="20BPS1111";
          j=1;
      }

      else if(card_ID[1]==s3[1] && card_ID[2]==s3[2] && card_ID[3]==s3[3] && card_ID[4]==s3[4])
      {
          Name="Student C";
          Number="20BPS1110";
          j=2;
      }

      else if(card_ID[1]==s4[1] && card_ID[2]==s4[2] && card_ID[3]==s4[3] && card_ID[4]==s4[4])
      {
          Name="Student D";
          Number="20BAI1234";
          j=3;
      }

      else if(card_ID[1]==s5[1] && card_ID[2]==s5[2] && card_ID[3]==s5[3] && card_ID[4]==s5[4])
      {
          Name="Student E";
          Number="20BCE1135";
          j=4;
      }
      
      else
      {
          digitalWrite(GreenLed,LOW);
          digitalWrite(RedLed,HIGH);
          goto cont;
     }
}
       if(NumbCard[j]!=1 && NumbCard[j]!=100)
      {
          NumbCard[j] = 1;
          Serial.print("DATA,DATE,TIME," + Name);
          Serial.print(",");
          Serial.println(Number); 
          digitalWrite(GreenLed,HIGH);
          digitalWrite(RedLed,LOW);
      }
      
      else if(NumbCard[j] == 1)
      {
          /*NumbCard[j] = 100;
          Serial.print("DATA,DATE,TIME," + Name);
          Serial.print(",");
          Serial.println(Number );  
          digitalWrite(RedLed,LOW);
          digitalWrite(GreenLed,HIGH);*/
      }
      
cont:
  delay(2000);
  digitalWrite(GreenLed,LOW);
  digitalWrite(RedLed,LOW);
}
