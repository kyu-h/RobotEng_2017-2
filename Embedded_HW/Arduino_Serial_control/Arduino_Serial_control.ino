int led = 8;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}
// the loop function runs over and over again forever
void loop() {
if(Serial.available()>0){
  int value = Serial.parseInt();
    if(value>=5){
      Serial.print("Put number under the 5");
    }else {
      Serial.print("Turn on while ");
      Serial.print(value);
      Serial.print(" seconds \n");
      digitalWrite(led, HIGH);
      delay(value*1000);
      digitalWrite(led, LOW);
      delay(value*1000);
    }
  }
}
