#include <Wire.h>

// Update pins to match the actual ESP32-S3 development board wiring.
const int SDA_PIN = 8;
const int SCL_PIN = 9;
const uint8_t MPU_ADDR = 0x68;
const uint32_t I2C_CLOCK_HZ = 200000;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(I2C_CLOCK_HZ);
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00);
  Serial.println(Wire.endTransmission() == 0 ? "MPU6050 initialized" : "MPU6050 not responding");
}
void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  if (Wire.endTransmission(false) == 0 && Wire.requestFrom(MPU_ADDR, (uint8_t)6) == 6) {
    int16_t ax = (int16_t)((Wire.read() << 8) | Wire.read());
    int16_t ay = (int16_t)((Wire.read() << 8) | Wire.read());
    int16_t az = (int16_t)((Wire.read() << 8) | Wire.read());
    Serial.printf("AX: %d | AY: %d | AZ: %d\n", ax, ay, az);
  } else Serial.println("I2C read error");
  delay(100);
}
