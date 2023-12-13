const int LEDPin = 12;
const int buttonPin = 2;
int count = 0;
int buttonState = 1;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LEDPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(LEDPin, HIGH);
}

// the loop function runs over and over again forever
void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == 0) {   // Có nút bấm thì trả về 0
    delay(200);
    if (count == 0) {
      digitalWrite(LEDPin, HIGH); //LEDPin = 1
      count = 1;
    }
    else {
      digitalWrite(LEDPin, LOW);   // LEDPin = 0
      count = 0;
    }
  }
}
