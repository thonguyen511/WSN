#include <Wire.h>
#include <BH1750.h>
#include <SimpleKalmanFilter.h> // Thư viện cho bộ lọc Kalman
#include <BluetoothSerial.h> // Thư viện cho Bluetooth

BH1750 bh1750_b;
float light_level_b;
SimpleKalmanFilter kalman(2, 2, 0.01); // Khởi tạo bộ lọc Kalman
BluetoothSerial SerialBT; // Khởi tạo đối tượng BluetoothSerial

void setup(){
  Serial.begin(115200);
  Wire1.begin(21, 22);
  Serial.println(F("BH1750 Test"));
  bh1750_b.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &Wire1);

  // Khởi tạo Bluetooth với tên "ESP32_BT"
  SerialBT.begin("ESP32_BT");
}

void loop() {
  light_level_b = bh1750_b.readLightLevel();
  
  // Cập nhật bộ lọc Kalman với giá trị mới
  float filtered_light_level = kalman.updateEstimate(light_level_b);
  
  Serial.print("Filtered Light: ");
  Serial.print(filtered_light_level);
  Serial.println(" lx");

  // Gửi giá trị ánh sáng đã được lọc qua Bluetooth
  SerialBT.print("Filtered Light: ");
  SerialBT.print(filtered_light_level);
  SerialBT.println(" lx");
  
  delay(1000);
}
