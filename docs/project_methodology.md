# Project rationale and methodology

## Research hypothesis

As I²C clock speed increases, available settling time decreases. With a sufficiently capacitive bus or unsuitable pull-up network, slower rising edges may reduce timing margin and increase read failures. A nearby stepper driver is a plausible source of switching noise, but **whether it causes errors in this particular setup remains to be tested**.

## Why use acceleration samples as a communication check?

A valid sensor address followed by repeated 6-byte register reads gives a simple end-to-end check of the I²C transaction. The acceleration data are not a standalone electrical signal-integrity measurement: plausible samples do not prove that all transactions succeed, and raw count variation cannot be attributed to EMI without controlled comparisons.

## Interpretation of recorded results

Thirteen previously recorded AX/AY/AZ triples show a Z-axis mean of 14,984 raw counts and much smaller X/Y means. The data suggest an approximately stationary sensor in one orientation. No calibration, full-scale register readback, or temperature record is available. The observed samples demonstrate data retrieval, not sensor accuracy or maximum I²C performance.

## Planned quantitative EMI protocol

1. Verify the motor driver power, current limit, motor coil pairs, and input polarity with the power disconnected.
2. Fix the same I²C wires, sensor position, pull-up network, clock setting, and read interval for all trials.
3. Record at least a defined number of attempted reads with the motor driver off; count failures and save scope traces.
4. Repeat with the motor driver running and document its pulse rate, current setting, and cable separation.
5. Repeat each condition several times and calculate `read_failure_rate = failed_reads / attempted_reads`.
6. Compare error rates, rise times, and waveforms; do not claim causation from one screenshot alone.

## Evidence grading

- **Observed:** Arduino detected `0x68` and produced 13 recorded acceleration triples.
- **Reported approximate:** ~178–200 kHz and ~303 kHz observations without retained matched scope traces.
- **Unverified:** ESP32-S3 success, stable maximum frequency, controlled pull-up effects, motor EMI impact.
