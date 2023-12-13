const int ADC_Pin = A0;
const int PWW = 3;
int ADC_Read;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  ADC_Read = analogRead(ADC_Pin);
  // ADC_Read = 0 -> 1023
  // Hàm chuyển đổi thang đo:
  ADC_Read = map(ADC_Read, 0, 1023, 0, 255);
  // ADC_Read (now) 0 -> 255
  analogWrite(PWW, ADC_Read);
}
