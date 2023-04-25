// WEMOS D1 MINI ESP32
// https://randomnerdtutorials.com/esp32-built-in-oled-ssd1306/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 15

void setup() {

  Serial.begin(115200);
  Wire.begin(5, 4);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000); // Pause for 2 seconds
 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("DHT11 humidity and temp");
  display.display();
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
  String displayValueTemp = "t:" + String(DHT.temperature);
  String displayValueHumi = "h:" + String(DHT.humidity);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(displayValueTemp);
  display.setCursor(0,20);
  display.println(displayValueHumi);
  display.display();
  delay(100);
}
