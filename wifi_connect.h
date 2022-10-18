#include <WiFi.h>

#define WIFI_LED 2

String ssid = "Galaxy" ;
String password = "mny1122286#" ;

void checkConnectivity() {
  // check for wifi for reconnect function
  //Serial.println("WIFI CHECK Time ");
  if (WiFi.status() == WL_CONNECTED) return ;
  digitalWrite(WIFI_LED , LOW );
  int tryCounts = 0;

  WiFi.disconnect();
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.println("try reConnecting ... ");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
    if (tryCounts ++ >= 10) break ; // try for 10 seconds only
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("");
    Serial.println("Connected again sucess ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    digitalWrite(WIFI_LED , HIGH);
  }
}

void connectWifi()
{
  WiFi.begin(ssid.c_str(), password.c_str());

  Serial.println("");
  int tryCount = 0 ;
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    tryCount ++ ;
    Serial.print(".");
    delay(500);

    if (tryCount > 30) {
      ESP.restart();
    }
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    digitalWrite(WIFI_LED , HIGH);
    Serial.println(WiFi.localIP());
  }
}
