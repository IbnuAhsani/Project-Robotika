//Arduino PWM Speed Controlï¼š
const int E1 = 5;  
const int M1 = 4; 
const int E2 = 6;                      
const int M2 = 7;
const int pingKanan = 9;
const int pingKiri = 8;
//const int pingDepan = 10;
//const int buzzer = 7;
char serialData;

long pinPingFunc(int pinPing){
  long duration, inches, cm;

  pinMode(pinPing, OUTPUT);
  digitalWrite(pinPing, LOW);
  delayMicroseconds(2);
  digitalWrite(pinPing, HIGH);
  delayMicroseconds(5);
  digitalWrite(pinPing, LOW);

  pinMode(pinPing, INPUT);
  duration = pulseIn(pinPing, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  delay(100);  
  return cm;
}

void setup() 
{ 
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT); 
//    pinMode(buzzer, OUTPUT); 
    Serial.begin(9600);
} 

void kiri(){
    digitalWrite(M1,LOW);   
    digitalWrite(M2, LOW);       
    analogWrite(E1, 175);   //PWM Speed Control
    analogWrite(E2, 175);   //PWM Speed Control
    delay(100);
}

void kanan(){
    digitalWrite(M1,HIGH);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, 175);   //PWM Speed Control
    analogWrite(E2, 175);   //PWM Speed Control
    delay(100);
}

void diam(){
    analogWrite(E1, 0);   //PWM Speed Control
    analogWrite(E2, 0);   //PWM Speed Control
    delay(100);
}

void loop() 
{ 
  long cmKanan, cmKiri,cmDepan;
  cmKanan = pinPingFunc(pingKanan);
  cmKiri = pinPingFunc(pingKiri);
//  cmDepan = pinPingFunc(pingDepan);
  
  Serial.print(cmKanan);
  Serial.println("cm in ping Kanan");
  Serial.print(cmKiri);
  Serial.print("cm in ping Kiri");
  Serial.println();


 // Kodingan berhasil
  if(Serial.available() > 0){
    serialData = Serial.read();
    Serial.print(serialData);

    if(serialData == '1'){
      if(cmKiri <= 50){
        diam();
      } else{
        kanan();
        
      }
    } else if(serialData == '0'){
      if(cmKanan <= 50){
        diam();
      } else{
        kiri();
      }
    } else{
      diam();
//      if(cmDepan <= 12){
//        Tendang
//          Serial.print("Tendang DIGG");
//          Serial.println();
//        digitalWrite(buzzer,HIGH);
//        delay(200);
//        digitalWrite(buzzer,LOW);
//        delay(200);
//      }
    }
  }
//  Serial.print(cmDepan);
//  Serial.print("cm di depan");
//  Serial.println();
  delay(10);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
