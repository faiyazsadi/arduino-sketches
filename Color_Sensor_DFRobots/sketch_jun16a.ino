#include<Servo.h>

int s0=3,s1=4,s2=5,s3=6;
int out=2;
int flag=0;
byte counter=0;
byte countR=0,countG=0,countB=0;
Servo myservo;

int r, g, b;

void setup() {
 myservo.attach(9);
 Serial.begin(115200);
 pinMode(s0,OUTPUT);
 pinMode(s1,OUTPUT);
 pinMode(s2,OUTPUT);
 pinMode(s3,OUTPUT);
}

void TCS() {
 flag=0;
 digitalWrite(s0,HIGH);
 digitalWrite(s1, HIGH);
 digitalWrite(s2,LOW);
 digitalWrite(s3,LOW);
 Serial.println("TCS");
 attachInterrupt(0, ISR_INTO, CHANGE);
 timer0_init();
}

void ISR_INTO() {
 counter++;
}

void timer0_init(void) {
  TCCR2A=0x00;
  TCCR2B=0x07;   //the clock frequency source 1024 points
  TCNT2= 100;    //10 ms overflow again
  TIMSK2 = 0x01; //allow interrupt
}

//void red() {
//  myservo.write(20);
//  delay(5000);
//}
//
//void green() {
//  myservo.write(90);
//  delay(5000);
//}
//
//void blue() {
//  myservo.write(150);
//  delay(5000);
//}

int i=0;
ISR(TIMER2_OVF_vect)//the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function 
{
  TCNT2=100;
  flag++;
  if(flag==1) {
    countR=counter;
    Serial.print("red=");
    Serial.println(countR,DEC);
//    myservo.write(20);
//    delay(5000);
//    myservo.write(0);
//    delay(1000);
    r = countR;
    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);
  }
  else if(flag==2) {
    countG=counter;
    Serial.print("green=");
    Serial.println(countG,DEC);
//    myservo.write(90);
//    delay(5000);
//    myservo.write(0);
//    delay(1000);
    g = countG;
    digitalWrite(s2,LOW);
    digitalWrite(s3,HIGH);
  }
  else if(flag==3) {
    countB=counter;
    Serial.print("blue=");
    Serial.println(countB,DEC);
//    myservo.write(150);
//    delay(5000);
//    myservo.write(0);
//    delay(1000);
    b = countB;
    Serial.println("\n");
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW);
   } 
   else if(flag==4) {
      flag=0;
   }
   counter=0;
//   if(r > g and r > b) red();
//   else if(g > r and g > b) green();
//   else if(b > r and b > g) blue();
//   Serial.println("ISR");
   
}

void loop() {
  TCS();
  while(1);
}
