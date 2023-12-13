// UART - Serial Protocol
// or Heculles, Realterm

void setup() {
    Serial.begin(9600); // Tốc độ (...bit/giây)
    Serial.print("A");
    Serial.println("-B");
}

void loop() {
    // Câu lệnh nhận: Serial.read()/Serial.readString()
    // Lệnh kiểm tra xem có nhận được bộ đệm chưa:
    if(Serial.available() > 0) {
        Serial.print(Serial.read());
    }
}
