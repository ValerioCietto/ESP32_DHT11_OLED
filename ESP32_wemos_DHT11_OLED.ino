
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
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ssl_client.h>
const char* ssid = "XXXXXXXXXXX";
const char* password = "XXXXXXXXXXXXXXX";
#define BOT_TOKEN "XXXXXXXXXXXXXXXXXXXXXXXXXXX"
WiFiClientSecure secured_client;
#include <UniversalTelegramBot.h>
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done
String chat_id;

void handleNewMessages(int numNewMessages)
{
  for (int i = 0; i < numNewMessages; i++)
  {
    bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].text, "");
  }
}

void setup() {

  Serial.begin(115200);
  Wire.begin(5, 4);

  WiFi.begin(ssid, password);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
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
  display.setCursor(0,20);
  display.println("bot name XXXXXXXXXXXXXX");
  display.display();

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  // Print the WiFi connection details
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost");
    // Reconnect to the WiFi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
  }
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
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

  for (int i = 0; i < numNewMessages; i++) {
    chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    if (text.equals("read")) {
      String message = displayValueTemp + "C°\n" + displayValueHumi + "%";
      bot.sendMessage(chat_id, message);
    }
  }
  
}
