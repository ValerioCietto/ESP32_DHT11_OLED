// WEMOS D1 MINI ESP32
#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 15

void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

void loop() {
  // If there's any serial data available, read it and print it to the serial monitor:
  if (Serial.available() > 0) {
    int incomingByte = Serial.read();
    Serial.print("Received: ");
    Serial.println(incomingByte, DEC);
  }
  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  Serial.print(DHT.temperature);
  Serial.print("  humi:");
  Serial.println(DHT.humidity);
  delay(1000);
}
