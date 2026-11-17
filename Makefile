SKETCH = sardinometer
PORT = /dev/ttyACM0
FQBN = esp32:esp32:esp32s3:CDCOnBoot=cdc
RATE = 115200

setup:
	arduino-cli config set board_manager.additional_urls file:///$(CURDIR)/arduino_packages.json
	arduino-cli core update-index
	arduino-cli core install esp32:esp32
	arduino-cli lib install "SparkFun VL53L5CX Arduino Library" "Adafruit BMP5xx Library"

upload:
	arduino-cli compile --upload --fqbn $(FQBN) -p $(PORT) $(SKETCH)

monitor:
	arduino-cli monitor -p $(PORT) -c baudrate=$(RATE)

