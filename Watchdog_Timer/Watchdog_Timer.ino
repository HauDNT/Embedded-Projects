// Tác dụng: giám sát và chống treo chương trình.
#include <avr/wdt.h>

void setup() {
    pinMode(2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(2), myISR, FALLING);
    pinMode(13, OUTPUT);  // Chân 13 để lấy led
    wdt_disable();        // Tắt watchdog timer
}

void loop() {
    while(1) {
      digitalWrite(13, LOW);
    } // Đứng yên - lặp vô hạn (Để tạo lỗi test watchdog)
}

void myISR() {
    digitalWrite(13, HIGH);
    wdt_enable(WDTO_2S);  // Bắt đầu bật watchdog timer (Sau 2s không phản hồi thì tắt chương trình)
    while(digitalRead(2) == 0);
    wdt_disable();
}




