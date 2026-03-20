// 定义LED引脚
const int ledPin = 2;
const int ledPin_Y = 22;

// 设置PWM属性
const int freq = 5000;          // 频率 5000Hz
const int resolution = 8;       // 分辨率 8位 (0-255)

int dutyCycle = 0;              // 当前占空比
unsigned long lastTime = 0; // 上一次更新的时间
const long interval = 10;       // 每次更新的间隔时间(ms)
bool isBrightening = true;      // 是否处于“变亮”阶段

void setup() {
  Serial.begin(115200);
  // 绑定引脚、频率和分辨率
  ledcAttach(ledPin, freq, resolution);
  ledcAttach(ledPin_Y, freq, resolution);
}

void loop() {
  unsigned long now = millis();

  // 判断是否到了更新占空比的时间
  if (now - lastTime >= interval) {
    lastTime = now; // 保存当前时间

    if (isBrightening) {
      // 逐渐变亮
      dutyCycle++;
      if (dutyCycle > 255) {
        dutyCycle = 255;
        isBrightening = false; // 切换为变暗阶段
      }
    } else {
      // 逐渐变暗
      dutyCycle--;
      if (dutyCycle < 0) {
        dutyCycle = 0;
        isBrightening = true; // 切换为变亮阶段
        Serial.println("Breathing cycle completed");
      }
    }

    // 更新PWM占空比
    ledcWrite(ledPin, dutyCycle);
    ledcWrite(ledPin_Y, dutyCycle);
  }
}
