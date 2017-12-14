#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup(){
  lcd.begin(16, 2);
}
void loop(){
  for(int i=16; i>=0; i--){
    lcd.setCursor(i,0);
    lcd.print("Hello world!!");
    delay(1000);
    lcd.clear();
  }
}
