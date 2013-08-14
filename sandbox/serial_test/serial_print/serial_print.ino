
int delayValue = 1000;

void setup(){
   Serial.begin(9600); 
   pinMode(13, OUTPUT);
}

void loop(){
  digitalWrite(13, HIGH);
  delay(delayValue);  
  digitalWrite(13, LOW);
  delay(delayValue);
  delayValue = delayValue + 500;
  Serial.println(delayValue, HEX);
}
