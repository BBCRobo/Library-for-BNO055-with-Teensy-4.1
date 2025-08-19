/*
TEST PROGRAM for BNO055 using a Teensy 4.1 to print orientation

If you're using the GY-BNO055 breakout board, make sure you connect external
10k pullup resistors to the SCL and SDA pins.

The Adafruit BNO055 breakout board does NOT need external pullup resistors.

VIN  --> 3.3V
GND  --> GND
SCL  --> SCL
SDA  --> SDA
ADDR --> 3.3V (Address B)

Please note if the ADDR pin on the Adafruit BNO055 breakout board is left
floating, the address for the BNO will be BNO055_ADDRESS_A. If the pin is
pulled HIGH (3.3V), the address will be BNO055_ADDRESS_B. 

For the GY-BNO055, the address is always BNO055_ADDRESS_B unless other
soldering is done to the board.

For the bno.begin() function, pass the operation mode as a parameter. The 
OPERATION_MODE_IMUPLUS uses the sensor fusion but produces a higher output rate
when compared to other fusion modes.

Please also know the added library dependencies in platformio.ini:
lib_deps =
    adafruit/Adafruit BusIO
    SPI
*/
#include <Adafruit_BNO055.h>

// Change the address to BNO_ADDRESS_B if needed. Also change &Wire to &Wire1
// or &Wire2 depending on which I2C bus is being used.
Adafruit_BNO055 bno = Adafruit_BNO055(55, BNO055_ADDRESS_A, &Wire);


void setup() {
    Serial.println("Orientation Sensor Test");
    Serial.println();

    while(!bno.begin(OPERATION_MODE_IMUPLUS)) {
        Serial.println("No BNO055 detected. Check your wiring or I2C ADDR.");
        delay(1000);
    }
    delay(500);
    bno.setExtCrystalUse(true);
    delay(500);
}


void loop() {
    sensors_event_t event;
    bno.getEvent(&event);

    Serial.print("Orientation: ");
    Serial.print(event.orientation.x);
    Serial.print(" ");
    Serial.print(event.orientation.y);
    Serial.print(" ");
    Serial.print(event.orientation.z);
    Serial.println();
}
