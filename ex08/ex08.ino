#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "HANNAH";
const char* password = "liuzihan2006";

const int LED = 2;
const int TouchPin = 4;

WebServer server(80);

bool isArm = false;    // 布防
bool isAlarm = false;  // 报警

// 网页
const char* html = R"HTML(
<!DOCTYPE html>
<meta charset="UTF-8">
<h1>安防报警</h1>
<p><a href=" ">布防</a ></p >
<p><a href="/disarm">撤防</a ></p >
)HTML";

void handleRoot() { server.send(200, "text/html; charset=utf-8", html); }
void handleArm()  { isArm = true;  isAlarm = false; server.send(200,"text/html","已布防 <a href='/'>返回</a >"); }
void handleDisarm(){isArm = false; isAlarm = false; digitalWrite(LED,LOW);server.send(200,"text/html","已撤防 <a href='/'>返回</a >");}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(TouchPin, INPUT_PULLUP); 

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nIP:"); Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
}

void loop() {
  server.handleClient();

  if (isArm && digitalRead(TouchPin) == LOW) {
    isAlarm = true;
  }

  if (isAlarm) {
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
  } else {
    digitalWrite(LED, LOW);
  }
}