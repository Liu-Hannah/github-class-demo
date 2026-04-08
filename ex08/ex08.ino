#include <WiFi.h>
#include <WebServer.h>

// 配置区（建议用英文WiFi名！）
const char* ssid = "我要和你豹了";
const char* password = "liuzihan2006";

const int LED_PIN = 2;
const int TOUCH_PIN = 14;

WebServer server(80);
bool isArmed = false;
bool isAlarming = false;

// 网页代码（UTF-8解决乱码）
const char* htmlPage = R"HTML(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <title>安防报警器</title>
    <style>
        body { text-align: center; margin-top: 50px; }
        .btn { padding: 15px 30px; margin: 10px; font-size: 18px; text-decoration: none; color: white; border-radius: 5px; }
        .arm { background: #f44336; } .disarm { background: #4CAF50; }
    </style>
</head>
<body>
    <h1>物联网安防报警器</h1>
    <a href=" " class="btn arm">布防(Arm)</a >
    <a href="/disarm" class="btn disarm">撤防(Disarm)</a >
</body>
</html>
)HTML";

void handleRoot() { server.send(200, "text/html; charset=UTF-8", htmlPage); }
void handleArm() { isArmed = true; isAlarming = false; server.send(200, "text/html; charset=UTF-8", "<h3>已布防</h3><a href='/'>返回</a >"); }
void handleDisarm() { isArmed = false; isAlarming = false; digitalWrite(LED_PIN, LOW); server.send(200, "text/html; charset=UTF-8", "<h3>已撤防</h3><a href='/'>返回</a >"); }

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(TOUCH_PIN, INPUT);
    digitalWrite(LED_PIN, LOW);

    // 【增强版WiFi连接】增加超时+重试
    WiFi.begin(ssid, password);
    int retryCount = 0;
    while (WiFi.status() != WL_CONNECTED && retryCount < 20) { // 最多重试20次（10秒）
        delay(500);
        Serial.print(".");
        retryCount++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n✅ WiFi连接成功！IP: " + WiFi.localIP().toString());
        server.on("/", handleRoot);
        server.on("/arm", handleArm);
        server.on("/disarm", handleDisarm);
        server.begin();
        Serial.println("✅ Web服务器启动");
    } else {
        Serial.println("\n❌ WiFi连接失败！请检查WiFi名/密码/频段");
        // 连接失败时，LED闪烁提示
        while(1) {
            digitalWrite(LED_PIN, HIGH); delay(200);
            digitalWrite(LED_PIN, LOW); delay(200);
        }
    }
}

void loop() {
    server.handleClient();

    if (isArmed && digitalRead(TOUCH_PIN) == HIGH && !isAlarming) {
        isAlarming = true;
    }

    if (isAlarming) {
        digitalWrite(LED_PIN, HIGH); delay(100);
        digitalWrite(LED_PIN, LOW); delay(100);
    } else {
        digitalWrite(LED_PIN, LOW);
    }
}