// ex05 多档位触摸调速呼吸灯
#include <Arduino.h>

// 引脚定义
const int ledPin = 2;
const int touchPin = 4;
const int freq = 5000;
const int resolution = 8;

// 档位与控制变量
int speedLevel = 1;
int delayTime;
bool touchFlag = false;
unsigned long lastTouchTime = 0;
const unsigned long debounceTime = 100;

// 触摸中断服务函数
void gotTouch() {
  if (millis() - lastTouchTime < debounceTime) return;
  lastTouchTime = millis();
  touchFlag = true;
}

void setup() {
  Serial.begin(115200);
  // 初始化PWM呼吸灯
  ledcAttach(ledPin, freq, resolution);
  // 初始化触摸中断
  touchAttachInterrupt(touchPin, gotTouch, 500);
}

void loop() {
  // 处理触摸事件，切换档位
  if (touchFlag) {
    touchFlag = false;
    speedLevel = (speedLevel % 3) + 1; // 1→2→3→1循环
    Serial.print("当前档位：");
    Serial.println(speedLevel);
  }

  // 根据档位设置呼吸速度
  switch(speedLevel) {
    case 1: delayTime = 30; break; // 慢
    case 2: delayTime = 15; break; // 中
    case 3: delayTime = 5; break;  // 快
  }

  // 呼吸灯变亮
  for(int duty = 0; duty <= 255; duty++) {
    ledcWrite(ledPin, duty);
    delay(delayTime);
  }

  // 呼吸灯变暗
  for(int duty = 255; duty >= 0; duty--) {
    ledcWrite(ledPin, duty);
    delay(delayTime);
  }
}
