int i=0;
void setup() {
// put your setup code here, to run once:
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  if(i<60){
    int j = i % 60;
    Serial.print( j);
    Serial.print("sec");
    Serial.print("\n");
    i+=10;
  }else {
    int k = i/60;
    int m = i%60;
    Serial.print(k);
    Serial.print(" min");
    Serial.print(m);
    Serial.print(" sec");
    i+=10;
    Serial.print("\n");
  }
  delay(1000);
}
