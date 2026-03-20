#define LED_PIN 2
#define LED_PIN_Y 22 //定义LED引脚

bool LED_state=false;//灯的初始状态
unsigned long lastTime=0;//初始时间
unsigned long interval=1000;//间隔时常

void setup() {
  pinMode(LED_PIN,OUTPUT);
  pinMode(LED_PIN_Y,OUTPUT);
}

void loop() {
  unsigned long now=millis();
  if(now-lastTime>=interval)
  {
    LED_state=!LED_state;
    if(LED_state)
    {
      digitalWrite(LED_PIN,HIGH);
      digitalWrite(LED_PIN_Y,HIGH);
    }
    else
    {
      digitalWrite(LED_PIN,LOW);
      digitalWrite(LED_PIN_Y,LOW);
    }
    lastTime=now;
  }


}
