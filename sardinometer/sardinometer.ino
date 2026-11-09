#include <Wire.h> // I2C lib
#include <Adafruit_BMP5xx.h> // barometer lib
// https://github.com/adafruit/Adafruit_BMP5xx/blob/main/examples/bmp5xx_test/bmp5xx_test.ino
#include <SparkFun_VL53L5CX_Library.h>
// https://github.com/sparkfun/SparkFun_VL53L5CX_Arduino_Library/blob/main/examples/Example1_DistanceArray/Example1_DistanceArray.ino

Adafruit_BMP5xx barometer;

SparkFun_VL53L5CX tof;
VL53L5CX_ResultsData tofData;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Wire.begin(); // starts I2C bus with default pins

  Serial.println("Initializing ToF (up to 10s)");
  if (!tof.begin()) {
    Serial.println("ToF not found");
    while (1) ;
  }

  tof.setResolution(64);

  Serial.println("ToF setup complete");

  // BMP5XX_ALTERNATIVE_ADDRESS also exists? idk
  if (!barometer.begin(BMP5XX_DEFAULT_ADDRESS, &Wire)) {
    Serial.println("Barometer not found");
    while (1) ;
  }
}

void loop() {
  barometer.performReading();
  //substitue pressure reading with altitude since barometer already calculates it internally.
  //float pressure = barometer.pressure; // unit is hPa
  float altitude = barometer.altitude;
  Serial.printf("altitude = %.f meters\n", altitude);
  //Serial.printf("pressure = %.2f hPa\n", pressure);
  delay(1000);
}
