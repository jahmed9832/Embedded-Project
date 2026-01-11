#include<Servo.h>
Servo myservo;
#define trig A3
#define echo A4
int in1 = 4,in2 = 5,in3 = 3,in4 = 2;
int EnA = 11,EnB  = 6,spd = 200;
float duration,distance;
void setup(){
  Serial.begin(9600);
  pinMode(EnA,OUTPUT);
  pinMode(EnB,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  myservo.attach(9);
  myservo.write(90);
}
float getdistance(){
  digitalWrite(trig,LOW);
  delay(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);
  distance = duration / 58.00;
  return distance;
}

void loop(){
  analogWrite(EnA,spd);
  analogWrite(EnB,spd);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  float d = getdistance();
  Serial.println(d);
 
  if(d < 40.0){
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    delay(400);
    myservo.write(20);
    delay(700);
    float d1 = getdistance();
    myservo.write(160);
    delay(700);
    float d2 = getdistance();
    myservo.write(90);
    delay(700);
    if(d1 > d2){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    delay(500);  
    }
    else{
   digitalWrite(in1,HIGH);
   digitalWrite(in2,LOW);
   digitalWrite(in3,HIGH);
   digitalWrite(in4,LOW);
   delay(500);
    }
  }
  delay(100);
}
