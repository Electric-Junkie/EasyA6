#include<EasyA6.h>

//!!!!
// The Simcard must be unlockd!! (No PIN)
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

  
}

void loop() {
  String message = easyA6.readSMS();
  Serial.print("New message: ");
  Serial.println(message);



}
