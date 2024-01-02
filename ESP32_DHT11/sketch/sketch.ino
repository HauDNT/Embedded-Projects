#include<WiFi.h>
#include<WebServer.h>
#include<DHT.h>  

// --------------------------- Cấu hình DHT11 --------------------------- 
const int DHTPIN = 2;       //Đọc dữ liệu từ DHT11 ở chân 2 trên mạch Arduino
const int DHTTYPE = DHT11;  //Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22
float h = 0;
float t = 0;

DHT dht(DHTPIN, DHTTYPE);

// --------------------------- Cấu hình ESP32 --------------------------- 
// Khai báo thông tin mạng cục bộ:
const char* ssid = "ESP32 Wifi";
const char* password = "123456789";

// Khai báo các cổng mạng:
IPAddress local_ip(192,168,49,15);
IPAddress gateway(192,168,49,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);
uint8_t LedPin = 2;
bool ledStatus = LOW;

void event_OnConnect() {
  ledStatus = LOW;
  Serial.print("Chan so 2 ESP32 dang tat");
  server.send(200, "text/html", HTMLGui(ledStatus, h, t));
}

void event_LedOn() {
  ledStatus = HIGH;
  Serial.print("Chan so 2 ESP32 dang bat");
  server.send(200, "text/html", HTMLGui(ledStatus, h, t));
}

void event_LedOff() {
  ledStatus = LOW;
  Serial.print("Chan so 2 ESP32 dang tat");
  server.send(200, "text/html", HTMLGui(ledStatus, h, t));
}

void event_NotFound() {
  server.send(400, "text/html", "Not found");
}

void setup() {
  Serial.begin(115200);

  // --------------------------- Khai báo các biến cơ bản của ESP32 --------------------------- 
  pinMode(LedPin, OUTPUT);

  // Cấu hình mạng Wifi:
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", event_OnConnect);
  server.on("/ledon", event_LedOn);
  server.on("/ledoff", event_LedOff);
  server.onNotFound(event_NotFound);

  // Khởi động server:
  server.begin();
  Serial.print("Server is starting");

  // --------------------------- Khởi động cảm biến DHT11 ---------------------------
  dht.begin();
}

void loop() {
  // --------------------------- DHT11 --------------------------- 
  h = dht.readHumidity();    //Đọc độ ẩm
  t = dht.readTemperature(); //Đọc nhiệt độ

  // --------------------------- ESP32 --------------------------- 
  // 192.168.49.15/       -> Connect
  // 192.168.49.15/ledon  -> Turn led on
  // 192.168.49.15/ledoff -> Turn led off

  // Thao tác với client:
  server.handleClient();

  if (ledStatus) {
      digitalWrite(LedPin, 1);
  } else {
      digitalWrite(LedPin, 0);
  }}

  String HTMLGui(uint8_t led, float h, float t) {
    String str = "<!DOCTYPE html>\n";
      str += "<html lang=\"en\">";
        str += "<head>";
          str += "<meta charset=\"UTF-8\">";
          str += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
          str += "<title>ESP32 & DHT11</title>";
          str += "<style>";
            str += "* {padding: 0; margin: 0; box-sizing: border-box;}";
            str += ".container {margin: 10px 0 0 10px;}";
            str += ".wrap-content {width: 100vw; height: 500px; padding: 10px; background-color: #a0a0a0; border: 1px solid black; border-radius: 15px; overflow-x: scroll; }";
          str += "</style>";
        str += "</head>";

        str += "<body>";
          str += "<div class=\"container\">";
            str += "<h1>Check DHT11 & ESP32</h1>";
            str += "<div class=\"wrap-content\"  id=\"output\">";
              str += "<script>";
                str += "function sleep(ms) {";
                str += "return new Promise(resolve => setTimeout(resolve, ms));}";
                
                str += "async function printMessages() {";
                  str += "for (let i = 0; i < 50; i++) {";
                    str += "const outputDiv = document.getElementById('output');";
                    str += "outputDiv.innerHTML += 'Nhiệt độ: ";
                    str += t;
                    str += "\n';";
                    str += "outputDiv.innerHTML += 'Độ ẩm: ";
                    str += h;
                    str += "\n\n';";
                    str += "await sleep(2000);";
                  str += "}";
                str += "}";
                
                str += "printMessages();";
                str += "</script>";

              str += "</script>";

            str += "</div>";
          str += "</div>";
        str += "</body>";
      str += "</html>";

      return str;
}

// if (led) 
// {
//   str += "<span>";
//   str += h;
//   str += "</span><br>";
// }
// else 
// {
//   str += "<span>";
//   str += t;
//   str += "</span><br>";
// }