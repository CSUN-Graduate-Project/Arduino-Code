/************************************************************************

  Test of Pmod TMP3

*************************************************************************

  Description: Pmod_TMP3
  The ambient temperature (in ° F and ° C) is displayed in the serial monitor.


  Material
  1. Arduino Uno
  2. Pmod TMP3  (set jumpers JP1, JP2 and JP3 on GND)

  Wiring
  Module<----------> Arduino
  VCC     to        3V3
  GND     to        GND
  SCL     to        A5 (SCL)
  SDA     to        A4 (SDA)

************************************************************************/

#include <Wire.h> // call library
#define adress 0x48 // I2C adress of Pmod TMP3 module (without jumpers JP1, JP2, JP3)

void setup() {
  Serial.begin(9600); // initialization of serial communication
  Wire.begin(); // initialization of I2C communication
  TMP3_init(); // initialization of Pmod TMP3
}

void loop() {
  //measure and display data
  Serial.print("Temperature in F = ");
  Serial.print(TMP3_getTemp_F());
  Serial.print('\t');  //tabulation
  Serial.print("Temperature in °C = ");
  Serial.println(TMP3_getTemp_C());
  delay(1000);
}

//get temperature in degrees Celsius
float TMP3_getTemp_C(void) {
  // Launch of the measurement
  Wire.beginTransmission(adress);
  Wire.endTransmission();
  delay(10);

  //ask for measured data
  Wire.requestFrom(adress, 2);
  int tmp = (Wire.read() << 8) | Wire.read(); //retrieve data
  tmp >>= 4;  //use only 12-bits
  return (tmp / 16.00);
}

//get temperature in farenheit
float TMP3_getTemp_F(void) {
  return TMP3_getTemp_C() * 9 / 5 + 32.2;
}

// Initialization of Pmod TMP3 module
void TMP3_init(void) {
  //set 12-bit resolution
  Wire.beginTransmission(adress);
  Wire.write(0x01);
  Wire.write(0x60);
  Wire.endTransmission();

  //set address pointer
  Wire.beginTransmission(adress);
  Wire.write(0x00);
  Wire.endTransmission();
}
