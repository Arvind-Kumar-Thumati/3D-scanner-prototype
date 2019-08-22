#include<UltrasonicSensor.h>
#include<Servo.h>
UltrasonicSensor ultra(9,8);
Servo servo;
float distance, hypotenuse, approx, angle=0 , set_angle =142 , ini_distance ,i=1 ;
int flag=1;
void setup() {
   Serial.begin(9600);
   ultra.setTemperature(33);
   servo.attach(3);
   //servo.write(0);
   servo.write(set_angle);
   delay(2000);
   ini_distance = ultra.distanceInMillimeters();
   angle-=1;
   servo.write(set_angle+angle);
   Serial.println(ini_distance);
}
void loop (){
  while (flag==1) {
    hypotenuse =ultra.distanceInMillimeters(); 
    /*if(i==1){
      approx = hypotenuse/cos(angle*3.14/180);
    }
    else*/
    approx = ini_distance/(cos(angle*3.14/180));
    if ((hypotenuse<=(approx+200))&&(hypotenuse>=(approx-200))){
      flag=1;
      angle--;
      servo.write(set_angle+angle);
      Serial.println("step\t\tapprox\thypot\tangle\theight");
      Serial.print("one step");     
      Serial.print("\t");
      Serial.print(approx);
      Serial.print("\t");      
      Serial.print(hypotenuse);
      Serial.print("\t");
      Serial.print(angle);
      Serial.print("\t");
      Serial.println(-1*tan(angle*3.14/180)*ini_distance);
      delay(50);
    }
    else {
      flag=0;
      Serial.print(approx);
      Serial.print("\t");      
      Serial.print(hypotenuse);
      Serial.print("\t");
      Serial.print(angle);
      Serial.print("\t");
      Serial.println(-1*tan(angle*3.14/180)*ini_distance);
      Serial.println("***********************");
      Serial.println(-1*tan(angle*3.14/180)*ini_distance);
      Serial.println("***********************");
      delay(5000);
    }
    servo.write(set_angle);
}
}
