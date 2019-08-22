#include <UltrasonicSensor.h>
//#include<math.h>
#include <Stepper.h>

#include<NoDelayTimerTask.h>
#include <Servo.h>

Servo servo;
NoDelayTimerTask timer1(140),timer2(1);// 140 , 0
Stepper mystepper(200,4,5,6,7);
Stepper height_adjust(200,8,9,10,11);
UltrasonicSensor ultrasonic(3,2);
float distance, hypotenuse, approx, angle=0 , set_angle =145 , ini_distance ,height,table=300 , prev_dist = 0 ;
int flag2=1;

float i=0 , j=0 , flag=0,k=0;
float y=1 , x ,z;
float height_acc=2 , rot_acc= 7.5 , act_angle = 145;

void setup() {
  Serial.begin(9600);
  mystepper.setSpeed(30);// 1
  height_adjust.setSpeed(100);
  ultrasonic.setTemperature(32);
  Serial.println("ready");
  while(!Serial.available()){
    //char incoming = Serial.read();
    //Serial.println(incoming);
    flag=0;
    }
   flag=1;
   servo.attach(12);
   servo.write(set_angle);
   /*ini_distance = ultrasonic.distanceInMillimeters();
   angle-=1;
   servo.write(set_angle+angle);
   //Serial.println(ini_distance);
  while (flag2==1) {
    hypotenuse =ultrasonic.distanceInMillimeters(); 
    approx = ini_distance/cos(angle*3.14/180);
    if ((hypotenuse<(approx+100))&&(approx>(approx-100))){
      flag2=1;
      angle-=1;
      servo.write(set_angle+angle);
      //Serial.println("one step");     
      delay(100);
    }
    else {
      flag2=0;
      //Serial.println(tan(angle*3.14/180)*ini_distance);
      height = -1*tan(angle*3.14/180)*ini_distance;
      //Serial.println(height);
      act_angle = angle;
      delay(5000);
    }
    
}*/
servo.write(set_angle);
angle = 0;
}

void loop() {
 
 if(flag==1){
  if (timer2.isTimeUp())
  {
    if(k>=10){
      Serial.println("end");
      delay(5000);
    }
    /*if(act_angle>angle){
    Serial.println("end");
    delay(5000);
  }*/
    if(i!=0)
    {
      timer2.resetTimer();
    float hypotenuse_plot = ultrasonic.distanceInMillimeters();
    //float distance_plot = -1*hypotenuse_plot*cos(angle*3.14/180);
    //Serial.println(val);
    if(hypotenuse_plot<table){
    x=(table-hypotenuse_plot)*cos(i*3.14/180);
    z=(table-hypotenuse_plot)*sin(i*3.14/180);
    //y=(distance_plot)*sin(angle*3.14/180);
    Serial.print(x);
    Serial.print(" ");
    Serial.print(y);
    Serial.print(" ");
    Serial.println(z);
    }
    else{
      //Serial.println("0 0 0");
    }
    if(i>=360){
      i=0;
      k++;
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      height_adjust.step(0.7*200*10);
      y+= height_acc;
      //angle-=(height_acc);
      //servo.write(set_angle+angle);  
    }
    /*Serial.print(" ");
    Serial.print(i);
    Serial.print(" ");
    Serial.println(j);
    */
  /*if(act_angle>angle){
    Serial.println("end");
    delay(5000);
  }*/
    /*Serial.println(val);
    Serial.print("         ");
    Serial.println(j);*/
    j++;
  }
  }
  if (timer1.isTimeUp())
  {
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    timer1.resetTimer();
    mystepper.step(1);
    //Serial.print("One Step      ");
    //Serial.println(i);
    i=i+1.8;
  }
 }
}
