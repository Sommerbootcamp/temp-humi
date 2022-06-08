#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN D2
#define DHTTYPE DHT11

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI   13
#define OLED_CLK   14
#define OLED_DC    5
#define OLED_CS    15
#define OLED_RESET 12 //D6

DHT dht11(DHTPIN, DHTTYPE);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


void setup() {
  Serial.begin(115200);
  dht11.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.display();
  delay(100);
}

void loop() {
  delay(5000);
  dht12();
}

void dht12() {

  int humi = dht11.readHumidity() * 10;
  int temp = dht11.readTemperature() * 10;
  if(temp < 0) {    // if temperature < 0
    Serial.printf("Temp: -%02u.%1u�C\n", (abs(temp)/10)%100, abs(temp) % 10);
  }
  else {            // temperature >= 0
    Serial.printf("Temp: %02u.%1u�C\n", (temp/10)%100, temp % 10);
  }

  Serial.printf("Humi: %02u.%1u%%\n", (humi/10)%100, humi % 10);

  displayDht12(dht11.readTemperature(), "Temperatur", " C");
  delay(5000);
  displayDht12(dht11.readHumidity(), "Humi.", " %");
}

void displayDht12(int value, String text, String dht12Unit) {
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println(text);

  display.setTextSize(3);
  display.setCursor(30,25);
  display.print(value);
  display.print(dht12Unit);
  display.display();
}
