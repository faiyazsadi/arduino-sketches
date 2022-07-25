/* This code works with GY-31 TCS3200 TCS230 color sensor module
 * It select a photodiode set and read its value (Red Set/Blue set/Green set) and displays it on the Serial monitor
 * Refer to www.surtrtech.com for more details
 */

#include<Servo.h>

#define s0 3       //Module pins wiring
#define s1 4
#define s2 5
#define s3 6
#define out 2
Servo top_servo, bottom_servo;

int data=0;        //This is where we're going to stock our values
int r, g, b;

void setup() 
{
   pinMode(s0,OUTPUT);    //pin modes
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);
   top_servo.attach(12);
   bottom_servo.attach(10);   
   Serial.begin(9600);   //intialize the serial monitor baud rate
   
   digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100% (recommended)
   digitalWrite(s1,HIGH); //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%
   
}

void top_servo_rotate(int pos) {
  int cur = top_servo.read();
  while(top_servo.read() != pos) {
    if(cur < pos) {
      cur++;
    } else if(cur > pos) {
      cur--;
    }
    top_servo.write(cur);
    delay(10);
  }
}
void servo_rotate(int pos) {
  int cur = bottom_servo.read();
  while(bottom_servo.read() != pos) {
    if(cur < pos) {
      cur++;
    } else if(cur > pos) {
      cur--;
    }
    bottom_servo.write(cur);
    delay(15);
  }
}
void red() {
//  bottom_servo.write(60);
  servo_rotate(25);
}
void green() {
//  bottom_servo.write(90);
  servo_rotate(60);
}
void blue() {
//  bottom_servo.write(110);
  servo_rotate(95);
}
void black() {
  servo_rotate(130);
}
void others(){
  servo_rotate(160);}
void loop()                  //Every 2s we select a photodiodes set and read its data
{
   top_servo.write(0);
   delay(3000);
//   top_servo.write(40);
   top_servo_rotate(40);
   delay(2000);
   
   for(int i = 0; i < 5; ++i) {
    digitalWrite(s2,LOW);        //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
    digitalWrite(s3,LOW);
    Serial.print("Red value= "); 
    r = GetData();                   //Executing GetData function to get the value

    digitalWrite(s2,LOW);
    digitalWrite(s3,HIGH);
    Serial.print("Blue value= ");
    b = GetData();

    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);
    Serial.print("Green value= ");
    g = GetData();
   
    Serial.println();
//    digitalWrite(s0,LOW);
//    digitalWrite(s1,LOW);
    digitalWrite(s0,HIGH);
    digitalWrite(s1,HIGH);
   }
   Serial.println("");
   
   if(r < g and r < b)
   {if(g<b)others();
   else red();}
   else if(g < r and g < b) green();
   else if(b < r and b < g and b <= 16)
   {if(g<r)blue();
   else others();}
   else if(b < r and b < g and b >= 18) black();
   else if(r < g and r < b and g<b) others(); //yellow

   delay(2000);
//   top_servo.write(90);
   top_servo_rotate(90);
   delay(1000);
   
//   myservo.write(0);
//   delay(1000);
   
   
}

int GetData(){
   data=pulseIn(out,LOW);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
   Serial.print(data);          //it's a time duration measured, which is related to frequency as the sensor gives a frequency depending on the color
   Serial.print("\t");          //The higher the frequency the lower the duration
   delay(20);
   return data;
}
