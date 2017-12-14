#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    long val1 = Serial.parseInt();
    char text = Serial.read();
    long val2 = Serial.parseInt();
    if(text == '+'){
    Serial.print(val1);
    Serial.print("+");
    Serial.print(val2);
    Serial.print("=");
    Serial.println(val1 + val2);
    lcd.clear();
    lcd.print(val1);
    lcd.print("+");
    lcd.print(val2);
    lcd.print("=");
    lcd.print(val1 + val2);
  }else {
    Serial.print(val1);
    Serial.print("-");
    Serial.print(val2);
    Serial.print("=");
    Serial.println(val1 - val2);
    lcd.clear();
    lcd.print(val1);
    lcd.print("-");
    lcd.print(val2);
    lcd.print("=");
    
    lcd.print(val1 - val2);
  }
  }
}
