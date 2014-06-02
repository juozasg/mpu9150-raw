#include "i2c.h"


uint8_t read_byte(int dev, int addr) {
  Wire.beginTransmission(dev);
  Wire.write(addr);
  Wire.endTransmission(false);

  Wire.requestFrom(dev, 1, true);
  return Wire.read();
}

void read_byte(int dev, int addr, uint8_t *buff) {
  Wire.beginTransmission(dev);
  Wire.write(addr);
  Wire.endTransmission(false);

  Wire.requestFrom(dev, 1, true);
  *buff = Wire.read();
}

void read_bytes(int dev, int addr, uint8_t *buff, uint8_t count) {
  Wire.beginTransmission(dev);
  Wire.write(addr);
  Wire.endTransmission(false);

  Wire.requestFrom(dev, count, true);
  for(uint8_t i = 0; i < count; i ++) {
    buff[i] = Wire.read();
  }
}

void read_word(int dev, int addr, int16_t *buff) {
  Wire.beginTransmission(dev);
  Wire.write(addr);
  Wire.endTransmission(false);

  Wire.requestFrom(dev, 2, true);
  *buff = Wire.read () << 8;
  *buff |= Wire.read();
}

void read_xyz(int dev, int addr, int16_t *buff) {
  Wire.beginTransmission(dev);
  Wire.write(addr);
  Wire.endTransmission(false);

  Wire.requestFrom(dev, 6, true);

  buff[0] = Wire.read () << 8;
  buff[0] |= Wire.read();

  buff[1] = Wire.read () << 8;
  buff[1] |= Wire.read();

  buff[2] = Wire.read () << 8;
  buff[2] |= Wire.read();
}



void write_byte(int dev, int addr, uint8_t data) {
  Wire.beginTransmission(dev);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission(true);
}

