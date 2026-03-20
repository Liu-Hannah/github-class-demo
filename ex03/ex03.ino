#define LED_PIN_R 2
#define LED_PIN_Y 22

// 全局计时变量，仅用于替代delay()
unsigned long lastTime = 0;

// 替代delay_ms的非阻塞函数
bool wait(unsigned long ms) {
  static unsigned long start = 0;
  if (millis() - start >= ms) {
    start = millis();
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN_R, OUTPUT);
  pinMode(LED_PIN_Y, OUTPUT);
  lastTime = millis();
}

void loop() {
  // S: 短闪3次
  for(int i = 1; i <= 3; i++) {
    digitalWrite(LED_PIN_R, HIGH);
    digitalWrite(LED_PIN_Y, HIGH);
    while(!wait(200)); // 替代delay(200)
    digitalWrite(LED_PIN_R, LOW);
    digitalWrite(LED_PIN_Y, LOW);
    while(!wait(200)); // 替代delay(200)
  }

  // S字母间隔
  while(!wait(600)); // 替代delay(600)

  // O: 长闪3次
  for(int i = 1; i <= 3; i++) {
    digitalWrite(LED_PIN_R, HIGH);
    digitalWrite(LED_PIN_Y, HIGH);
    while(!wait(600)); // 替代delay(600)
    digitalWrite(LED_PIN_R, LOW);
    digitalWrite(LED_PIN_Y, LOW);
    while(!wait(200)); // 替代delay(200)
  }

  // O字母间隔
  while(!wait(600)); // 替代delay(600)

  // S: 短闪3次
  for(int i = 1; i <= 3; i++) {
    digitalWrite(LED_PIN_R, HIGH);
    digitalWrite(LED_PIN_Y, HIGH);
    while(!wait(200)); // 替代delay(200)
    digitalWrite(LED_PIN_R, LOW);
    digitalWrite(LED_PIN_Y, LOW);
    while(!wait(200)); // 替代delay(200)
  }

  // 单词间隔
  while(!wait(2000)); // 替代delay(2000)
}