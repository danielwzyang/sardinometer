#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000); // Gives native USB (/dev/ttyACM0) time to connect

  WiFi.mode(WIFI_STA);
  delay(100);  // Gives the Wi-Fi driver time to load the MAC address

  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {}
