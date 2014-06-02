#include <Arduino.h>
#include "constants.h"
#include "i2c.h"
void setup();
void setup_direct_access();
void setup_aux_access();
void loop();
void print_readings();
void print_accel();
void print_gyro();
void print_mag();
double convert_temp();
void rate();
#line 1 "src/mpu9150_raw.ino"
//#include "constants.h"
//#include "i2c.h"

int MPU = 0x68;
int MAG = 0x0C;

// i2c_data read_data;

// //Variables where our values can be stored
int16_t cmps[3];
int16_t accl[3];
int16_t gyro[3];
int16_t temp;
uint8_t data;

uint32_t sample_started = 0;
uint32_t now = 0;
volatile int samples = 0;


// void int_data_ready() {
  // read_xyz(MPU, ACCEL_XOUT_H, accl);
  // Serial.print(".");
  // Serial.println();
  // samples++;
// }

void setup()
{
  Serial.begin(115200);
  Wire.begin();


  write_byte(MPU, PWR_MGMT_1, 1); //turn on and use gyro osc for clock


  setup_direct_access();
  // pinMode(8, INPUT);
  // attachInterrupt(8, int_data_ready, CHANGE);

  // setup_aux_access();
}

void setup_direct_access() {
  write_byte(MPU, USER_CTRL, 0);        // disable master i2c mode
  write_byte(MPU, INT_PIN_CFG, 0x02);   // enable i2c bypass mode for ECL/EDA pins
  write_byte(MPU, INT_ENABLE, 0x0);    // data ready interrupt disable
  write_byte(MPU, ACCEL_CONFIG, 0x10);    // AFS_SEL = 2 (+- 8g)
  // write_byte(MPU, SMPLRT_DIV, 0xFF);    // slow it down

  // write_byte(MAG, MAG_CNTL, 0x02); // continuous read mode (where did i find this?)
}

void setup_aux_access() {
}

void loop()
{
  rate();
  // read_xyz(MPU, ACCEL_XOUT_H, accl);
  if(read_byte(MPU, INT_STATUS) & 0x01) {
    read_xyz(MPU, ACCEL_XOUT_H, accl);
    // Serial.print(".");
    samples++;
  }

  // read_word(MPU, TEMP_OUT_H,  &temp);
  // read_xyz(MPU, GYRO_XOUT_H, gyro);
  // if(read_byte(MAG, MAG_ST1) & 0x01) {
    // read_bytes(MAG, MAG_XOUT_L, (uint8_t*) cmps, 6); // mag is little endian
    // write_byte(MAG, MAG_CNTL, 0x01); // read value
    // Serial.print(".");

  // }

  print_readings();
}

void print_readings() {
  // Serial.print("T: ");
  // Serial.print(convert_temp());

  print_accel();
  print_accel();
  print_accel();
  // print_gyro();
  // print_mag();
  Serial.println();
}

void print_accel() {
  // Serial.print("     ACCEL: ");
  Serial.print(accl[0]);
  Serial.print(" ");
  Serial.print(accl[1]);
  Serial.print(" ");
  Serial.print(accl[2]);
}

void print_gyro() {
  Serial.print("     GYRO: ");
  Serial.print(gyro[0]);
  Serial.print(" ");
  Serial.print(gyro[1]);
  Serial.print(" ");
  Serial.print(gyro[2]);

}

void print_mag() {
  // Serial.print("     MAG: ");
  Serial.print(cmps[0]);
  Serial.print(" ");
  Serial.print(cmps[1]);
  Serial.print(" ");
  Serial.print(cmps[2]);
}

double convert_temp() {
  return ((double)temp + 12412.0) / 340.0;
}

void rate() {
  now = micros();
  if(sample_started == 0) sample_started = now;
  if(now - sample_started > 1000000) { // 1 second
    Serial.print("                                                                                ");
    Serial.print(((double) samples) * 1000000.0/(now - sample_started));
    Serial.print(" Hz");
    Serial.println();

    sample_started = 0;
    samples = 0;
  }
}
