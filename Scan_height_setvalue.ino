#include <Servo.h>
#include <NoDelayTimerTask.h>
#include <UltrasonicSensor.h>
int pot=A0,ini_distance,angle;
UltrasonicSensor ultrasonic(3,2);
Servo servo;
void setup() {
  Serial.begin(9600);
  servo.attach(12);
  pinMode(A0,INPUT);
  int temperature = 33;
  angle=100;
  servo.write(145);
  ultrasonic.setTemperature(temperature);
  ini_distance=ultrasonic.distanceInMillimeters();
}

void loop() {
  int distance = ultrasonic.distanceInMillimeters();
  //int val = analogRead(A0);
  //val = map(val,0,1023,0,360);
  //servo.write(val);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" mm    Angle: ");
//  Serial.print(val);
  Serial.print("   ");
  //Serial.println(ini_distance/cos((val-angle)*3.14/180));
}
