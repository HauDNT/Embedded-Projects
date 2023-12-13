// Khai báo thư viện hỗ trợ DHT, chân cắm:
#include "DHT.h"
#define DHT1Pin 8
#define DHTType DHT11

// Khai báo chân cắm của cảm biến báo cháy:
int fireSensor = 5;

// Khởi tạo đối tượng và các biến lưu giá trị của DHT:
DHT HT(DHT1Pin, DHTType);
float humi;   //do am
float tempC;  //do C
float tempF;  // do F

void FireSensor() {
  if (digitalRead(fireSensor) == 0)
    Serial.print("Có lửa\t");
  else 
    Serial.print("Không có lửa\t");
}

void DHTSensor() {
  humi = HT.readHumidity();
  tempC = HT.readTemperature();
  tempF = HT.readTemperature(true);

  Serial.print("Độ ẩm: ");
  Serial.print(humi);
  Serial.print("%");
  Serial.print("\tĐộ C: ");
  Serial.print(tempC);
  Serial.print(" ~ Độ F: ");
  Serial.println(tempF);
}

void setup() {
  Serial.begin(9600);
  HT.begin();
  pinMode(fireSensor, INPUT);
  delay(1000);
}

void loop() {
  delay(2000);
  FireSensor();
  DHTSensor();
}
