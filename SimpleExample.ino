#include<NoDelayTimerTask.h>

//Set timer1 to a delay of 1 second and timer2 to a delay of 2 seconds
NoDelayTimerTask timer1(1000),timer2(2000);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (timer1.isTimeUp())
  {
    timer1.resetTimer();
    Serial.println("Timer1 triggered");
  }
  if (timer2.isTimeUp())
  {
    timer2.resetTimer();
    Serial.println("Timer2 triggered");
  }
}