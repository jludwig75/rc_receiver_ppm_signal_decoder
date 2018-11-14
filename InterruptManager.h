#pragma once

#include <Arduino.h>


#define MAX_NUMBER_OF_INTERRUPTS  6


class InterruptClass
{
  public:
    virtual void on_change_interrupt() = 0;
};

class InterruptManagerClass
{
  public:
    InterruptManagerClass();
    bool attachInterrupt(byte interruptPin, InterruptClass *class_instance, void (InterruptClass::*instance)(), int mode);
    void(*_isr_table[MAX_NUMBER_OF_INTERRUPTS])();
};

extern InterruptManagerClass InterruptManager;
