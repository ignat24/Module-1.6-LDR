#include <Arduino.h>

constexpr uint8_t ANALOG_INPUT=7;
constexpr float V_max = 3.1;
constexpr uint16_t ADC_MAX = 4095;

float calculateVoltage(uint16_t RAWdata) {
  return (RAWdata / static_cast<float>(ADC_MAX)) * V_max;
}

float calculateError(float measured, float calculated) {
    if (measured == 0.0f) {
        return 0.0f;
    }

    return fabsf(measured - calculated) / measured * 100.0f;
}

void setup() {
  Serial.begin(115200);
  pinMode(ANALOG_INPUT, INPUT);
  analogReadResolution(12);
}

void loop() {
  delay(100);
  uint16_t RAWdata = analogRead(ANALOG_INPUT);
  uint32_t voltage_read = analogReadMilliVolts(ANALOG_INPUT);
  float voltage_calculated = calculateVoltage(RAWdata);
  float measuredVoltage = voltage_read / 1000.0f;
  float error = calculateError(measuredVoltage, voltage_calculated);

  Serial.printf(
    "RAW: %4u | Measured: %4lu mV | Calculated: %.3f V | Error: %.2f%%\n",
    RAWdata,
    (unsigned long)voltage_read,
    voltage_calculated,
    error
);
}