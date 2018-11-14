#pragma once


class BricktronicsMotor;

class NxtVehicle
{
  public:
    NxtVehicle(BricktronicsMotor *steering_and_ss_left_motor,
                BricktronicsMotor *drive_and_ss_right_motor,
                int steering_mode_pin,
                int center_steering_pin,
                int steering_seinsitivity_pin);

    void begin();

    // Value between -255 and 255
    void set_steering_position(int position);
    // Value between -255 and 255
    void set_drive_speed(int position);

  private:
    BricktronicsMotor *_steering_and_ss_left_motor;
    BricktronicsMotor *_drive_and_ss_right_motor;
    int _steering_mode_pin;
    int _center_steering_pin;
    int _steering_seinsitivity_pin;

    long _last_power_value;
};
