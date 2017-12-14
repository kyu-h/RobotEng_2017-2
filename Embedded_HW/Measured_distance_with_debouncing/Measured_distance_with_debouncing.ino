#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define DELAY 100

const int trigPin = 8; //Trig 핀 할당
const int echoPin = 7; //Echo 핀 할당
const int buttonPin = 9;

int LedState=0;
int InputTime=0;
int LastState=1;
int Button = 0;
int speak = 10;

void setup(){
  lcd.begin(16, 2);
  Serial.begin(115200); //시리얼 초기화
  pinMode(trigPin, OUTPUT); //Trig 핀 output으로 세팅
  pinMode(echoPin, INPUT); //Echo 핀 input으로 세팅
  pinMode(buttonPin, INPUT_PULLUP);
}
void loop(){
  int SwState = digitalRead(buttonPin);
  if(SwState != LastState) { //SwState는 button의 input 값으로 LastState=1 과 비교 한다.
    InputTime = millis(); //SwState 와 LastState가 다를시 InputTime에 millis 값 할당.
  }
  if(millis() - InputTime > DELAY) { // 0.1s 보다 클 경우
    if(SwState != Button) { //Button 값이 0이고, SwState와 상태가 다를 경우 진입
      Button = SwState; //Button에 현재 상태 값 할당.
      if (Button == HIGH){
       LedState = !LedState; //상태 반전.
      }
    }
  }
  if(LedState){
    lcd.clear();
    long duration, distance; //기본 변수 선언
    //Trig 핀으로 10us의 pulse 발생
    digitalWrite(trigPin, LOW); //Trig 핀 Low
    delayMicroseconds(2); //2us 유지
    digitalWrite(trigPin, HIGH); //Trig 핀 High
    delayMicroseconds(10); //10us 유지
    digitalWrite(trigPin, LOW); //Trig 핀 Low
    //Echo 핀으로 들어오는 펄스의 시간 측정
    duration = pulseIn(echoPin, HIGH);
    //pulseIn함수가 호출되고 펄스가 입력될 때까지의 시간. us단위로 값을 리턴.
    //음파가 반사된 시간을 거리로 환산
    //음파의 속도는 340m/s 이므로 1cm를 이동하는데 약 29us.
    //따라서, 음파의 이동거리 = 왕복시간 / 1cm 이동 시간 / 2 이다.
    distance = duration / 29 / 2; //센치미터로 환산
    
    Serial.print(distance);
    Serial.print("cm");
    Serial.println();
    lcd.print(distance);
    lcd.print("cm");
    if(distance < 10){
      tone(speak ,500,1000);
      delay(1000);
    }
    delay(100);
  }
  LastState = SwState;
}
