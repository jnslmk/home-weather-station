#include "DHT.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <SD.h>

// Define type of temperature and humidity sensor
#define DHTTYPE DHT22

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// Pin definitions
const int pinTempHum = 2; // Temperature and humidity sensor
const int chipSelect = 10;

// Global variables
DHT dht(pinTempHum, DHTTYPE);

void setup() {
  // Start serial connection
  Serial.begin(9600);
  
  // Start temperature/humidity sensor
  dht.begin();
  
  // Start display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  // Initialize SD card
  pinMode(chipSelect, OUTPUT);
  Serial.print("Initializing SD card...");
  // See if the card is present and can be initialized
//  if (!SD.begin(chipSelect)) {
//    Serial.println("Card failed, or not present");
//  } else {
//    Serial.println("Card initialized.");
//  }
}

void loop() {
  // Set update frequency
  delay(1000);

  // Read values from sensor
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Print sensor values
  Serial.print("Temperature: "); Serial.print(temp); Serial.println("°C");
  Serial.print("Humidity: "); Serial.print(hum); Serial.println("%");

  // Display sensor values
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Temperature: "); display.print(temp); display.print((char)247); display.println("C");
  display.print("Humidity: "); display.print(hum); display.println("%");
  display.display();

  // Write values to SD card
//  String dataString = String(temp) + "," + String(hum);
//  File dataFile = SD.open("humTempLog.txt", FILE_WRITE);
//  if (dataFile) {
//    dataFile.println(dataString);
//    dataFile.close();
//    Serial.print("Data string: "); Serial.println(dataString);
//  } else {
//    Serial.println("Error opening humTempLog.txt");
//  }
}

