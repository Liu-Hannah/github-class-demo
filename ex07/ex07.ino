#include <WiFi.h>
#include <WebServer.h>

// WiFi配置（必须改成你自己的WiFi！）
const char* ssid = "我要和你豹了";
const char* password = "liuzihan2006";

// 硬件配置
const int ledPin = 2;

WebServer server(80);

// 修复乱码的网页
const char* html = R"HTML(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>ESP32调光器</title>
</head>
<body>
    <h1>ESP32 无极调光器</h1>
    <input type="range" min="0" max="255" id="slider" oninput="sendBrightness(this.value)">
    <p>亮度: <span id="val">0</span></p >

    <script>
        function sendBrightness(b) {
            document.getElementById("val").innerText = b;
            fetch("/set?brightness=" + b);
        }
    </script>
</body>
</html>
)HTML";

void handleRoot() {
    server.send(200, "text/html; charset=UTF-8", html);
}

void handleSet() {
    if (server.hasArg("brightness")) {
        int b = server.arg("brightness").toInt();
        b = constrain(b, 0, 255);
        analogWrite(ledPin, b);
        server.send(200, "text/plain", "OK");
    } else {
        server.send(400, "text/plain", "参数错误");
    }
}

void setup() {
    Serial.begin(115200);
    
    pinMode(ledPin, OUTPUT);
    analogWrite(ledPin, 0);

    // 连接WiFi，增加打印提示
    WiFi.begin(ssid, password);
    Serial.print("正在连接WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("."); // 连接中打印点，直观看到进度
    }
    // 【关键修复】WiFi连上后，再打印IP！
    Serial.println("\nWiFi连接成功!");
    Serial.print("ESP32的IP地址是:");
    Serial.println(WiFi.localIP()); // 这里就是你要的网址！

    server.on("/", handleRoot);
    server.on("/set", handleSet);
    server.begin();
    Serial.println("Web服务器已启动");
}

void loop() {
    server.handleClient();
}