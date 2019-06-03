void WiFiEvent(WiFiEvent_t event)
{  
  switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.print("[WiFi] WiFi connected. ");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("[WiFi] WiFi lost connection.  Attempting to reconnect...");
      WiFi.reconnect();
      break;
    case SYSTEM_EVENT_STA_START:
      Serial.println("[WiFi] WiFi station start");
      break;
    case SYSTEM_EVENT_STA_CONNECTED:
      Serial.println("[WiFi] WiFi station connected to AP");
      wifi_connected = true;
      break;
    case SYSTEM_EVENT_AP_START:
      Serial.println("[WiFi] WiFi AP start");
      break;
    default:      
      Serial.printf("[WiFi] Unhandled WiFi Event %d\n", event);       
      break;
  }
}

void setupWiFi()
{
    //disable brownout detector
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
    
    // delete old config
    WiFi.disconnect(true);
    delay(1000);

    WiFi.onEvent(WiFiEvent);

    WiFi.begin(ssid, password);
    Serial.println("[WiFi] Wait for WiFi...");
}

