/*!
 * @file RcPwmChannel.cpp
 */

#include <Arduino.h>
#include <RcPwmChannel.h>

/*!
 *    @brief  Constructor for RcPwmChannel object without center point, without deadzone. Pulse lengths can be determined with PulseLengthDeterminer.cpp
 *    @param  pin The pin # the pwm signal is connected to
 *    @param  maxMsBetweenUpdates Max ms between good signal reads before signal is considered unhealthy
 *    @param  lowPulseLength low pulse length used to convert signal to percent - counts as 0%
 *    @param  highPulseLength high pulse length used to convert signal to percent - counts as 100%
 *    @param  invalidLowThreshold low pulse threshold to count as invalid signal
 *    @param  invalidHighThreshold high pulse threshold to count as invalid signal
 */
RcPwmChannel::RcPwmChannel(int pin, unsigned long maxMsBetweenUpdates,
                          unsigned long lowPulseLength, unsigned long highPulseLength,
                          unsigned long invalidLowThreshold, unsigned long invalidHighThreshold)
{
  _PIN = pin;
  pinMode(_PIN, INPUT);

  _pulseLength = 0;
  _pulseStartTime = 0;
  _lastGoodSignal = 0;
  _updatesDisabled = 0;

  _MAX_MS_BETWEEN_RC_UPDATES = maxMsBetweenUpdates;
  _INVALID_LOW_THRESHOLD = invalidLowThreshold;
  _INVALID_HIGH_THRESHOLD = invalidHighThreshold;

  _LOW_PULSE_LENGTH = lowPulseLength;
  _CENTER_PULSE_LENGTH = 0;
  _HIGH_PULSE_LENGTH = highPulseLength;

  _LOW_DEADZONE_LENGTH = 0;
  _CENTER_DEADZONE_LENGTH = 0;
  _CENTER_HALF_DEADZONE_LENGTH = (unsigned long)(_CENTER_DEADZONE_LENGTH/2);
  _HIGH_DEADZONE_LENGTH = 0; 
}

/*!
 *    @brief  Constructor for RcPwmChannel object without center point, with deadzone. Pulse lengths can be determined with PulseLengthDeterminer.cpp
 *    @param  pin The pin # the pwm signal is connected to
 *    @param  maxMsBetweenUpdates Max ms between good signal reads before signal is considered unhealthy
 *    @param  lowPulseLength low pulse length used to convert signal to percent - counts as 0%
 *    @param  lowerDeadzoneWidth lower pulse range deadzone width - pulses in deadzone count as 0%
 *    @param  highPulseLength high pulse length used to convert signal to percent - counts as 100%
 *    @param  higherDeadzoneWidth higher pulse range deadzone width - pulses in deadzone count as 100%
 *    @param  invalidLowThreshold low pulse threshold to count as invalid signal
 *    @param  invalidHighThreshold high pulse threshold to count as invalid signal
 */
RcPwmChannel::RcPwmChannel(int pin, unsigned long maxMsBetweenUpdates,
                          unsigned long lowPulseLength, unsigned long lowerDeadzoneWidth,
                          unsigned long highPulseLength, unsigned long higherDeadzoneWidth,
                          unsigned long invalidLowThreshold, unsigned long invalidHighThreshold)
{
  _PIN = pin;
  pinMode(_PIN, INPUT);

  _pulseLength = 0;
  _pulseStartTime = 0;
  _lastGoodSignal = 0;
  _updatesDisabled = 0;

  _MAX_MS_BETWEEN_RC_UPDATES = maxMsBetweenUpdates;
  _INVALID_LOW_THRESHOLD = invalidLowThreshold;
  _INVALID_HIGH_THRESHOLD = invalidHighThreshold;

  _LOW_PULSE_LENGTH = lowPulseLength;
  _CENTER_PULSE_LENGTH = 0;
  _HIGH_PULSE_LENGTH = highPulseLength;

  _LOW_DEADZONE_LENGTH = lowerDeadzoneWidth;
  _CENTER_DEADZONE_LENGTH = 0;
  _CENTER_HALF_DEADZONE_LENGTH = (unsigned long)(_CENTER_DEADZONE_LENGTH/2);
  _HIGH_DEADZONE_LENGTH = higherDeadzoneWidth; 
}

/*!
 *    @brief  Constructor for RcPwmChannel object with center point, without deadzone. Pulse lengths can be determined with PulseLengthDeterminer.cpp
 *    @param  pin The pin # the pwm signal is connected to
 *    @param  maxMsBetweenUpdates Max ms between good signal reads before signal is considered unhealthy
 *    @param  lowPulseLength low pulse length used to convert signal to percent - counts as -100%
 *    @param  centerPulseLength center pulse length used to convert signal to percent - counts as 0%
 *    @param  highPulseLength high pulse length used to convert signal to percent - counts as 100%
 *    @param  invalidLowThreshold low pulse threshold to count as invalid signal
 *    @param  invalidHighThreshold high pulse threshold to count as invalid signal
 */
RcPwmChannel::RcPwmChannel(int pin, unsigned long maxMsBetweenUpdates,
                          unsigned long lowPulseLength, unsigned long centerPulseLength, unsigned long highPulseLength,
                          unsigned long invalidLowThreshold, unsigned long invalidHighThreshold)
{
  _PIN = pin;
  pinMode(_PIN, INPUT);

  _pulseLength = 0;
  _pulseStartTime = 0;
  _lastGoodSignal = 0;
  _updatesDisabled = 0;

  _MAX_MS_BETWEEN_RC_UPDATES = maxMsBetweenUpdates;
  _INVALID_LOW_THRESHOLD = invalidLowThreshold;
  _INVALID_HIGH_THRESHOLD = invalidHighThreshold;

  _LOW_PULSE_LENGTH = lowPulseLength;
  _CENTER_PULSE_LENGTH = centerPulseLength;
  _HIGH_PULSE_LENGTH = highPulseLength;

  _LOW_DEADZONE_LENGTH = 0;
  _CENTER_DEADZONE_LENGTH = 0;
  _CENTER_HALF_DEADZONE_LENGTH = (unsigned long)(_CENTER_DEADZONE_LENGTH/2);
  _HIGH_DEADZONE_LENGTH = 0; 
}

/*!
 *    @brief  Constructor for RcPwmChannel object with center point, without deadzone. Pulse lengths can be determined with PulseLengthDeterminer.cpp
 *    @param  pin The pin # the pwm signal is connected to
 *    @param  maxMsBetweenUpdates Max ms between good signal reads before signal is considered unhealthy
 *    @param  lowPulseLength low pulse length used to convert signal to percent - counts as -100%
 *    @param  lowerDeadzoneWidth lower pulse range deadzone width - pulses in deadzone count as -100%
 *    @param  centerPulseLength low pulse length used to convert signal to percent - counts as 0%
 *    @param  centerDeadzoneWidth center pulse range deadzone width - pulses in deadzone count as 0%
 *    @param  highPulseLength high pulse length used to convert signal to percent - counts as 100%
 *    @param  higherDeadzoneWidth higher pulse range deadzone width - pulses in deadzone count as 100%
 *    @param  invalidLowThreshold low pulse threshold to count as invalid signal
 *    @param  invalidHighThreshold high pulse threshold to count as invalid signal
 */
RcPwmChannel::RcPwmChannel(int pin, unsigned long maxMsBetweenUpdates,
                          unsigned long lowPulseLength, unsigned long lowerDeadzoneWidth, 
                          unsigned long centerPulseLength, unsigned long centerDeadzoneWidth,
                          unsigned long highPulseLength, unsigned long higherDeadzoneWidth,
                          unsigned long invalidLowThreshold, unsigned long invalidHighThreshold)
{
  _PIN = pin;
  pinMode(_PIN, INPUT);

  _pulseLength = 0;
  _pulseStartTime = 0;
  _lastGoodSignal = 0;
  _updatesDisabled = 0;

  _MAX_MS_BETWEEN_RC_UPDATES = maxMsBetweenUpdates;
  _INVALID_LOW_THRESHOLD = invalidLowThreshold;
  _INVALID_HIGH_THRESHOLD = invalidHighThreshold;

  _LOW_PULSE_LENGTH = lowPulseLength;
  _CENTER_PULSE_LENGTH = centerPulseLength;
  _HIGH_PULSE_LENGTH = highPulseLength;

  _LOW_DEADZONE_LENGTH = lowerDeadzoneWidth;
  _CENTER_DEADZONE_LENGTH = centerDeadzoneWidth;
  _CENTER_HALF_DEADZONE_LENGTH = (unsigned long)(_CENTER_DEADZONE_LENGTH/2);
  _HIGH_DEADZONE_LENGTH = higherDeadzoneWidth; 
}

/*!
 *    @brief  Function to call on pin change interrupt ISR to update timings of pulses
 */
void RcPwmChannel::updatePwmChannel()
{
  //if we are using the rc channel info - don't update it!

  if (_updatesDisabled == true) return;
  
  int currentState = digitalRead(_PIN);

  //pulse started
  if (currentState == HIGH) {
    _pulseStartTime = micros();
  }

  //pulse ended
  if (currentState == LOW) {
    //check if micros() didn't overflow
    if (micros() > _pulseStartTime) {
      unsigned long newPulseLenght = micros() - _pulseStartTime;
      //check if pulse length within limits -> healthy signal
      if (newPulseLenght <= _HIGH_PULSE_LENGTH && newPulseLenght >= _LOW_PULSE_LENGTH) {
        _pulseLength = newPulseLenght;
        _lastGoodSignal = millis();
      }
    }
  }
}

/*!
 *    @returns pulseLength in microseconds
 */
unsigned long RcPwmChannel::getPulseLength()
{
  return(_pulseLength);
}

int RcPwmChannel::_convertPulseLengthPercent()
{
  _updatesDisabled = 1;
  unsigned long pulseLength = _pulseLength;
  _updatesDisabled = 0;

  //low-center
  if (pulseLength<_CENTER_PULSE_LENGTH){
    int percent = map(pulseLength, _LOW_PULSE_LENGTH+_LOW_DEADZONE_LENGTH, _CENTER_PULSE_LENGTH-_CENTER_HALF_DEADZONE_LENGTH, -100, 0);
    if (percent<-100) return -100;  //cutoff low deadband
    else if (percent>0) return 0;  //cutoff center deadband
    else return percent;
  }

  //center-high
  else {
    int percent = map(pulseLength,_CENTER_PULSE_LENGTH+_CENTER_HALF_DEADZONE_LENGTH, _HIGH_PULSE_LENGTH-_HIGH_DEADZONE_LENGTH, 0, 100);
    if (percent<0) return 0;  //cutoff center deadband
    else if (percent>100) return 100;  //cutoff high deadband
    else return percent;
  }
}

int RcPwmChannel::_convertPulseLengthPercentWithoutCenter()
{
  unsigned long pulseLength = _pulseLength;
  _updatesDisabled = 0;

  //low-high
  int percent = map(pulseLength, _LOW_PULSE_LENGTH+_LOW_DEADZONE_LENGTH, _HIGH_PULSE_LENGTH-_HIGH_DEADZONE_LENGTH, 0, 100);
  if (percent<0) return 0;  //cutoff low deadband
  else if (percent>100) return 100;  //cutoff high deadband
  else return percent;
}

/*!
 *    @returns  int which is signal in percent ranging from 0 to 100 when no center is given, -100 to 100 when center is given
 */
int RcPwmChannel::getSignalPercent(){
  if(_CENTER_PULSE_LENGTH != 0) return _convertPulseLengthPercent();
  else return _convertPulseLengthPercentWithoutCenter();
}

/*!
 *    @brief Evaluates if rc signal is healthy based on given valid pulse range and max ms between valid signal reads
 *    @returns Bool: true if signal is healthy, else false
 */
bool RcPwmChannel::rcSignalIsHealthy(){
  _updatesDisabled = 1;
  unsigned long lastGoodSignal = _lastGoodSignal;
  _updatesDisabled = 0;

  if (lastGoodSignal == 0) return false; //no good signal yet
  else if (millis() - lastGoodSignal > _MAX_MS_BETWEEN_RC_UPDATES) return false;
  else return true;
}