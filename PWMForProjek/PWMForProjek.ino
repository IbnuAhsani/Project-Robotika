//Arduino PWM Speed Controlï¼š
int E1 = 5;  
int M1 = 4; 
int E2 = 6;                      
int M2 = 7;
const int pingPin = 9;
const int pingPin2 = 8;
//int E1 = 4;  
//int M1 = 5; 
//int E2 = 7;                      
//int M2 = 6;                        
long pinPingFunc(int pinPing){
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pinPing, OUTPUT);
  digitalWrite(pinPing, LOW);
  delayMicroseconds(2);
  digitalWrite(pinPing, HIGH);
  delayMicroseconds(5);
  digitalWrite(pinPing, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pinPing, INPUT);
  duration = pulseIn(pinPing, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

//  Serial.print(inches);
//  Serial.print("in, ");
//  Serial.print(cm);
//  Serial.print("cm");
//  Serial.println();

  delay(100);  
  return cm;
}
void setup() 
{ 
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT); 
} 
void kiri(){
    digitalWrite(M1,LOW);   
    digitalWrite(M2, LOW);       
    analogWrite(E1, 200);   //PWM Speed Control
    analogWrite(E2, 200);   //PWM Speed Control
    delay(300);
}
void kanan(){
    digitalWrite(M1,HIGH);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, 200);   //PWM Speed Control
    analogWrite(E2, 200);   //PWM Speed Control
    delay(300);
}
void diam(){
    analogWrite(E1, 0);   //PWM Speed Control
    analogWrite(E2, 0);   //PWM Speed Control
    delay(30);
}
void loop() 
{ 
  long cm1,cm2;
  cm1 = pinPingFunc(pingPin);
  cm2 = pinPingFunc(pingPin2);
//    digitalWrite(M1,HIGH);   
//    digitalWrite(M2, HIGH);       
//    analogWrite(E1, 50);   //PWM Speed Control
//    analogWrite(E2, 50);   //PWM Speed Control
//    delay(30); 
 
//  int value;
//  for(value = 0 ; value <= 255; value+=5) 
//  { 
//
//  }
//kanan();
  if(cm1 <=9 && cm1 >= 0){
     Serial.print("STOP");  
//      diam();
      kanan();
//
  }else if(cm2 <=9 && cm2 >= 0){
    kiri();    
  }else{
    diam();
  }
  delay(10);
}
long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
