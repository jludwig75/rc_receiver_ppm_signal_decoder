#include "RCVehicle.h"

#include "NxtVehicle.h"
#include "RemoteControl.h"

#include <Arduino.h>


RCVehicle::RCVehicle(NxtVehicle *vehicle, RemoteControl *remote) :
  _vehicle(vehicle),
  _remote(remote)
{
}

bool RCVehicle::begin()
{
  _vehicle->begin();
  return _remote->begin();
}


void RCVehicle::on_loop()
{
  /// @todo Somehow apply dead zone here
  int steering_position = _remote->get_steering_position();
  int drive_speed = _remote->get_drive_position();

  Serial.print("Input: [");
  Serial.print(steering_position);
  Serial.print(", ");
  Serial.print(drive_speed);
  Serial.println("]");
  
  _vehicle->set_steering_position(steering_position);
  _vehicle->set_drive_speed(drive_speed);
}
