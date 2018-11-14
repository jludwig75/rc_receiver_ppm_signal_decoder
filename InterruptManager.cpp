#include "InterruptManager.h"


typedef void (InterruptClass::*InterruptMethod)();

struct InterruptInfo
{
    InterruptClass *class_instance;
    InterruptMethod method;
};

static InterruptInfo _instances[MAX_NUMBER_OF_INTERRUPTS];

static void interrupt_0_isr()
{
    InterruptMethod method = _instances[0].method;
    ((_instances[0].class_instance)->*method)();
}

static void interrupt_1_isr()
{
    InterruptMethod method = _instances[1].method;
    ((_instances[1].class_instance)->*method)();
}

static void interrupt_2_isr()
{
    InterruptMethod method = _instances[2].method;
    ((_instances[2].class_instance)->*method)();
}

static void interrupt_3_isr()
{
    InterruptMethod method = _instances[3].method;
    ((_instances[3].class_instance)->*method)();
}

static void interrupt_4_isr()
{
    InterruptMethod method = _instances[4].method;
    ((_instances[4].class_instance)->*method)();
}

static void interrupt_5_isr()
{
    InterruptMethod method = _instances[5].method;
    ((_instances[5].class_instance)->*method)();
}

InterruptManagerClass::InterruptManagerClass()
{
    for (unsigned i = 0; i < MAX_NUMBER_OF_INTERRUPTS; i++)
    {
        _instances[i].class_instance = NULL;
        _instances[i].method = NULL;
    }

    _isr_table[0] = interrupt_0_isr;
    _isr_table[1] = interrupt_1_isr;
    _isr_table[2] = interrupt_2_isr;
    _isr_table[3] = interrupt_3_isr;
    _isr_table[4] = interrupt_4_isr;
    _isr_table[5] = interrupt_5_isr;
}

bool InterruptManagerClass::attachInterrupt(byte interruptPin, InterruptClass *class_instance, void (InterruptClass::*instance)(), int mode)
{
    for (unsigned i = 0; i < MAX_NUMBER_OF_INTERRUPTS; i++)
    {
        if (_instances[i].method == NULL)
        {
            _instances[i].class_instance = class_instance;
            _instances[i].method = instance;
            ::attachInterrupt(digitalPinToInterrupt(interruptPin), _isr_table[i], mode);
            return true;
        }
    }

    return false;
}

InterruptManagerClass InterruptManager;
