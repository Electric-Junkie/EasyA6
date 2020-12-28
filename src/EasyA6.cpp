

#include "Arduino.h"
#include "EasyA6.h"


EasyA6::EasyA6(byte rxPin, byte txPin, int baudrate, const char* APN)
  : m_rxPin(rxPin), m_txPin(txPin), m_baudrate(baudrate), m_APN(APN), m_serialA6(rxPin, txPin) { }

EasyA6::EasyA6(byte rxPin, byte txPin, int baudrate)
  : m_rxPin(rxPin), m_txPin(txPin), m_baudrate(baudrate), m_APN(NULL), m_serialA6(rxPin, txPin) { }


void EasyA6::begin(){
  m_serialA6.begin(115200);
  delay(1000);
  command("AT");
  command("AT+IPR=9600");

  m_serialA6.begin(m_baudrate);
  delay(1000);
  command("AT");
  command("AT"); 

  //Set SMS 
  command("AT+CNMI=1,2,0,0,0");
  command("AT+CMGF=1");

  //Set TCP 
  command("AT+CGATT=1");
  command("AT+CGDCONT=1,\"IP\",\""+ String(m_APN) +"\""); 
  command("AT+CGACT=1,1");

}


String EasyA6::command(String command) {
  //Serial.println(command); 
  m_serialA6.println(command);
  delay(10);
  return read(); 

}


String EasyA6::read() {
  String response = "";

  while (!(m_serialA6.available())){
    delay(1);
  }
  
  if (m_serialA6.available()) {
    response = m_serialA6.readString();
  }

  if (response.indexOf("+CIEV:") > 0) {
    m_reservedResponse[m_reservedResponseSize] = response;
    m_reservedResponseSize++;
  }

  
  //Serial.print("response: ");
  //Serial.println(response);
  //Serial.println("response ende");

  return response;

}

String EasyA6::readSMS(){
  read();

  if (m_reservedResponseSize >= 1) {
    if (m_reservedResponse[m_reservedResponseSize - 1].indexOf("+CIEV:") > 0) {
      int index = m_reservedResponse[m_reservedResponseSize - 1].lastIndexOf("\"");
      String smsMessage = m_reservedResponse[m_reservedResponseSize - 1].substring(index+3);
      m_reservedResponseSize--;
      command("at+cmgd=1");
      return smsMessage;
    }
    
  }
  
}


String EasyA6::sendSMS(String number, String content){
  command("AT+CMGS=\""+String(number)+"\"");
  m_serialA6.print(content);
  m_serialA6.write(26);

  return read();;
}

int EasyA6::signalQuality(){
  String response = command("AT+CSQ");
  int index = response.indexOf("+CSQ", 6);
  int qualitiy = response.substring(index+6, index+11).toInt()+1;

  return qualitiy;

}

String EasyA6::postRequest(String host, String path, String body){
  return httpRequest("POST", host, path, "80", "application/x-www-form-urlencoded", body);
}



String EasyA6::httpRequest(String method, String host, String path, String port, String Content_Type, String body){

 
  command("AT+CIPSTART=\"TCP\",\"" + host + "\","+ port); 
  command("AT+CIPSEND"); 
  m_serialA6.print(method);
  m_serialA6.print(" "+ path);
  m_serialA6.print(" HTTP/1.1");
  m_serialA6.print("\r\n");
  m_serialA6.print("HOST: ");
  m_serialA6.print(host);
  m_serialA6.print("\r\n");
  m_serialA6.print("Content-Length: " + String(body.length()));
  m_serialA6.print("\r\n");
  m_serialA6.print("Content-Type: " + Content_Type);
  m_serialA6.print("\r\n");
  m_serialA6.print("\r\n");
  m_serialA6.print(body);
  m_serialA6.write(26);

  m_serialA6.println("AT+CIPSTATUS");
   
  String reply = "";
  do {
    reply = read();
  } while ((reply.indexOf("OK") == -1));
 
  delay(10);
  command("AT+CIPCLOSE"); 

  return reply;
}



