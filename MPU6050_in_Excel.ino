#include <Wire.h>
#include <I2Cdev.h>
#include "MPU6050.h"

MPU6050 mpu(0x68);

const float fact = (2.0 * 9.8066) / 32768.0;
float ang_x, ang_y;
int16_t ax, ay, az;
int16_t gx, gy, gz;

void obtener_angulos(int16_t ax, int16_t ay, int16_t az) {

  ang_x = atan((ax * fact) / sqrt(pow((ay * fact), 2) + pow((az * fact), 2))) * (180.0 / 3.1416);
  ang_y = atan((ay * fact) / sqrt(pow((ax * fact), 2) + pow((az * fact), 2))) * (180.0 / 3.1416);
  
}

void setup() {
  
  Serial.begin(9600);

  Wire.begin();
  mpu.initialize(); 

  if(!mpu.testConnection()) {
    Serial.println("Fallo en incialización de MPU6050");
    return;
  }

}

void loop() {

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  //obtener_angulos(ax, ay, az);

  Serial.print(ax);
  Serial.print(",");
  Serial.print(ay);
  Serial.print(",");
  Serial.print(az);
  Serial.print(",");
  Serial.print(gx);
  Serial.print(",");
  Serial.print(gy);
  Serial.print(",");
  Serial.print(gz);
  Serial.print("\n");

  delay(100);

}
