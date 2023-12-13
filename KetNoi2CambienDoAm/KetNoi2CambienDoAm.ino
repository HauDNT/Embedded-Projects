#include "DHT.h"
#define DHT1Pin 4
#define DHT2Pin 8
#define DHTType DHT11

DHT HT1(DHT1Pin, DHTType);
DHT HT2(DHT2Pin, DHTType);

float doAm_Chip1;
float doAm_Chip2;
float doC_Chip1;
float doC_Chip2;
float doF_Chip1;
float doF_Chip2;

void setup() {
  Serial.begin(9600);
  HT1.begin();
  HT2.begin();
  delay(1000);
}

void loop() {
  delay(3000);

  doAm_Chip1 = HT1.readHumidity();
  doAm_Chip2 = HT2.readHumidity();
  doC_Chip1 = HT1.readTemperature();
  doC_Chip2 = HT2.readTemperature();
  doF_Chip1 = HT1.readTemperature(true);
  doF_Chip2 = HT2.readTemperature(true);

  Serial.print("\tChip 1 \t Chip 2\n");

  Serial.print("Do am:\t");
  Serial.print(doAm_Chip1);
  Serial.print("\t");
  Serial.print(doAm_Chip2);
  Serial.println();

  Serial.print("Do C:\t");
  Serial.print(doC_Chip1);
  Serial.print("\t");
  Serial.print(doC_Chip2);
  Serial.println();

  Serial.print("Do F:\t");
  Serial.print(doF_Chip1);
  Serial.print("\t");
  Serial.print(doF_Chip2);

  Serial.println();
}
