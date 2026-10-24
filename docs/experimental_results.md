# Experimental results and observations

This record is reconstructed from lab notes and Serial Monitor screenshots shared during the project. It distinguishes **observed output**, **reported approximate values**, and **unverified tests**. It is not a substitute for a saved oscilloscope trace or a controlled measurement log.

## 1. I²C device detection — observed

- Controller: Arduino UNO
- Sensor: MPU6050 / GY-521 breakout
- Detected 7-bit I²C address: **`0x68`**
- Initial attempts failed to find the device, with intermittent I²C error codes. A later scan detected `0x68`, after which accelerometer readings were obtained.

## 2. Accelerometer readings — observed

The following **raw counts** were transcribed from a shared Serial Monitor screenshot while the sensor was stationary. They are not calibrated acceleration in m/s² or g.

| Sample | AX | AY | AZ |
|---:|---:|---:|---:|
| 1 | 136 | 196 | 15004 |
| 2 | 188 | 256 | 15048 |
| 3 | 220 | 248 | 14984 |
| 4 | 172 | 224 | 15192 |
| 5 | 84 | 216 | 14852 |
| 6 | 116 | 228 | 14964 |
| 7 | 212 | 256 | 15136 |
| 8 | 60 | 120 | 14956 |
| 9 | 88 | 224 | 15092 |
| 10 | 32 | 248 | 14960 |
| 11 | 8 | 192 | 14908 |
| 12 | 72 | 356 | 14924 |
| 13 | 4 | 276 | 14772 |

Interpretation: AX and AY were close to zero compared with AZ, which remained around 15,000 raw counts in this orientation. The exact gravity scale depends on the configured accelerometer range; do not claim a calibrated value without confirming the range and calibration.

## 3. Clock frequency experiments — reported, not fully documented

- A nominal **200 kHz** I²C setting was used in code (`Wire.setClock(200000)`). This is a **requested** SCL frequency, not proof of the actual measured SCL frequency.
- During the broader project, approximate **178–200 kHz** SCL observations were reported. No matching saved oscilloscope trace, instrument settings, or timestamped measurement table is available in this repository, so treat this as an **approximate recollection**, not a verified final result.
- Pull-up combinations involving **3.3 kΩ and 5.6 kΩ** were also tried; an approximately **303 kHz** result was reported during experimentation. A photograph now documents a bottom automatic measurement of 304.33 kHz (period 3.29 µs), with a conflicting top-right frequency readout of 30.6269 kHz. The exact resistor placement, programmed clock, and repeatability remain unknown. It is **not** evidence that the resistors alone increased the clock frequency.
- The maximum stable bus frequency has **not** been established.

## 4. Troubleshooting observations

- Before reliable sensor detection, the Serial Monitor repeatedly showed **`Register yazma hatası: 2`** (I²C address NACK in the Wire library's usual status mapping).
- An intermittent **error 4** was also reported, along with an occasional incomplete-data message when the unsoldered sensor board was moved.
- These observations are consistent with possible contact/wiring problems but do not prove a unique root cause.
- After connections were improved, the sensor was detected and nonzero accelerometer readings were observed.

## 5. Not yet measured or validated

- ESP32-S3 successful sensor readout and oscilloscope results
- Motor/driver running alongside I²C communication
- Before/after EMI waveforms or bit-error/read-error rates
- A controlled pull-up resistor comparison
- Exact maximum reliable I²C frequency

## 6. Recommended measurement protocol

For each configuration: record board, supply and logic levels, requested clock, **measured** SCL frequency and rise time, pull-up resistance on each line (including onboard resistors), wire length, and number of successful/failed transactions. Repeat with motor off/on only after verifying safe motor-driver wiring. Save oscilloscope screenshots with filenames identifying the test condition.

## 7. Photographic evidence

See the README gallery and the `images/` directory for the four original oscilloscope captures. Probe channel indicated 1X in the 304.33 kHz image, but physical probe attenuation was not confirmed. Recorded voltage amplitudes should not be treated as calibrated bus levels without probe verification.
