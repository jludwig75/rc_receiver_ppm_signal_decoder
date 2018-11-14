#include "RemoteControl.h"

#define PPM_MIN_TIME  1100
#define PPM_MAX_TIME  1900


RemoteControl::RemoteControl(byte drive_signal_pin, byte steering_signal_pin) :
  _drive_signal(drive_signal_pin),
  _steering_signal(steering_signal_pin)
{
}

bool RemoteControl::begin()
{
  if (!_drive_signal.begin())
  {
    return false;
  }
  if (!_steering_signal.begin())
  {
    return false;
  }
  return true;
}


long RemoteControl::get_drive_position() const
{
  Serial.println(_drive_signal.channel_high_time());
  // 1. Use constrain to limit the PPM signal time to be within the designated input range: [PPM_MIN_TIME, PPM_MAX_TIME]
  // 2. Use map to map from the input time range to the output position range.
  return map(constrain(_drive_signal.channel_high_time(), PPM_MIN_TIME, PPM_MAX_TIME), PPM_MIN_TIME, PPM_MAX_TIME, RC_POSITION_MIN, RC_POSITION_MAX);
}

long RemoteControl::get_steering_position() const
{
  Serial.println(_steering_signal.channel_high_time());
  // 1. Use constrain to limit the PPM signal time to be within the designated input range: [PPM_MIN_TIME, PPM_MAX_TIME]
  // 2. Use map to map from the input time range to the output position range.
  return map(constrain(_steering_signal.channel_high_time(), PPM_MIN_TIME, PPM_MAX_TIME), PPM_MIN_TIME, PPM_MAX_TIME, RC_POSITION_MIN, RC_POSITION_MAX);
}
