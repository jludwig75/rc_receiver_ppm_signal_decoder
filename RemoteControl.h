#pragma once

#include "PpmInputSignal.h"

#define RC_POSITION_MIN  -255
#define RC_POSITION_MAX  255

class RemoteControl
{
  public:
    RemoteControl(byte drive_signal_pin, byte steering_signal_pin);
    bool begin();
    long get_drive_position() const;
    long get_steering_position() const;
   private:
    PpmInputSignal _drive_signal;
    PpmInputSignal _steering_signal;
};
