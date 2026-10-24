#include <Wire.h>

const uint8_t MPU_ADDR = 0x68;
const uint32_t I2C_CLOCK_HZ = 200000;

bool writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.write(value);
  return Wire.endTransmission() == 0;
}

bool readAcceleration(int16_t &ax, int16_t &ay, int16_t &az) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  if (Wire.endTransmission(false) != 0) return false;
  if (Wire.requestFrom(MPU_ADDR, (uint8_t)6) != 6) return false;
  ax = (int16_t)((Wire.read() << 8) | Wire.read());
  ay = (int16_t)((Wire.read() << 8) | Wire.read());
  az = (int16_t)((Wire.read() << 8) | Wire.read());
  return true;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(I2C_CLOCK_HZ);
  if (!writeRegister(0x6B, 0x00)) Serial.println("MPU6050 initialization failed");
  else Serial.println("MPU6050 initialized");
}

void loop() {
  int16_t ax, ay, az;
  if (readAcceleration(ax, ay, az)) {
    Serial.print("AX: "); Serial.print(ax);
    Serial.print(" | AY: "); Serial.print(ay);
    Serial.print(" | AZ: "); Serial.println(az);
  } else Serial.println("I2C read error");
  delay(100);
}
