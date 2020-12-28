
#ifndef EASYA6_HPP
#define EASYA6_HPP

#include "Arduino.h"
#include "String.h"
#include "SoftwareSerial.h"

class EasyA6 {
  
  private:
    byte m_txPin;
    byte m_rxPin;
    int m_baudrate;
    const char* m_APN;
    SoftwareSerial m_serialA6;

    String m_reservedResponse[10];
    int m_reservedResponseSize = 0;


  protected:
    String read();



  public:
    EasyA6(byte rxPin, byte txPin, int baudrate, const char* APN);
    EasyA6(byte rxPin, byte txPin, int baudrate);
    void begin();

    String command(String command);

    String readSMS();

    String sendSMS(String number, String content);

    String postRequest(String host, String path, String body);
    
    String httpRequest(String method, String host, String path, String port, String Content_Type, String body);

    int signalQuality();


};

#endif
