#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#define FIREBASE_HOST "smart-sound-system.firebaseio.com"
#define FIREBASE_AUTH "hd9tSW92zM3qCx10SqTxYIC22Hppjg20ruxmOslV"
#define WIFI_SSID "MEO-87F0F4"
#define WIFI_PASSWORD "UC75RM7JJ2"

String myString;
int button_up = 2; // button connected to D4
int button_down = 5; // button connected to D1
int sensor = 13; // button connected to D7
int buttonState_up=0;
int buttonState_down=0;

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(button_up ,INPUT);
  pinMode(button_down ,INPUT);
  pinMode(sensor ,INPUT);
  pinMode(D0,OUTPUT);
  
  // connect to wifi and show ip
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  //Firebase connection
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop()
{

 buttonState_up=digitalRead(button_up); // read button state up
 buttonState_down=digitalRead(button_down); // read button state down
 long state=digitalRead(sensor); // read motion sensor state

 //Motion sensor
 if(state == HIGH) {
  myString = "LEFT"; 
  Serial.println(myString); 
  Firebase.pushString("Instructions/",myString);
  state=0;
  //delay of 1 sec
  delay(1000);
  state = LOW;
 }

 //UP button
 if (buttonState_up == 1)
 {
 myString = "UP"; 
 Serial.println(myString); 
 Firebase.pushString("Instructions/",myString);
 //delay of 1 sec
 delay(1);
 //delay(200);
 buttonState_up = 0;
 }

 //DOWN button
 if (buttonState_down == 1)
 {
 myString = "DOWN"; 
 Serial.println(myString); 
 Firebase.pushString("Instructions/",myString);
 //delay of 1 sec
 delay(1);
 //delay(200);
 buttonState_down = 0;
 }

 // Check for firebase communication errors
 if (Firebase.failed())
 {
  Serial.print("setting /number failed:");
  Serial.println(Firebase.error());
  delay(200);
  return;
  }

 
}
