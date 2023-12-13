#define LED 2
#define Button 4
boolean ButtonState = 1;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  if (touchRead(Button) < 20) {
    if (ButtonState == 1) {
      digitalWrite(LED, !digitalRead(LED));
    }
    ButtonState = 0;
  } else {
    ButtonState = 1;
  }
  delay(200);
}
