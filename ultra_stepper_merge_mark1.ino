#include <NoDelayTimerTask.h>
#include <UltrasonicSensor.h>
#include <Stepper.h>
#include<Servo.h>

int StepsPerRev = 48 , PointsPerRev = 360 , TimePerPoint = 20 , TimePerPoint2 = 20;
int scanningFrequency = 180; // scans(points) per sec
//int StepperTime , UltraTime , StepperSpeed;

int UltraTime = PointsPerRev * TimePerPoint ;
int StepperTime = UltraTime ;
int StepperSpeed = StepperTime / 60 ;
int TimePerStep = StepperTime / StepsPerRev ;

int *TimePerPointPtr = &TimePerPoint ;

int i=0,j=0,k=0;
int Xp ,Yp ,Zp , Distance , Table = 30, HeightPrecision = 1/7, SetAngle = 142;
int Flag1=0,Flag2=1;

Stepper rotating_table( StepsPerRev ,4,5,6,7);
Stepper height_adjust ( 200 , 8,9,10,11);
UltrasonicSensor ultra(3,2);
Servo servo;
NoDelayTimerTask timer_ultra(*TimePerPointPtr),timer_stepper(TimePerStep);
void setup(){
  // put your setup code here, to run once:
  Serial.begin(9600);
  ultra.setTemperature(33);
  rotating_table.setSpeed(30);  
  Serial.println("ready");
  while(!Serial.available()){
    Flag1=0;
    }
   Flag1=1;
   servo.attach(3);
   servo.write(SetAngle);
}

void loop() {
  if(Flag1){
    if(Flag2){
      if (timer_ultra.isTimeUp()){
        timer_ultra.resetTimer();
        int Time1 = millis();
        int distance = ultra.distanceInMillimeters();
        Xp = (Table-Distance)*cos(j*3.14/180);
        Yp = (Table-Distance)*sin(j*3.14/180);
        Zp = k;
        Serial.print(Distance);  
        Serial.print("    ");
        Serial.println(i);
        TimePerPointPtr = TimePerPoint2-millis()+Time1;
        j+= 360/PointsPerRev;
          if(j>PointsPerRev){
            j=0;
            Flag2=0;
          }
      }
      if (timer_stepper.isTimeUp()){
        timer_stepper.resetTimer();
        rotating_table.step(1);
        /*Serial.print("             steps  :");
        Serial.println(i);*/
        i++;
      }
    }
    else{
      k+= HeightPrecision ;
      height_adjust.step(HeightPrecision);
    }
}
}
