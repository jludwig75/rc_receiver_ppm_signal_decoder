#include "NxtVehicle.h"

#include <BricktronicsMotor.h>


static long map_drive_signal(long signal_value, long signal_min, long signal_max, int dead_zone_width, long power_min, long power_max)
{
  if (signal_value < signal_min)
  {
    signal_value = signal_min;
  }
  if (signal_value > signal_max)
  {
    signal_value = signal_max;
  }
  int value = map(signal_value, signal_min, signal_max, power_min, power_max);
  if (value < dead_zone_width && value >= -dead_zone_width)
  {
    value = 0;
  }

  return value;
}

NxtVehicle::NxtVehicle(BricktronicsMotor *steering_and_ss_left_motor,
            BricktronicsMotor *drive_and_ss_right_motor,
            int steering_mode_pin,
            int center_steering_pin,
            int steering_seinsitivity_pin) :
  _steering_and_ss_left_motor(steering_and_ss_left_motor),
  _drive_and_ss_right_motor(drive_and_ss_right_motor),
  _steering_mode_pin(steering_mode_pin),
  _center_steering_pin(center_steering_pin),
  _steering_seinsitivity_pin(steering_seinsitivity_pin),
  _last_power_value(0)
{
}

void NxtVehicle::begin()
{
  _steering_and_ss_left_motor->begin();
  _drive_and_ss_right_motor->begin();
  pinMode(_steering_mode_pin, INPUT);        // digital
  pinMode(_center_steering_pin, INPUT);      // digital
  pinMode(_steering_seinsitivity_pin, INPUT);// analog

  /// @todo Set both motors to zero for skid steer.
  _steering_and_ss_left_motor->goToPositionWaitForDelay(0, 1000);
}

// Value between -255 and 255
void NxtVehicle::set_steering_position(int position)
{
  long steering_position = map_drive_signal(position, -255, 255, 10, -270, 270);
  
  if (!_steering_and_ss_left_motor->settledAtPosition(steering_position))//steering_position != currentPosition)
  {
    _steering_and_ss_left_motor->goToPositionWaitForDelay(steering_position, 100);
  }
  else
  {
    _steering_and_ss_left_motor->hold();
  }
}

// Value between -255 and 255
void NxtVehicle::set_drive_speed(int position)
{
  long drive_power = map_drive_signal(position, -255, 255, 10, -255, 255);
  
  if (drive_power != _last_power_value)
  {
    _drive_and_ss_right_motor->setFixedDrive(drive_power);
    _last_power_value = drive_power;
  }
}
