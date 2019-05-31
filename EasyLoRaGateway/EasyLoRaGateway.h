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

// Speaker
#define SPK 12
#define SPK_CHANNEL 0
#define SPK_FREQ  800
#define SPK_RESOLUTION  8

// WiFi
#include <WiFi.h>
const char* ssid     = "Optimum 2.4";
const char* password = "Password123;";
static bool wifi_connected = false;
