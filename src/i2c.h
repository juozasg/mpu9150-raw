#include <Wire.h>
// typedef union {
//   uint8_t bytes[6];
//   int8_t byte;
//   int16_t word;
//   struct {
//     int16_t x0;
//     int16_t y0;
//     int16_t z0;
//   };
//   struct {
//     int16_t x1;
//     int16_t y1;
//     int16_t z1;
//   };
//   struct {
//     int16_t x2;
//     int16_t y2;
//     int16_t z2;
//   };
// } i2c_data;


// extern i2c_data read_data;
// extern uint8_t read_buff[6];


void read_byte(int dev, int addr, uint8_t  *buff);
uint8_t read_byte(int dev, int addr);
void read_bytes(int dev, int addr, uint8_t  *buff, uint8_t count);
void read_word(int dev, int addr, int16_t *buff);
void read_xyz(int dev, int addr, int16_t *buff); // read 3 words
void write_byte(int dev, int addr, uint8_t data);