// 定义板载LED引脚，避免使用"魔法数字"
#define LED_PIN 2
#define LED_PIN_R 22

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  // 初始化板载LED引脚为输出模式
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_R, OUTPUT);
}

void loop() 
{
  // S: 短闪3次
  for(int i=0; i<3; i++) { digitalWrite(LED_PIN_R, HIGH); delay(200); digitalWrite(LED_PIN_R, LOW); delay(200); }
  delay(500); // 字母间隔
  // O: 长闪3次
  for(int i=0; i<3; i++) { digitalWrite(LED_PIN_R, HIGH); delay(600); digitalWrite(LED_PIN_R, LOW); delay(200); }
  delay(500);
  // S: 短闪3次
  for(int i=0; i<3; i++) { digitalWrite(LED_PIN_R, HIGH); delay(200); digitalWrite(LED_PIN_R, LOW); delay(200); }
  delay(2000); // 单词间隔
  

}
