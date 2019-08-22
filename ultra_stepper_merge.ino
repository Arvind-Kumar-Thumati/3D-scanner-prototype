#include <NoDelayTimerTask.h>
#include <UltrasonicSensor.h>
#include <Stepper.h>

int StepsPerRev = 48 , PointsPerRev = 360 , TimePerPoint = 15 , TimePerPoint2 = 15 ;
int scanningFrequency = 180; // scans(points) per sec
//int StepperTime , UltraTime , StepperSpeed;

int UltraTime = PointsPerRev * TimePerPoint ;
int StepperTime = UltraTime ;
int StepperSpeed = StepperTime / 60 ;
int TimePerStep = StepperTime / StepsPerRev ;

int *TimePerPointPtr = &TimePerPoint ;

int i=1,j=1;
Stepper stepper( StepsPerRev ,4,5,6,7);
UltrasonicSensor ultra(9,8);
NoDelayTimerTask timer_ultra(*TimePerPointPtr),timer_stepper(TimePerStep);
void setup(){  
  // put your setup code here, to run once:
  Serial.begin(9600);
  ultra.setTemperature(33);
  stepper.setSpeed(30);  
}

void loop() {
  if (timer_ultra.isTimeUp()){
    timer_ultra.resetTimer();
    int time1 = millis();
    int distance = ultra.distanceInMillimeters();
    Serial.print(distance);  
    Serial.print("    ");
    Serial.println(i);
    TimePerPointPtr = TimePerPoint2-millis()+time1;
    i++;
    if(i>PointsPerRev){
      i=1;
    }
  }
  if (timer_stepper.isTimeUp()){
    timer_stepper.resetTimer();
    stepper.step(1);
    Serial.print("             steps  :");
    Serial.println(j);
    j++;
    if (j>StepsPerRev){
      j=1;
      i=1;
    }
  }

}
