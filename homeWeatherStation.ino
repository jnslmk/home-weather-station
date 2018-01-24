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
const int pinTempHum = 2;  // Temperature and humidity sensor
const int pinChipSelect = 10;  // Chip select for SPI connection to SD card

// Global variables
DHT dht(pinTempHum, DHTTYPE);
bool sdOk = false;

void setup() {
    // Start serial connection
    Serial.begin(9600);

    // Start and temperature/humidity sensor
    dht.begin();

    // Start and setup display
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextSize(1.5);
    display.setTextColor(WHITE);

    // Initialize SD card
    pinMode(pinChipSelect, OUTPUT);
    Serial.print("Initializing SD card...");
    // See if the card is present and can be initialized
    if (!SD.begin(pinChipSelect)) {
        Serial.println("Card failed, or not present");
        sdOk = false;
    } else {
        Serial.println("Card initialized.");
        sdOk = true;
    }
}

void loop() {
    // Set update frequency
    delay(1000);

    // Read values from sensor
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    // Print sensor values
    printSensorValues(temp, hum);

    // Display sensor values
    displaySensorValues(temp, hum);

    // Write values to SD card
    if (sdOk) {
//        writeToSd(temp, hum);
    }
}

void printSensorValues(float temp, float hum) {
    Serial.print("Temperature: "); Serial.print(temp); Serial.println("°C");
    Serial.print("Humidity: "); Serial.print(hum); Serial.println("%");
}

void displaySensorValues(float temp, float hum) {
    display.clearDisplay();
    display.setTextSize(1.5);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("Temperature: "); display.print(temp); 
    display.print((char)247); display.println("C");
    display.print("Humidity: "); display.print(hum); display.println("%");
    display.display();
}

void writeToSd(float temp, float hum) {
    String dataString = String(temp) + "," + String(hum);
    File dataFile = SD.open("humTempLog.txt", FILE_WRITE);
    if (dataFile) {
        dataFile.println(dataString);
        dataFile.close();
        Serial.print("Data string: "); Serial.println(dataString);
    } else {
        Serial.println("Error opening humTempLog.txt");
    }
}

