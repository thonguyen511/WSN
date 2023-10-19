#include <DHT.h>
#include <BluetoothSerial.h>

#define DHTPIN 13     // Cổng kết nối với DHT11
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); // Tên thiết bị Bluetooth
  dht.begin();
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  SerialBT.print("Humidity: ");
  SerialBT.print(h);
  SerialBT.print(" %\t");
  SerialBT.print("Temperature: ");
  SerialBT.print(t);
  SerialBT.println(" *C");
}
