#include <Wire.h> // I2C lib
#include <Adafruit_BMP5xx.h> // barometer lib
#include <SparkFun_VL53L5CX_Library.h> // tof lib
#include <config.h>

Adafruit_BMP5xx barometer;

float heights[FLOORS] = {0, 5, 9, 13, 16, 20, 24, 28, 33, 37, 41};
int floor_numbers[FLOORS] = {-2, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9};

SparkFun_VL53L5CX tof;
VL53L5CX_ResultsData tofData;

unsigned long prev_millis_bmp = 0;
unsigned long prev_millis_tof = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN); // starts I2C bus

  Serial.println("Initializing ToF (up to 10s)");
  if (!tof.begin()) {
    Serial.println("ToF not found");
    while (1) ;
  }

  tof.setResolution(TOF_RES);
  tof.setRangingFrequency(TOF_FREQ);
  tof.startRanging();

  Serial.println("ToF setup complete");

  if (!barometer.begin(BMP5XX_ALTERNATIVE_ADDRESS, &Wire)) {
    Serial.println("Barometer not found");
    while (1) ;
  }

  barometer.setTemperatureOversampling(BMP5XX_OVERSAMPLING_1X); // reduce overhead since we don't need temp
  barometer.setPressureOversampling(BMP5XX_OVERSAMPLING_8X); // average 8 consecutive samples to reduce noise

  prev_millis_bmp = millis();
  prev_millis_tof = millis();
}

float getAltitude() {
  barometer.performReading();
  // sea level altitude = 1013.25 Pa
  static float base_pressure = barometer.pressure;
  return barometer.readAltitude(base_pressure);
}

int getFloor(float altitude) {
  float min_dist = 1000; // arbitrary big number
  int floor = UNDEFINED_FLOOR;

  for (int i = 0; i < FLOORS; i++) {
    float dist = fabs(heights[i] - altitude);
    if (dist < min_dist) {
      min_dist = dist;
      floor = floor_numbers[i];
    }
  }

  return floor;
}

bool getTOFData() {
  return tof.isDataReady() && tof.getRangingData(&tofData);
}

void printTOFData() {
  // 1d array
  Serial.print("["); 
  for (int i = 0; i < TOF_RES; i++) {
    Serial.print(tofData.distance_mm[i]);
    if (i != TOF_RES - 1) Serial.print(",");
  }
  Serial.println("]");
}

void loop() {
  unsigned long cur_millis = millis();

  if (cur_millis - prev_millis_bmp >= BMP_MS) {
    prev_millis_bmp += BMP_MS;
    float altitude = getAltitude();
    Serial.printf("altitude = %.2f meters\n", altitude);
    int floor = getFloor(altitude);
    Serial.printf("floor = %d\n", floor);
  }

  if (cur_millis - prev_millis_tof >= TOF_MS && getTOFData()) {
    prev_millis_tof += TOF_MS;
    printTOFData();
  }
}
