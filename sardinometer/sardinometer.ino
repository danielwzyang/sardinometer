#include <Wire.h> // I2C lib
#include <Adafruit_BMP5xx.h> // barometer lib
// https://github.com/adafruit/Adafruit_BMP5xx/blob/main/examples/bmp5xx_test/bmp5xx_test.ino

Adafruit_BMP5xx barometer;

void setup() {
  Serial.begin(115200);
  Wire.begin(); // starts I2C bus with default pins

  // BMP5XX_ALTERNATIVE_ADDRESS also exists? idk
  if (!barometer.begin(BMP5XX_DEFAULT_ADDRESS, &Wire)) {
    Serial.println("Barometer not found");
    while (1) delay(10);
  }
}

void loop() {
  barometer.performReading();
  float pressure = barometer.pressure; // unit is hPa

  Serial.printf("pressure = %.2f hPa", pressure);
  delay(1000);
}
