#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// =================================
// Define your sensor pin in here
#define lamp1 16
#define lamp2 5
#define lamp3 4
#define ldrPin A0
//====================================

// Configure for wifi connection
const char* wlanName = "KEDAI DJENGGOT $$$";
const char* wlanPassword = "iniibubudi";

// Delay or millis
unsigned long lastMsg = 0;

// Define configure for mqtt broker
const char* brokerAddress = "ec2-3-86-238-120.compute-1.amazonaws.com";
const char* brokerUsername = "jti";
const char* brokerPassword = "password";

// Declare instance for wificlient
WiFiClient espClient;
PubSubClient client(espClient);

// mqtt callbacrk
void callback(char* topic,byte* payload,unsigned int length);

// function for mqtt if disconnected will reconnect
void reconnect() {
  // Reconnect if connection lost...
  Serial.println("In Reconnect....");

  while (!client.connected()){
    Serial.print("Attempting mqtt connection....");
    if (client.connect("lampard",brokerUsername, brokerPassword)) {
      Serial.println("Connected");
      client.subscribe("street_lamp");
    }else{
      Serial.print("failed,");
      // Show state mqtt broker
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
  
}

// Broker callback
void callback(char*  topic,byte* payload,unsigned int length) {
  String tempPayload;
  for (int i=0; i < length; i++) {
    // Store payload to tempPayload
    tempPayload += (char)payload[i];
  }
  if (tempPayload == "lamp1/on") {
    Serial.println("==================");
    Serial.println("Lamp-1 Status: ON");
    Serial.println("Topic Message "+tempPayload);
    Serial.println("==================");
    pinMode(lamp1, OUTPUT);
  }
  if (tempPayload == "lamp1/off") {
    Serial.println("==================");
    Serial.println("Lamp-1 Status: OFF");
    Serial.println("Topic Message "+tempPayload);
    Serial.println("==================");
    pinMode(lamp1, INPUT);
  }
  if (tempPayload == "lamp2/on") {
    Serial.println("==================");
    Serial.println("Lamp-2 Status: ON");
    Serial.println("Topic Message "+tempPayload);
    Serial.println("==================");
    pinMode(lamp2, OUTPUT);
  }
  if (tempPayload == "lamp2/off") {
    Serial.println("==================");
    Serial.println("Lamp-2 Status: OFF");
    Serial.println("Topic Message "+tempPayload);
    Serial.println("==================");
    pinMode(lamp2, INPUT);
  }
  if (tempPayload == "lamp3/on") {
    Serial.println("==================");
    Serial.println("Lamp-3 Status: ON");
    Serial.println("Topic Message "+tempPayload);
    Serial.println("==================");
    pinMode(lamp3, OUTPUT);
  }
  if (tempPayload == "lamp3/off") {
    Serial.println("==================");
    Serial.println("Lamp-3 Status: OFF");
    Serial.println("Topic Message "+tempPayload);
    Serial.println("==================");
    pinMode(lamp3, INPUT);
  }
  // Validation if empty request 
  if (tempPayload == "") {
    Serial.println("==================");
    Serial.println("Topic Message message not found");
    Serial.println("==================");
  }
}

void setup(){
  
  Serial.begin(9600);
  pinMode(ldrPin,INPUT);
  
  // Declare wifi config
  WiFi.begin(wlanName,wlanPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("#");
  }
  Serial.println("");
  Serial.println("Connected");

  // Set server broker
  client.setServer(brokerAddress,1883);
  client.setCallback(callback);
}

void loop() {  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  // Delay
  unsigned long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    int ldrStatus = analogRead(ldrPin);
    char cstr[16]; // convert to char
    itoa(ldrStatus, cstr, 10); // int to string
    client.publish("topic",cstr); // send to mqtt
    
     // Logic for turn on lamp
     // Comment saja jika lampu nggak mau mati
    if (ldrStatus < 365) {
      pinMode(lamp1, INPUT);
      pinMode(lamp2, INPUT);
      pinMode(lamp3, INPUT);
    }else {
      pinMode(lamp1, OUTPUT);
      pinMode(lamp2, OUTPUT);
      pinMode(lamp3, OUTPUT);
    }
    
  }
} 
