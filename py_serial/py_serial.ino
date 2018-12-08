char serialData;
int pinLED = 9;

void setup() {
  pinMode(pinLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {  
  if(Serial.available() > 0){
    serialData = Serial.read();
    Serial.print(serialData);

    if(serialData == '1'){
      digitalWrite(pinLED, HIGH);
    } else if(serialData == '0'){
      digitalWrite(pinLED, LOW);
    }
  }
}
