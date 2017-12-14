#define SWITCH 2
#define LED 13

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(SWITCH, INPUT);
}
void loop() {
  int state = digitalRead(SWITCH);
  digitalWrite(LED, state);
}
