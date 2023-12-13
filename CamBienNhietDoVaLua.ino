#include <DHT.h>
#include <DHT_U.h>

#define DHT11Pin 4  //Cổng cắm
#define DHTType DHT11

DHT HT(DHT11Pin, DHTType);
float humi;   //do am
float tempC;  //do C
float tempF;  // do F
int cambien = 5; //Chân cảm biến nối chân số 5 Arduino
int giatri;

void setup() {
  Serial.begin(9600);
  HT.begin();
  pinMode(cambien, INPUT);
  delay(1000);
}

void loop() {
  delay(1000); 

  humi = HT.readHumidity(); // Đọc độ ẩm
  tempC = HT.readTemperature(); // Đọc độ C
  tempF = HT.readTemperature(true); // Đọc độ F

  Serial.print("Humidity: ");
  Serial.print(humi);
  Serial.print("%");
  Serial.print("\tTemporature C: ");
  Serial.print(tempC);
  Serial.print(" ~ Temporature F: ");
  Serial.println(tempF);

  giatri = digitalRead(cambien); //Đọc giá trị digital từ cảm biến và gán vào biến giatri
  Serial.print("Giá trị cảm biến là: ");
  Serial.println(giatri);
}
