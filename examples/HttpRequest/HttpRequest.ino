#include<EasyA6.h>

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
    //easyA6.httpRequest(methoden, hostUrl, path, port, Content-typ, body);
    String response = easyA6.httpRequest("POST", "postman-echo.com","/post", "80", "application/x-www-form-urlencoded", "body");
    Serial.println("Response: ");
    Serial.println(response);
    
    //short version: postRequest(String host, String path, String body)
  }
}

void loop() {
  // put your main code here, to run repeatedly:



}
