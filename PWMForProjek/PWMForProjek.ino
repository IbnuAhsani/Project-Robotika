//Arduino PWM Speed Controlï¼š
const int E1 = 5;  
const int M1 = 4; 
const int E2 = 6;                      
const int M2 = 7;
const int pingPin = 9;
const int pingPin2 = 8;
char serialData;
//
//long pinPingFunc(int pinPing){
//  long duration, inches, cm;
//
//  pinMode(pinPing, OUTPUT);
//  digitalWrite(pinPing, LOW);
//  delayMicroseconds(2);
//  digitalWrite(pinPing, HIGH);
//  delayMicroseconds(5);
//  digitalWrite(pinPing, LOW);
//
//  pinMode(pinPing, INPUT);
//  duration = pulseIn(pinPing, HIGH);
//
//  inches = microsecondsToInches(duration);
//  cm = microsecondsToCentimeters(duration);
//
//  delay(100);  
//  return cm;
//}

void setup() 
{ 
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT); 
    Serial.begin(9600);
} 

void kiri(){
    digitalWrite(M1,LOW);   
    digitalWrite(M2, LOW);       
    analogWrite(E1, 255);   //PWM Speed Control
    analogWrite(E2, 255);   //PWM Speed Control
    delay(10);
}

void kanan(){
    digitalWrite(M1,HIGH);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, 255);   //PWM Speed Control
    analogWrite(E2, 255);   //PWM Speed Control
    delay(10);
}

void diam(){
    analogWrite(E1, 0);   //PWM Speed Control
    analogWrite(E2, 0);   //PWM Speed Control
    delay(10);
}

void loop() 
{ 
//  long cm1,cm2;
//  cm1 = pinPingFunc(pingPin);
//  cm2 = pinPingFunc(pingPin2);
//
//  Serial.print(cm1);
//  Serial.println("cm in ping 1");
//  Serial.print(cm2);
//  Serial.print("cm in ping 2");
//  Serial.println();

// Kodingan faizin
//  if(cm1 <= 50 || cm2 <= 50){
//    Serial.print("STOP");  
//    diam();
//  }else{
//    kanan();
//  }
//  delay(10);

//  if(cm1 <= 5 || cm2 <= 5){
//    Serial.print("Berhenti");
//  } else {
//    if(Serial.available() > 0){
//    serialData = Serial.read();
//    Serial.print(serialData);
//
//    if(serialData == '1'){
//      kanan();
//    } else if(serialData == '0'){
//      kiri();
//    } else{
//      diam();
//    }
//  }
//  }

// Kodingan berhasil
  if(Serial.available() > 0){
    serialData = Serial.read();
    Serial.print(serialData);

    if(serialData == '1'){
      kanan();
    } else if(serialData == '0'){
      kiri();
    } else{
      diam();
    }
//   if(cm1 <= 25 || cm2 <= 25){
//      Serial.print("STOP");  
//      diam();
//    }
//    delay(10);
  }
}

//long microsecondsToInches(long microseconds) {
//  return microseconds / 74 / 2;
//}
//
//long microsecondsToCentimeters(long microseconds) {
//  return microseconds / 29 / 2;
//}
