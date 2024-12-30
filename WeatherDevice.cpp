#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h> // Library for BME280 sensor
#include <LowPower.h>        // For deep sleep

// LoRa pin definitions (adjust based on your module and Arduino pins)
#define LORA_SS 10
#define LORA_RST 9
#define LORA_DIO0 2

// BME280 I2C address
#define BME280_I2C_ADDR 0x76

// LoRa parameters
const long frequency = 915E6; // Frequency (adjust based on region)

// Define data payload
byte data[6]; // Adjusted for higher precision

float temp;
float humd;
float pres;

Adafruit_BME280 bme; // BME280 instance

void setup() {
  // Start USB serial communication
  Serial.begin(9600);
  while (!Serial);

  Serial.println(F("Start program"));
  Serial.println(F("LoRaWAN example - Send Confirmed packets (ACK)\n"));

  // Initialize BME280 sensor
  if (!bme.begin(BME280_I2C_ADDR)) {
    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
    while (1);
  }

  // Initialize LoRa module
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0); // Set LoRa pins

  if (!LoRa.begin(frequency)) {
    Serial.println(F("Starting LoRa failed!"));
    while (1);
  }

  Serial.println(F("LoRa initialized"));
}

void loop() {
  // Read sensor data
  temp = bme.readTemperature();
  humd = bme.readHumidity();
  pres = bme.readPressure() / 100.0F; // Convert to hPa

  // Print sensor data to Serial
  Serial.println("-----------------------------");
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  Serial.print("Humidity: ");
  Serial.print(humd);
  Serial.println(" %");
  Serial.print("Pressure: ");
  Serial.print(pres);
  Serial.println(" hPa");
  Serial.println("-----------------------------");

  // Encode data to send
  int16_t temp_encoded = (int16_t)(temp * 100); // Convert to 0.01 precision
  int16_t humd_encoded = (int16_t)(humd * 100); // Convert to 0.01 precision
  int16_t pres_encoded = (int16_t)(pres * 10);  // Convert to 0.1 precision

  data[0] = temp_encoded >> 8;
  data[1] = temp_encoded & 0xFF;
  data[2] = humd_encoded >> 8;
  data[3] = humd_encoded & 0xFF;
  data[4] = pres_encoded >> 8;
  data[5] = pres_encoded & 0xFF;

  // Send data via LoRa
  LoRa.beginPacket();
  LoRa.write(data, sizeof(data));
  if (LoRa.endPacket() == 0) {
    Serial.println(F("Failed to send packet!"));
  } else {
    Serial.println(F("Data sent via LoRa"));
  }

  // Deep sleep for 10 seconds (use LowPower library)
  Serial.println(F("Entering deep sleep for 10 seconds..."));
  for (int i = 0; i < 2; i++) { // Sleep for 8s + 2s to achieve ~10 seconds
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }

  Serial.println(F("Waking up\n"));
}

