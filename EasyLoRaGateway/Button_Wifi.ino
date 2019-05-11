long buttonTimer = 0;
long longPressTime = 5000;

boolean buttonActive = false;
boolean longPressActive = false;
void setupBTN() {
  pinMode(BTN, INPUT);
}

void runBTN() {
  if (digitalRead(BTN) == HIGH) 
  {
    if (buttonActive == false) 
    {
      buttonActive = true;
      buttonTimer = millis();
    }
    if ((millis() - buttonTimer > longPressTime) && (longPressActive == false)) 
    {
      longPressActive = true;
      Serial.println("Factory resetted");
    }
  } 
  else 
  {
    if (buttonActive == true) 
    {
      if (longPressActive == true) 
      {
        longPressActive = false;
      } 
      else 
      {
        if (wifistatus == false)
        {
          delay(2000);
          setupCaptivePortal();
          wifistatus = true;
        }
        else
        {
          WiFi.disconnect(); 
          WiFi.mode(WIFI_OFF);
          //WiFi.forceSleepBegin();
          delay(1);
          wifistatus = false;
        }
        }
      }
      buttonActive = false;
    }

}
