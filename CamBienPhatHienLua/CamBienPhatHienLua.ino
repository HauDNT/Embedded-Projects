int aIn = A0;
int dIn = 4;
int giatri;

void setup() 
{
  Serial.begin(9600);
  pinMode(aIn, INPUT);
  pinMode(dIn, INPUT);
}

void loop() 
{
  //giatri = digitalRead(cambien); //Đọc giá trị digital từ cảm biến và gán vào biến giatri

  giatri = analogRead(aIn);
  if (digitalRead(dIn) == LOW) {
    Serial.print("Co lua!");
    Serial.print(giatri);
  }
  else {
        Serial.print("Khong co lua!");
    Serial.print(giatri);
  }

  // Serial.print("Giá trị cảm biến là: ");
  // Serial.println(giatri);
  delay(2000);
}