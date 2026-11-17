#include <Wire.h> // I2C lib
#include <Adafruit_BMP5xx.h> // barometer lib
// https://github.com/adafruit/Adafruit_BMP5xx/blob/main/examples/bmp5xx_test/bmp5xx_test.ino
#include <SparkFun_VL53L5CX_Library.h>
// https://github.com/sparkfun/SparkFun_VL53L5CX_Arduino_Library/blob/main/examples/Example1_DistanceArray/Example1_DistanceArray.ino

Adafruit_BMP5xx barometer; // Address: 0x47

SparkFun_VL53L5CX tof; // Address: 0x29
VL53L5CX_ResultsData tofData;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Wire.begin(8, 9); // starts I2C bus

  Serial.println("Initializing ToF (up to 10s)");
  if (!tof.begin()) {
    Serial.println("ToF not found");
    while (1) ;
  }

  tof.setResolution(64);
  tof.startRanging();

  Serial.println("ToF setup complete");

  /*
  if (!barometer.begin(BMP5XX_DEFAULT_ADDRESS, &Wire)) {
    Serial.println("Barometer not found");
    while (1) ;
  }
  */
}

void loop() {
  /*
  barometer.performReading();
  // substitute pressure reading with altitude since barometer already calculates it internally.
  // float pressure = barometer.pressure; // unit is hPa
  // Serial.printf("pressure = %.2f hPa\n", pressure);

  float altitude = barometer.altitude;
  Serial.printf("altitude = %.f meters\n", altitude);
  */

  if (tof.isDataReady() && tof.getRangingData(&tofData) ) {
    Serial.print("["); 
    for (int i = 0; i < 64; i++) {
      Serial.print(tofData.distance_mm[i]);
      if (i != 63) Serial.print(",");
    }
    Serial.println("]");
  }
  
  delay(1000);
}
