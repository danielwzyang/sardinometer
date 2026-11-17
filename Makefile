SKETCH = sardinometer
PORT = /dev/ttyACM0
FQBN = esp32:esp32:esp32s3
RATE = 115200

setup:
	arduino-cli config add board_manager.additional_urls https://espressif.github.io/arduino-esp32/package_esp32_index.json
	arduino-cli core update-index
	arduino-cli core install esp32:esp32
	arduino-cli lib install "SparkFun VL53L5CX Arduino Library" "Adafruit BMP5xx Library"

run:
	arduino-cli compile --upload --fqbn $(FQBN) -p $(PORT) $(SKETCH)
	arduino-cli monitor -p $(PORT) -c baudrate=$(RATE)

monitor:
	arduino-cli monitor -p $(PORT) -c baudrate=$(RATE)

