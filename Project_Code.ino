#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10 //RX slave select
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

byte card_ID[4]; //card UID size 4byte

byte s1[4]={0x86,0x00,0x3D,0x29};//first UID card
byte s2[4]={0x60, 0x73, 0x13, 0x71};//second UID card
byte s3[4] = {0xC7, 0x44, 0xE3, 0xE0};
byte s4[4] = {0xC0, 0xD9, 0x71, 0xAE};
byte s5[4] = {0xE0, 0x13, 0xBD, 0xD4};

//if you want the Arduino to detect the cards only once
int NumbCard[5];//this array contains the number of cards. in my case, i have just two cards.
int j=0;        

int const RedLed=6;
int const GreenLed=5;

String Name;//user name
String Number;//user number
int n=5 ;//The number of cards you want to detect (optional)  

void setup() 
{
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  
  Serial.println("CLEARSHEET");                 // clears starting at row 1
  Serial.println("LABEL,Date,Time,Student Name,Register Number");// make four columns (Date,Time,[Name:"user name"]line 48 & 52,[Number:"user number"]line 49 & 53)

  pinMode(RedLed,OUTPUT);
  pinMode(GreenLed,OUTPUT);

}
    
void loop() 
{
  //look for a new card
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;//got to start of the loop if there is no card present
 }
 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;//if read card serial(0) returns 1, the uid struct contains the ID of the read card.
 }
 
 for (byte i = 0; i < mfrc522.uid.size; i++) 
 {
      card_ID[1]=mfrc522.uid.uidByte[1];
      card_ID[2]=mfrc522.uid.uidByte[2];
      card_ID[3]=mfrc522.uid.uidByte[3];
      card_ID[4]=mfrc522.uid.uidByte[4];
     

       if(card_ID[1]==s1[1] && card_ID[2]==s1[2] && card_ID[3]==s1[3] && card_ID[4]==s1[4])
       {
       Name="Student A";//user name
       Number="20BPS1115";//user number
       j=0;//first number in the NumbCard array : NumbCard[j]

      }
      else if(card_ID[1]==s2[1] && card_ID[2]==s2[2] && card_ID[3]==s2[3] && card_ID[4]==s2[4])
      {
       Name="Student B";//user name
       Number="20BPS1111";//user number
       j=1;//Second number in the NumbCard array : NumbCard[j]
      }

      else if(card_ID[1]==s3[1] && card_ID[2]==s3[2] && card_ID[3]==s3[3] && card_ID[4]==s3[4])
      {
       Name="Student C";//user name
       Number="20BPS1110";//user number
       j=2;//Second number in the NumbCard array : NumbCard[j]
      }

      else if(card_ID[1]==s4[1] && card_ID[2]==s4[2] && card_ID[3]==s4[3] && card_ID[4]==s4[4])
      {
       Name="Student D";//user name
       Number="20BAI1234";//user number
       j=3;//Second number in the NumbCard array : NumbCard[j]
      }

      else if(card_ID[1]==s5[1] && card_ID[2]==s5[2] && card_ID[3]==s5[3] && card_ID[4]==s5[4])
      {
       Name="Student E";//user name
       Number="20BCE1135";//user number
       j=4;//Second number in the NumbCard array : NumbCard[j]
      }
      else{
          digitalWrite(GreenLed,LOW);
          digitalWrite(RedLed,HIGH);
          //delay(1000);
          goto cont;//go directly to line 85
     }
}
      if(NumbCard[j] == 1){//to check if the card already detect
      //if you want to use LCD
      //Serial.println("Already Exist");
      }
      else{
      NumbCard[j] = 1;//put 1 in the NumbCard array : NumbCard[j]={1,1} to let the arduino know if the card was detecting 
      n++;//(optional)
      Serial.print("DATA,DATE,TIME," + Name);//send the Name to excel
      Serial.print(",");
      Serial.println(Number); //send the Number to excel
      digitalWrite(GreenLed,HIGH);
      digitalWrite(RedLed,LOW);
      Serial.println("SAVEWORKBOOKAS,Names/WorkNames");
      }
cont:
delay(2000);
digitalWrite(GreenLed,LOW);
digitalWrite(RedLed,LOW);
}
