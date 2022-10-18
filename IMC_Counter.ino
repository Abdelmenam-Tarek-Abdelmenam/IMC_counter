#include "wifi_connect.h"
#include "requests.h"


void setup(void)
{
  Serial.begin(9600);
  pinMode(WIFI_LED, OUTPUT);
  connectWifi();
}
void loop() {
  checkConnectivity();
}
