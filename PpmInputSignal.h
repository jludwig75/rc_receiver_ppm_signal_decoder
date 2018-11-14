#pragma once
#include "InterruptManager.h"


class PpmInputSignal : public InterruptClass
{
  public:
    PpmInputSignal(byte signal_pin);
    bool begin();
    virtual void on_change_interrupt();
    unsigned long channel_high_time() const;
  private:
    byte _signal_pin;
    volatile unsigned long _last_channel_rise_time;
    volatile unsigned long _channel_high_time;
};
