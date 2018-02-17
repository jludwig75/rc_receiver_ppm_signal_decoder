
const byte channel_1_interrupt_pin = 2;
const byte channel_2_interrupt_pin = 3;


class PpmInputSignal
{
  public:
    PpmInputSignal(byte signal_pin) : _signal_pin(signal_pin), _last_channel_rise_time(micros()), _channel_high_time(1500)
    {
      
    }
    void on_change_interrupt()
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
    unsigned long channel_high_time() const
    {
      return _channel_high_time;
    }
  private:
    byte _signal_pin;
    volatile unsigned long _last_channel_rise_time;
    volatile unsigned long _channel_high_time;
};

PpmInputSignal channel_1_signal(channel_1_interrupt_pin);
PpmInputSignal channel_2_signal(channel_2_interrupt_pin);

void channel_1_isr() {
  channel_1_signal.on_change_interrupt();
}

void channel_2_isr() {
  channel_2_signal.on_change_interrupt();
}


void setup() {
  Serial.begin(9600);
  
  pinMode(channel_1_interrupt_pin, INPUT);
  pinMode(channel_2_interrupt_pin, INPUT);

  attachInterrupt(digitalPinToInterrupt(channel_1_interrupt_pin), channel_1_isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(channel_2_interrupt_pin), channel_2_isr, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Channel 1:");
  Serial.print(channel_1_signal.channel_high_time());
  Serial.print("Channel 2:");
  Serial.println(channel_2_signal.channel_high_time());
  delay(500);
}
