#include "PpmInputSignal.h"

#include <util/atomic.h>


PpmInputSignal::PpmInputSignal(byte signal_pin) : _signal_pin(signal_pin), _last_channel_rise_time(micros()), _channel_high_time(1500)
{
  
}

bool PpmInputSignal::begin()
{
  pinMode(_signal_pin, INPUT);
  return InterruptManager.attachInterrupt(_signal_pin, this, &InterruptClass::on_change_interrupt, CHANGE);
}

void PpmInputSignal::on_change_interrupt()
{
  if (digitalRead(_signal_pin) == HIGH)
  {
    _last_channel_rise_time = micros();
  }
  else
  {
    _channel_high_time = micros() - _last_channel_rise_time;
  }
}

unsigned long PpmInputSignal::channel_high_time() const
{
  unsigned long ret;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    ret = _channel_high_time;
  }
  return ret;
}
