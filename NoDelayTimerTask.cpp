/* NoDelayTimerTask, created by John Adlington
	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "NoDelayTimerTask.h"

    NoDelayTimerTask::NoDelayTimerTask(unsigned long ms) {
      DesiredDelay = ms;
    }
    NoDelayTimerTask::NoDelayTimerTask(unsigned long ms,int newStartPhase, int newEndPhase) {
      DesiredDelay = ms;
      StartPhase = newStartPhase; EndPhase = newEndPhase;
    }

    unsigned long NoDelayTimerTask::getElapsedTime(){
      return millis() - LastTime;
    }

    //Used if you wish to change the delay after creation
    void NoDelayTimerTask::setDelay(unsigned long l){
      DesiredDelay=l;
    }
    /*
     * Remember to use resetTimer() when the time is up
     */
    boolean NoDelayTimerTask::isTimeUp()
    {
      return (millis() - LastTime) >= DesiredDelay;
    }
    
    void NoDelayTimerTask::resetTimer()
    {
      LastTime = millis();
    }

    int NoDelayTimerTask::getPhase()
    {
      return phase;
    }

    void NoDelayTimerTask::setPhase(int newPhase)
    {
      phase = newPhase;
    }

    void NoDelayTimerTask::incrementPhase()
    {
      phase++;
      if(phase>EndPhase){phase=StartPhase;}
    }