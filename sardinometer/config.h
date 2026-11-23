#define SDA_PIN 8 // blue wire (data)
#define SCL_PIN 9 // yellow wire (clock)

#define TOF_RES 64

#define BMP_FREQ 5
#define BMP_MS 1000 / BMP_FREQ
#define TOF_FREQ 1
#define TOF_MS 1000 / TOF_FREQ

#define FLOORS 11
int heights[FLOORS] = {0, 5, 9, 13, 16, 30, 24, 28, 33, 37, 41};
int floor_numbers[FLOORS] = {-2, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
#define UNDEFINED_FLOOR 0