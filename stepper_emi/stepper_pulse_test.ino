// Standalone STEP/DIR test. Do not run the motor without a correctly rated
// external driver supply and verified coil pairs/current limit.
const uint8_t STEP_PIN = 2;
const uint8_t DIR_PIN = 3;
const unsigned int HALF_PERIOD_US = 1000; // ~500 steps/s
void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(STEP_PIN, LOW);
  digitalWrite(DIR_PIN, HIGH);
}
void loop() {
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(HALF_PERIOD_US);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(HALF_PERIOD_US);
}
