# EasyA6

Small library for the A6 GPRS modules. Includes examples for send/receive SMS and http requests.

**Dont use delay() combined with receiveing SMS and unlock your simcard for HTTP requests**

## Quickstart:

At the beginning create a object with the constructor 
```c++
//tx to D3, rx to D2, Baudrate, Set Your APN code
EasyA6 easyA6(3, 2, 9600, "APN"); 
```

The begin function connect the Arduino with the A6 module and set your baudrade (default is 115200) 
```c++
easyA6.begin(); 
```


### Send SMS
For sending a SMS use the sendSMS function with the phonenumber and your message as a string
```c++
//sendSMS(String number, String content)
//Number example  "+49 123456789"
easyA6.sendSMS("+XXxxxxxxxx", "Message");
```


### Receive SMS
For receiveing SMS use the readSMS function in the loop function. When you use this function don´t use delay, because this can distrub the serial communication.
```c++
String message = easyA6.readSMS();
```


### HTTP request
For HTTP requests use the httpRequest function with all paramteters as a string. 
```c++
//easyA6.httpRequest(methoden, hostUrl, path, port, Content-typ, body);
String response = easyA6.httpRequest("POST", "postman-echo.com","/post", "80", "application/x-www-form-urlencoded", "body");
```

For POST resquests you can the short version 
```c++
easyA6.postRequest(String host, String path, String body)
```