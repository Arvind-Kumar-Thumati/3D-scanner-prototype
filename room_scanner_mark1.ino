#include <TFMPlus.h>

#include <SoftwareSerial.h>
//#include <UltrasonicSensor.h>
//#include<math.h>
#include <Stepper.h>

#include<NoDelayTimerTask.h>
#include <Servo.h>

Servo servo;
Stepper mystepper(200,4,5,6,7);
Stepper height_adjust(200,8,9,10,11);
//UltrasonicSensor ultrasonic(4,5);
SoftwareSerial Serial1(2,3);
TFMPlus tfmp;
float distance, hypotenuse;
int start_angle = 0 , end_angle = 180 , num_scans= 35;
float i=0 , j=0 , flag=0;
float y, x ,z ;
int lidar_dist();
int check; //save check value
int i1 ;
uint16_t dist , flux ,temp;
int uart[9]; //save data measured by LiDAR
const int HEADER=0x59; //frame header of data package

/*int lidar_dist(){
  if (Serial1.available()) { //check if serial port has data input
    if(Serial1.read() == HEADER) { //assess data package frame header 0x59
      uart[0]=HEADER;
        if (Serial1.read() == HEADER) { //assess data package frame header 0x59
          uart[1] = HEADER;
          for (i1 = 2; i1 < 9; i1++) { //save data in array
            uart[i1] = Serial1.read();
          }
          check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
          if (uart[8] == (check & 0xff)){ //verify the received data as per protocol
            dist = uart[2] + uart[3] * 256;
          }
          delay(10);
          return dist;
        }
    }
  }
}
*/
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  delay(20);
  tfmp.begin( &Serial1);
  mystepper.setSpeed(30);// 1
  height_adjust.setSpeed(100);
  //ultrasonic.setTemperature(32);
  Serial.println("ready");
  while(!Serial.available()){
    //char incoming = Serial.read();
    //Serial.println(incoming);
    flag=0;
    }
  
  flag=1;
  servo.attach(12);
}

void loop() {
  if(flag==1){
    for ( j=1 ; j<= num_scans ;j++){
      for(i = start_angle ; i<= end_angle ; i++){
        
        servo.write(i);
        //distance = lidar_dist();
        delay(10);
        tfmp.getData(dist,flux,temp);
        //distance = ultrasonic.distanceInCentimeters();
        Serial.print(dist);
        Serial.print(" ");
        //Serial.print(distance);
        //Serial.print(" ");
        Serial.print(90+i);
        Serial.print(" ");
        Serial.println(j*1.8);
        
      }
      mystepper.step(1);
      servo.write(0);
      delay(200);
    }
    Serial.println("end");
    flag=0;
  }
}
