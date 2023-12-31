#include<WiFi.h>
#include<WebServer.h>

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
  server.send(200, "text/html", HTMLGui(ledStatus));
}

void event_LedOn() {
  ledStatus = HIGH;
  Serial.print("Chan so 2 ESP32 dang bat");
  server.send(200, "text/html", HTMLGui(ledStatus));
}

void event_LedOff() {
  ledStatus = LOW;
  Serial.print("Chan so 2 ESP32 dang tat");
  server.send(200, "text/html", HTMLGui(ledStatus));
}

void event_NotFound() {
  server.send(400, "text/html", "Not found");
}

void setup() {
  // Khai báo các biến cơ bản:
  Serial.begin(115200);
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
}

void loop() {
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

  String HTMLGui(uint8_t led) {
    String str = "<!DOCTYPE html>\n";
      str += "<html lang=\"en\">";
        str += "<head>";
          str += "<meta charset=\"UTF-8\">";
          str += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
          str += "<title>ESP32 - Webserver</title>";
          str += "<style>";
            str += "* {padding: 0; margin: 0; box-sizing: border-box;}";
            str += "html {font-family: Arial, Helvetica, sans-serif; margin: 0px auto; text-align: center;}";
            str += "body {margin-top: 50px;}";
            str += ".container {background-color: #3559E0;width: 300px;border: 1px solid gray;border-radius: 10px;margin: auto;padding: 20px;}";
            str += "h1 {color: white; margin: 50px 30px;}";
            str += "h3 {color: white;margin-bottom: 50px;}";
            str += ".button {display: block;width: 150px;border: none;padding: 20px 0px;text-decoration: none;font-size: 25px;margin: 15px auto 35px;cursor: pointer;border-radius: 5px;}";
            str += ".button-off {background-color: #EEE7DA;}";
            str += ".button-off:active {background-color: black;}";
            str += "p {font-size: 20px;color: #F9F9E0;margin-bottom: 10px;}";
          str += "</style>";
        str += "</head>";

        str += "<body>";
          str += "<div class=\"container\">";
            str += "<h1>ESP32 Webserver</h1>";

            if (led) 
            {str += "<p>Led status: ON</p><a class=\"button button-off\" href=\"/ledoff\">OFF</a>\n";}
            else 
            {str += "<p>Led status: OFF</p><a class=\"button button-on\" href=\"/ledon\">ON</a>\n";}


          str += "</div>";
        str += "</body>";
      str += "</html>";

      return str;
}












