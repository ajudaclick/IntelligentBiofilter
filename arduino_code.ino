#include <MQUnifiedsensor.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define Board ("ESP-32")
#define Pin (34) // Pin where the sensor is connected
#define Type ("MQ-4")
#define Voltage_Resolution (3.3)
#define ADC_Bit_Resolution (12)
#define RatioMQ4CleanAir (4.4)

MQUnifiedsensor MQ4(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* serverName = "http://your_influxdb_server/write?db=your_database";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  MQ4.setRegressionMethod(1); // Set regression method to linear
  MQ4.setA(69.65); MQ4.setB(-1.3); // Configure the equation to calculate ppm of CH4
  MQ4.init();
}

void loop() {
  MQ4.update(); // Update the sensor readings
  float CH4 = MQ4.readSensor(); // Read the CH4 concentration

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String httpRequestData = "methane=" + String(CH4);
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
  delay(60000); // Send data every minute
}