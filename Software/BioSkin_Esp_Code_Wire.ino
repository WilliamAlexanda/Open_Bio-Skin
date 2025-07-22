#include <Arduino.h>

// Pin Definitions
#define MUX_S0 1
#define MUX_S1 2
#define MUX_S2 3
#define MUX_S3 4
#define MUX_SIG 5 // Signal from MUX to ESP32-S3
#define MUX_EN 15 // MUX enable pin
#define HEATER_CTRL 6 // Heater control pin
#define STANDARD_SENSOR 10 // New standard sensor analog input

// Multiplexer control
uint8_t muxChannel[10] = {
  0b0000, 0b0001, 0b0010, 0b0011, 0b0100, 
  0b0101, 0b0110, 0b0111, 0b1000, 0b1001
};

// Sampling interval
const unsigned long samplingInterval = 5; // 10ms for 100Hz
const unsigned long heaterPeriod = 500; // 0.5 seconds in ms

unsigned long lastHeaterUpdate = 0;
int heaterDutyCycle = 0; // Duty cycle in percentage

void setup() {
  // Initialize Serial Monitor
  Serial.begin(250000);

  // Pin Modes
  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);
  pinMode(MUX_S3, OUTPUT);
  pinMode(MUX_EN, OUTPUT);
  pinMode(HEATER_CTRL, OUTPUT);
  pinMode(MUX_SIG, INPUT);
  pinMode(STANDARD_SENSOR, INPUT); // Configure the standard sensor pin as input

  // Enable multiplexer
  digitalWrite(MUX_EN, LOW);
  // Turn off heater initially
  digitalWrite(HEATER_CTRL, LOW);

  // Set ADC characteristics
  analogReadResolution(12); // Set ADC resolution to 12 bits
  analogSetAttenuation(ADC_11db); // Set attenuation to measure full range (0 - 3.3V)
}

void loop() {
  // Array to store analog readings
  int readings[11]; // Adjusted size to include standard sensor data

  // Loop through each channel of the multiplexer
  for (int i = 0; i < 10; i++) {
    selectMuxChannel(i);
    delayMicroseconds(100); // Allow settling time (0.1ms)
    readings[i] = analogRead(MUX_SIG);
    if (i == 9) { // Check the temperature channel
      adjustHeater(readings[i]);
    }
  }

  // Read the standard sensor data
  readings[10] = analogRead(STANDARD_SENSOR);

  // Send data over Serial
  sendDataSerial(readings);

  // Wait for next sample
  delay(samplingInterval);
}

void selectMuxChannel(int channel) {
  digitalWrite(MUX_S0, bitRead(muxChannel[channel], 0));
  digitalWrite(MUX_S1, bitRead(muxChannel[channel], 1));
  digitalWrite(MUX_S2, bitRead(muxChannel[channel], 2));
  digitalWrite(MUX_S3, bitRead(muxChannel[channel], 3));
}

void sendDataSerial(int *readings) {
  char data[64];
  int len = 0;

  // Format data as a compact comma-separated string
  for (int i = 0; i < 11; i++) {
    len += snprintf(data + len, sizeof(data) - len, "%d", readings[i]);
    if (i < 10) {
      len += snprintf(data + len, sizeof(data) - len, ",");
    }
  }

  // Send data via Serial
  Serial.println(data);
}

void adjustHeater(int temperatureAdcValue) {
  if (temperatureAdcValue < 1100) {
    heaterDutyCycle = 100; // Maximum duty cycle
  } else if (temperatureAdcValue >= 1100 && temperatureAdcValue < 2050) {
    heaterDutyCycle = map(temperatureAdcValue, 1100, 2100, 100, 0); // Linearly decrease duty cycle
  } else {
    heaterDutyCycle = 0; // Turn off heater
  }

  unsigned long currentTime = millis();
  unsigned long onTime = heaterPeriod * heaterDutyCycle / 100;
  unsigned long offTime = heaterPeriod - onTime;

  if (heaterDutyCycle > 0 && currentTime - lastHeaterUpdate < onTime) {
    digitalWrite(HEATER_CTRL, HIGH); // Heater ON
  } else if (heaterDutyCycle > 0 && currentTime - lastHeaterUpdate >= onTime && currentTime - lastHeaterUpdate < heaterPeriod) {
    digitalWrite(HEATER_CTRL, LOW); // Heater OFF
  } else if (currentTime - lastHeaterUpdate >= heaterPeriod) {
    lastHeaterUpdate = currentTime; // Reset the cycle
  }
}
