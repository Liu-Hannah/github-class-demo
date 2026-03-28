// ex06 双通道反相PWM警灯
const int ledPinA = 2;
const int ledPinB = 14;
const int freq = 5000;
const int resolution = 8;

void setup() {
  Serial.begin(115200);

  // 直接用你实验3里的写法，绑定两个通道
  ledcAttach(ledPinA, freq, resolution);
  ledcAttach(ledPinB, freq, resolution);
}

void loop() {
  // 灯A从0→255变亮，灯B同步从255→0变暗
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    int brightnessB = 255 - dutyCycle;
    ledcWrite(ledPinA, dutyCycle);
    ledcWrite(ledPinB, brightnessB);
    delay(15); // 控制速度，越小越快
  }

  // 反向循环，让灯A从255→0变暗，灯B从0→255变亮
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    int brightnessB = 255 - dutyCycle;
    ledcWrite(ledPinA, dutyCycle);
    ledcWrite(ledPinB, brightnessB);
    delay(15);
  }
}
