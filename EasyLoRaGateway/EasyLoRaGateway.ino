// Include required EasyLoraGateway libraries
#include "EasyLoRaGateway.h"

// ===================================================
// Main Program
// ===================================================
// This runs once when the gateway boots. 
// The delay is not neccessary and just to avoid component re-initizalized by other compopents.
// setupXXX functions are placed in module files
void setup() {     

  //pinMode(0, OUTPUT);
  //digitalWrite(0, HIGH);
   
  //pinMode(2, OUTPUT);
  //digitalWrite(2, HIGH);
   
  //setupLED();  
  setupSerial();
  setupSpeaker();
  onOffSpeaker(1, false);   
  //setupFileSystem();
  setupWiFi();
  //setupEthernet();
  //delay(1000);
  setupMQTT();
  setupLoRa();   
  setupWebServer();
  //delay(10000);
  //setupOTA();
  //delay(1000);
  //displayLEDErrorCode();
  //setupPreferences();   
}

// Do the real works here
void loop() {  
  // Working
  receiveAndForwardLoRaMessage();
  processMQTTMessages();
  runWebServer();
  
  // TODO: When to accept OTA update?
  //waitingForOTA();
}

// Need to flush buffer to send or receive MQTT messages
void processMQTTMessages() {
  // Send / receive from MQTT buffer
  flushMQTTBuffer();
}

// Receive LoRa message and send to MQTT Server
void receiveAndForwardLoRaMessage(){
  String message = receiveLoRaMessage();
  if(message != ""){    
    forwardNodeMessageToMQTT(message);
    dataReceivedLED();
  }
}

