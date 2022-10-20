#include <SPI.h>
#include <MFRC522.h>
#include <ezButton.h>
#include "wifi_connect.h"
#include "requests.h"

#define SS_PIN 5
#define RST_PIN 22
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#define BUTTON_mode 13  
#define BUTTON_ok 12  
#define LED_green    27  
#define LED_red    14  
#define LED_blue    26  

ezButton buttonmode(BUTTON_mode); 
ezButton buttonok(BUTTON_ok);  

String UID[10][15]={};
int j;
int c = 1 ;


void setup() 
{
  
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  
  pinMode(WIFI_LED, OUTPUT);
  connectWifi();
  
  pinMode(LED_green, OUTPUT);   // set ESP32 pin to output mode
  pinMode(LED_red, OUTPUT);   // set ESP32 pin to output mode
  pinMode(LED_blue, OUTPUT);   // set ESP32 pin to output mode
  buttonmode.setDebounceTime(50); // set debounce time to 50 milliseconds
  buttonok.setDebounceTime(50); // set debounce time to 50 milliseconds


}
void loop() 
{

  buttonmode.loop(); // MUST call the loop() function first
  buttonok.loop(); // MUST call the loop() function first
  checkConnectivity();
      if(buttonmode.isPressed()&& c==1)
  {
    Serial.println("Saving mode is working now ......"); c=2;
    digitalWrite(LED_blue, HIGH);digitalWrite(LED_green, LOW);digitalWrite(LED_red, LOW);
      
       while (digitalRead(BUTTON_ok)== LOW )
       {

         saving();

       }
  
      Serial.println("Saved successfully ^-^");
      digitalWrite(LED_blue, LOW);digitalWrite(LED_green, HIGH);digitalWrite(LED_red, LOW);

      
      //scanProductId()
  } 
 else if (buttonmode.isPressed()&& c==2) {
    Serial.println("Scaning mode is working now ......"); c=1 ; 
    digitalWrite(LED_blue, LOW);digitalWrite(LED_green, LOW);digitalWrite(LED_red, HIGH);

    //storeIdList()
  
  
  }
  
}



void saving(){
    // Look for new cards
  if (  mfrc522.PICC_IsNewCardPresent()) 
  {
 
  // Select one of the cards
  if (  mfrc522.PICC_ReadCardSerial()) 
  {
    //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
 
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  { 
     Serial.print(mfrc522.uid.uidByte[i]);
     UID[j][i]= mfrc522.uid.uidByte[i];   
    
  }
  Serial.println(); 
  j++;
  delay(2000);
  
  for (byte l = 0; l < 10; l++) 
  {
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  { 
    Serial.print( UID[l][i]); 
      
  }
    Serial.println();    
  }


  }
  }
  return ;
}
