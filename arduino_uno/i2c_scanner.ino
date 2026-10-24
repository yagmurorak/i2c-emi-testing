#include <Wire.h>
void setup() { Serial.begin(115200); Wire.begin(); }
void loop() {
  Serial.println("Scanning I2C bus...");
  for (uint8_t address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Device found at 0x");
      if (address < 16) Serial.print('0');
      Serial.println(address, HEX);
    }
  }
  delay(2000);
}
