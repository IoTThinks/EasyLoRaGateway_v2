// ===================================================
// Put all pin mappings and library here
// ===================================================
// Serial
#define BAUD_RATE 9600

// Filesystem
#include "FS.h"
#include "SPIFFS.h"

// Preferences
#include <Preferences.h>
/* create an instance of Preferences library */
Preferences preferences;
unsigned int reset_times;

// Ethernet
#define ETH_PHY_MDIO 0
#define ETH_PHY_ADDR 1
#define ETH_PHY_MDC 16
#define ETH_PHY_POWER 33 // LAN_RST, too
#define ETH_PHY_TYPE ETH_PHY_LAN8720
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
//#define LAN_RST   33

// Must be after #define
#include <ETH.h>

// =====================
// MQTT
// =====================
#include <MQTT.h>

// =====================
// LoRa
// =====================
#include <SPI.h>
#include <LoRa.h>

// LoRa pins
#define LORA_SS   23
#define LORA_SCK   18
#define LORA_MOSI  5
#define LORA_MISO  36
#define LORA_DIO012      39
#define LORA_RST  13

// LoRa signals
#define LORA_SF 12 // 7 is the fastest. 12 is is farthest
#define LORA_CR 5
#define LORA_BW 125E3
#define LORA_PREAMBLE_LENGTH  8

// =====================
// OTA
// =====================
#include <ArduinoOTA.h>

// =====================
// rOTA
// =====================
#include <HttpFOTA.h>

// LED
#define LED 1 // UART0-TXD
#define LED_PWR_INT // UART0-RXD

// Button
#define BTN 35
boolean wifistatus = true;

// Speaker
#define SPK 12
#define SPK_CHANNEL 0
#define SPK_FREQ  800
#define SPK_RESOLUTION  8

//wifi
#include <WiFi.h>
#include <DNSServer.h>
String WEBSERVER_Status = "Not Initialized";
WiFiServer webServer(80);
WiFiClient webClient = webServer.available();

//GUI
String GUI_LoRaEvents = "";
String GUI_SenssorEvents = "";
String GUI_PowerEvents = "";

//HTML
String statusHTML = ""
"<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Easy Lora Gateway</title>"
"<style type=\"text/css\"> .header { padding: 24px; text-align: center; background: #58c3ef; color: white; font-size: 20px; } .topnav { background-color: #333; overflow: hidden; } .topnav a { float: left; color: #f2f2f2; text-align: center; padding: 14px 16px; text-decoration: none; font-size: 17px; } .topnav a:hover { background-color: #ddd; color: black; } .topnav a.active { background-color: #58c3ef; color: white; } .btn { background-color: DodgerBlue; border: none; color: white; padding: 12px 30px; cursor: pointer; font-size: 20px; } .btn:hover { background-color: RoyalBlue; } </style>"
"</head>"
"<body>"
"<div class=\"header\">"
"<h1>Easy Lora Gateway</h1>"
"</div>"
"<div class=\"topnav\"> <a class=\"active\" href=\"#Status\">Status</a> <a href=\"#nSensor\">Sensor</a> <a href=\"#Power\">Power</a> <a href=\"#Setting\">Setting</a> </div>"
"<p><b>Overview</b><br></p>"
"<p>ID: 1</p>"
"<p>LAN IP:   191.68.10.10</p>"
"<p>Internet: Connected / Disconnected</p>"
"<p>MQTT: Connected / Disconnected<br></p>"
"<p><b>LoRa events</b></p>"
"<p>" + GUI_LoRaEvents + "<br></p>"
"<p><b>Sensor events</b></p>"
"<p>" + GUI_SenssorEvents + "<br></p>"
"<p><b>Power events</b></p>"
"<p>" + GUI_PowerEvents + "<br></p>"
"<button class=\"btn\" value=\"Refresh\" onClick=\"window.location.reload();\">Refresh</button>"
"</body>"
"</html>";

String sensorHTML ="<!DOCTYPE html> <html> <head> <title>Easy Lora Gateway</title> <style type=\"text/css\"> .header { padding: 24px; text-align: center; background: #58c3ef; color: white; font-size: 20px; } /* Add a black background color to the top navigation */ .topnav { background-color: #333; overflow: hidden; } /* Style the links inside the navigation bar */ .topnav a { float: left; color: #f2f2f2; text-align: center; padding: 14px 16px; text-decoration: none; font-size: 17px; } /* Change the color of links on hover */ .topnav a:hover { background-color: #ddd; color: black; } /* Add a color to the active/current link */ .topnav a.active { background-color: #58c3ef; color: white; } /* Style buttons */ .btn { background-color: #58c3ef; border: none; color: white; padding: 12px 12px; cursor: pointer; font-size: 15px; text-align: center; } /* Darker background on mouse-over */ .btn:hover { background-color: RoyalBlue; } .row { display: flex; } .column { flex: 80%; text-align: left; } .columnr { text-align: right; padding-right: 2em; flex: 50%; } .btncontain { text-align: left; } </style> </head> <body> <div class=\"header\"> <h1>Easy Lora Gateway</h1> </div> <div class=\"topnav\"> <a href=\"#Status\">Status</a> <a class=\"active\" href=\"#Sensor\">Sensor</a> <a href=\"#Power\">Power</a> <a href=\"#Setting\">Setting</a> </div> <p><b>RS485 Sensor</b></p> <div class=\"row\"> <div class=\"columnr\"> <p>Register address (in Hex)</p> </div> <div class=\"column\"> <br><input type=\"text\" name=\"RegisterAddress\"><br> </div> </div> <div class=\"row\"> <div class=\"columnr\"> <p>Data length (in Bytes)</p> </div> <div class=\"column\"> <br><input type=\"text\" name=\"Data Lenght\"> </div> </div> <br> <br> <div class=\"btncontain\"> <button class=\"btn\" value=\"Save\" onClick=\"SaveGUIRS485Sensor();\">Save</button> </div> </body> </html>";

String powerHTML ="<!DOCTYPE html> <html> <head> <title>Easy Lora Gateway</title> <style type=\"text/css\"> .header { padding: 24px; text-align: center; background: #58c3ef; color: white; font-size: 20px; } /* Add a black background color to the top navigation */ .topnav { background-color: #333; overflow: hidden; } /* Style the links inside the navigation bar */ .topnav a { float: left; color: #f2f2f2; text-align: center; padding: 14px 16px; text-decoration: none; font-size: 17px; } /* Change the color of links on hover */ .topnav a:hover { background-color: #ddd; color: black; } /* Add a color to the active/current link */ .topnav a.active { background-color: #58c3ef; color: white; } /* Style buttons */ .btn { background-color: #58c3ef; border: none; color: white; padding: 12px 12px; cursor: pointer; font-size: 15px; text-align: center; } /* Darker background on mouse-over */ .btn:hover { background-color: RoyalBlue; } .row { display: flex; } .column { flex: 60%; text-align: left; } .columnr { text-align: left; padding-right: 2em; flex: 50%; } .btncontain { text-align: left; } </style> </head> <body> <div class=\"header\"> <h1>Easy Lora Gateway</h1> </div> <div class=\"topnav\"> <a href=\"#Status\">Status</a> <a href=\"#Sensor\">Sensor</a> <a class=\"active\" href=\"#Power\">Power</a> <a href=\"#Setting\">Setting</a> </div> <br> <div class=\"row\"> <div class=\"columnr\"> Select Power mode and click Save </div> <div class=\"column\"> <form> <select name = \"dropdown\"> <option value = \"Automatic\" selected>Automatic</option> <option value = \"Force ON\">Force ON</option> <option value = \"Force OFF\">Force OFF</option> </select> </form> </div> </div> <br> <br> <div class=\"btncontain\"> <button class=\"btn\" value=\"Save\" onClick=\"SaveGUIRS485Sensor();\">Save</button> </div> </body> </html>";

String settingHTML ="<!DOCTYPE html> <html> <head> <title>Easy Lora Gateway</title> <style type=\"text/css\"> .header { padding: 24px; text-align: center; background: #58c3ef; color: white; font-size: 20px; } /* Add a black background color to the top navigation */ .topnav { background-color: #333; overflow: hidden; } /* Style the links inside the navigation bar */ .topnav a { float: left; color: #f2f2f2; text-align: center; padding: 14px 16px; text-decoration: none; font-size: 17px; } /* Change the color of links on hover */ .topnav a:hover { background-color: #ddd; color: black; } /* Add a color to the active/current link */ .topnav a.active { background-color: #58c3ef; color: white; } /* Style buttons */ .btn { background-color: #58c3ef; border: none; color: white; padding: 12px 12px; cursor: pointer; font-size: 15px; text-align: center; } /* Darker background on mouse-over */ .btn:hover { background-color: RoyalBlue; } .row { display: flex; } .column { flex: 80%; text-align: left; } .columnr { text-align: right; padding-right: 2em; flex: 20%; } .btncontain { text-align: left; } </style> </head> <body> <div class=\"header\"> <h1>Easy Lora Gateway</h1> </div> <div class=\"topnav\"> <a href=\"#Status\">Status</a> <a href=\"#Sensor\">Sensor</a> <a href=\"#Power\">Power</a> <a class=\"active\" href=\"#Setting\">Setting</a> </div> <div class=\"row\"> <div class=\"columnr\"> <p>ID</p> </div> <div class=\"column\"> <br><input type=\"text\" name=\"ID\"><br> </div> </div> <div class=\"row\"> <div class=\"columnr\"> <p>Secret</p> </div> <div class=\"column\"> <br><input type=\"text\" name=\"Secret\"> </div> </div> <div class=\"btncontain\"> <button class=\"btn\" value=\"Save\" onClick=\"SaveGUIRS485Sensor();\">Save</button> </div> </body> </html>";
