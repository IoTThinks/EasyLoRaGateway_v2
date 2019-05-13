void getGUIStatusHTML() 
  {
    webClient.println(statusHTML);
  }

void getGUISensorHTML(String registerAdd, String dataLength)
{
      webClient.println(sensorHTML);
}

void getGUIPowerHTML(String )
{
      webClient.println(powerHTML);
}

void getGUIISettingsHTML(String id,String secret) 
{
      webClient.println(settingHTML);
}
