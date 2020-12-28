#include<EasyA6.h>

//!!!!
// The Simcard must be unlocked!! (No PIN)
//!!!!

//tx to D3, rx to D2, Baudrate, Set Your APN code
EasyA6 easyA6(3, 2, 9600, "APN");

void setup() { 
  Serial.begin(9600);
  Serial.println("Start Setup");

  //configure the A6 
  easyA6.begin(); 
  Serial.println("A6 Redy");

  // test signal quality
  int quality = easyA6.signalQuality();
  Serial.print("Signal quality: ");
  Serial.println(quality);

  if(quality > 18){
    //sendSMS(String number, String content)
    //Number example  "+49 123456789"
    easyA6.sendSMS("+XXxxxxxxxx", "Message");
    Serial.println("SMS SEND");

  }
}

void loop() {
  // put your main code here, to run repeatedly:



}
