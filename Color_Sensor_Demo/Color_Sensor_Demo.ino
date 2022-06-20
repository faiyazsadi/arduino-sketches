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
Servo myservo;
int data=0;        //This is where we're going to stock our values

int r, g, b;

void setup() 
{
   pinMode(s0,OUTPUT);    //pin modes
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);
   myservo.attach(9);
   
   Serial.begin(9600);   //intialize the serial monitor baud rate
   
   digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100% (recommended)
   digitalWrite(s1,HIGH); //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%
   
}

void red() {
  myservo.write(35);
}
void green() {
  myservo.write(90);
}
void blue() {
  myservo.write(170);
}

void loop()                  //Every 2s we select a photodiodes set and read its data
{

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
   digitalWrite(s0,LOW);
   digitalWrite(s1,LOW);
   
   if(r < g and r < b) red();
   else if(g < r and g < b) green();
   else if(b < r and b < g) blue();
   
   delay(2000);
   myservo.write(0);
   delay(1000);
   
   digitalWrite(s0,HIGH);
   digitalWrite(s1,HIGH);
}

int GetData(){
   data=pulseIn(out,LOW);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
   Serial.print(data);          //it's a time duration measured, which is related to frequency as the sensor gives a frequency depending on the color
   Serial.print("\t");          //The higher the frequency the lower the duration
   delay(20);
   return data;
}
