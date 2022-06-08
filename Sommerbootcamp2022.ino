#include "DHT.h"
#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht11(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht11.begin();
}

void loop() {
  delay(5000);

  int humi = dht11.readHumidity() * 10;
  int temp = dht11.readTemperature() * 10;
  if(temp < 0)    // if temperature < 0
    Serial.printf("Temp: -%02u.%1u°C\n", (abs(temp)/10)%100, abs(temp) % 10);
  else            // temperature >= 0
    Serial.printf("Temp: %02u.%1u°C\n", (temp/10)%100, temp % 10);

  Serial.printf("Humi: %02u.%1u%%\n", (humi/10)%100, humi % 10);
}