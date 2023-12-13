#include <SoftwareSerial.h>
SoftwareSerial softUART(2, 3);  // RX = 2, TX = 3

void setup() {
  Serial.begin(9600);
  softUART.begin(9600);
}

void loop() {
  if (softUART.available()) {
    Serial.write(softUART.read());
    // if (softUART.read() == 1) {
    //   // Điều khiển thiết bị, động cơ,...
    // }
  }
}