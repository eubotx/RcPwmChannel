/*!
 *  @file RcPwmChannel1.h
 *
 *  This is a library for RC Receveivers which transmit data via PWM to the microcontroller.
 *  It reads the pwm inputs with interrupts. Each channel connected to an indivdual pin needs to be an own instance of this class.
 * 
 *
 *  written by Florian Geisser ~ eubotx
 *  MIT licensed
 */

#ifndef RcPwmChannel_h
#define RcPwmChannel_h

#include <Arduino.h>

class RcPwmChannel
{
public:
  //no center, no deadzone
  RcPwmChannel(int pin,unsigned long maxMsBetweenUpdates,
              unsigned long lowPulseLength, unsigned long highPulseLength,
              unsigned long invalidLowThreshold, unsigned long invalidHighThreshold);
  //no center, deadzone
  RcPwmChannel(int pin, unsigned long maxMsBetweenUpdates,
              unsigned long lowPulseLength, unsigned long lowerDeadzoneWidth,
              unsigned long highPulseLength, unsigned long higherDeadzoneWidth,
              unsigned long invalidLowThreshold, unsigned long invalidHighThreshold);

  //center, no deadzone
  RcPwmChannel(int pin, unsigned long maxMsBetweenUpdates,
              unsigned long lowPulseLength, unsigned long centerPulseLength, unsigned long highPulseLength,
              unsigned long invalidLowThreshold, unsigned long invalidHighThreshold);

  //center, deadzone
  RcPwmChannel(int pin, unsigned long maxMsBetweenUpdates,
              unsigned long lowPulseLength, unsigned long lowerDeadzoneWidth, 
              unsigned long centerPulseLength, unsigned long centerDeadzoneWidth,
              unsigned long highPulseLength, unsigned long higherDeadzoneWidth,
              unsigned long invalidLowThreshold, unsigned long invalidHighThreshold);

  void updatePwmChannel();
  unsigned long getPulseLength();
  int getSignalPercent();
  bool rcSignalIsHealthy();

private:
    int _PIN;

    unsigned long _pulseLength;
    unsigned long _pulseStartTime;
    unsigned long _lastGoodSignal;

    bool _updatesDisabled;

    unsigned long _MAX_MS_BETWEEN_RC_UPDATES;

    unsigned long _INVALID_LOW_THRESHOLD;
    unsigned long _INVALID_HIGH_THRESHOLD;

    unsigned long _LOW_PULSE_LENGTH;
    unsigned long _CENTER_PULSE_LENGTH;
    unsigned long _HIGH_PULSE_LENGTH;

    unsigned long _LOW_DEADZONE_LENGTH;
    unsigned long _CENTER_DEADZONE_LENGTH;
    unsigned long _CENTER_HALF_DEADZONE_LENGTH;
    unsigned long _HIGH_DEADZONE_LENGTH;

    int _convertPulseLengthPercent();
    int _convertPulseLengthPercentWithoutCenter();

};

#endif