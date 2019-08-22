/* NoDelayTimerTask, created by John Adlington
	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "Arduino.h"

#ifndef NoDelayTimerTask_h
#define NoDelayTimerTask_h

class NoDelayTimerTask
{
  private:
  //LastTime is the last time the object was reset or created
    unsigned long LastTime = millis(), DesiredDelay;
    NoDelayTimerTask();//Forces you to specify a desired delay time
    int phase=0,StartPhase=-1,EndPhase=-1;

  public:
    NoDelayTimerTask(unsigned long ms);
//Optionally used if you want to set a program phase:
    NoDelayTimerTask(unsigned long ms,int newStartPhase,int newEndPhase);
    unsigned long getElapsedTime();
    //Used if you wish to change the delay after creation
    void setDelay(unsigned long l);
    /*
     * ALWAYS manually reset or it won't work
     */
    boolean isTimeUp();

    void resetTimer();
//Optionally used for phases of execution e.g. a sequence of LEDs:
    int getPhase();
    void setPhase(int newPhase);
    void incrementPhase();
};

#endif