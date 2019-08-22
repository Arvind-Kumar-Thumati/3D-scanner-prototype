#include <NoDelayTimerTask.h>
#include <UltrasonicSensor.h>
#include <Stepper.h>
#include <Servo.h>
//////////////////////////////  ROTATING TABLE  ///////////////////////////
int StepsPerRev = 200 , PointsPerRev = 720 , TimePerPoint = 15 , TimePerPoint2 = 15;// 15 for 720 points with 100 rpm // 40 for 360 points with 60 rpm
int UltraTime = PointsPerRev * TimePerPoint ; // Time taken by ultra for scanning PointsPerRev points
int StepperTime = UltraTime ; // Time taken by stepper for moving StepsPerRev steps
int StepperSpeed = StepperTime / 60 ;
int TimePerStep = StepperTime / StepsPerRev ; // Time taken by stepper to take one step

int *TimePerPointPtr = &TimePerPoint ; // Time taken by ultra to scan one point

////////////////////////////// HEIGHT ADJUST  /////////////////////////////

float HeightPrecision = 1/7; // Minimum height movable for one revolution with the setup i.e 7 revolutions for 1cm or 10mm => for 1mm 0.7 rev
float OneMm = (1/(HeightPrecision*10)) * 200 ; //Steps of HeightPrecision // 0.7*StepsPerRev
float Height_acc = 2 ; // in mms
//down = +ve up = -ve
//////////////////////////////  SCANNER  //////////////////////////////////

int i=0,j=0,k=0;
int Xp ,Yp ,Zp , Distance , Table = 300, SetAngle = 142;
int Flag1=0,Flag2=1;

/////////////////////////////  CLASS INSTANCES  ///////////////////////////

Stepper rotating_table( StepsPerRev ,4,5,6,7);
Stepper height_adjust ( 200 , 8,9,10,11);
UltrasonicSensor ultra(3,2);
Servo servo ;
NoDelayTimerTask timer_ultra(*TimePerPointPtr),timer_stepper(TimePerStep);

////////////////////////////  MAIN FUNCTION  /////////////////////////////
int counter=0;
void setup(){
  // put your setup code here, to run once:
  Serial.begin(9600);
  ultra.setTemperature(33);
  rotating_table.setSpeed(30);  
  height_adjust.setSpeed(100);//100
  Serial.println("ready");
  while(!Serial.available()){
    Flag1=0;
    }
   Flag1=1;
   servo.attach(12);
   servo.write(SetAngle);
}

void loop() {
  if(Flag1){ // To check for serial 
    if(Flag2){ // To check for height adjustment 
      if (timer_ultra.isTimeUp()){  // To check for ultra timer timeup
        timer_ultra.resetTimer();
        int Time1 = millis();
        int Distance = ultra.distanceInMillimeters();
        counter++;
        if(Distance<Table){
        Xp = (Table-Distance)*cos(j*3.14/180); //  Calculating x point from ultra distance using circle's equation
        Yp = (Table-Distance)*sin(j*3.14/180); //  Calculating y point from ultra distance using circle's equation 
        Zp = k;
        Serial.print(Xp);  
        Serial.print(" ");
        Serial.print(Yp);  
        Serial.print(" ");
        Serial.println(Zp);  
        }
        else{
          Serial.println("0 0 0");
        }
        //Serial.print(Table-Distance);
        //Serial.print("  ");
        //Serial.println(counter);
        
        TimePerPointPtr = TimePerPoint2-millis()+Time1;
        j+= 360/PointsPerRev;
          if(j>PointsPerRev){
            j=0;
            Flag2=0;
          }
          else if(i>=200){
            i=0;
            Flag2=0;
          }
      }
      if (timer_stepper.isTimeUp()){
        timer_stepper.resetTimer();
        digitalWrite(8,LOW);
        digitalWrite(9,LOW);
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
        rotating_table.step(1);
        Serial.print("             steps  :");
        Serial.println(i);
        i++;
      }
    }
    else{
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      k+= 2 ;
      height_adjust.step(10*OneMm);
      Serial.println("Rotated");
      Flag2=1;
      //timer_stepper.resetTimer();
      //timer_ultra.resetTimer();
      if(k>=16){
        Serial.println("end");
      }    
    }
  }
}
