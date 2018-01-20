#include "DHT.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define type of temperature and humidity sensor
#define DHTTYPE DHT22

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// Pin definitions
const int pinTempHum = 2; // Temperature and humidity sensor

// Global variables
DHT dht(pinTempHum, DHTTYPE);

void setup() {
  // Start serial connection
  Serial.begin(9600);
  // Start temperature/humidity sensor
  dht.begin();
  // Start display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
  // Clear the buffer.
  display.clearDisplay();
}

void loop() {
  // Set update frequency
  delay(1000);

  // Read values from sensor
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Print sensor values
  //Serial.print("Temperature: "); Serial.print(temp); Serial.println("°C");
  //Serial.print("Humidity: "); Serial.print(hum); Serial.println("%");

  // Display sensor values
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Temperature: "); display.print(temp); display.print((char)247); display.println("C");
  display.print("Humidity: "); display.print(hum); display.println("%");
  display.display();
}

