#include <BricktronicsMotor.h>
#include "NxtVehicle.h"
#include "RemoteControl.h"
#include "RCVehicle.h"

const byte steering_channel_interrupt_pin = 3;
const byte drive_channel_interrupt_pin = 2;


byte motor1_enPin = 4;
byte motor1_dirPin = 5;
byte motor1_pwmPin = 6;
byte motor1_encoderPin1 = 7;
byte motor1_encoderPin2 = 8;

byte motor2_enPin = 9;
byte motor2_dirPin = 10;
byte motor2_pwmPin = 11;
byte motor2_encoderPin1 = 12;
byte motor2_encoderPin2 = 13;

byte steering_mode_pin = A2;
byte center_steering_pin = A1;
byte steering_seinsitivity_pin = A0;

BricktronicsMotor motor1(motor1_enPin, motor1_dirPin, motor1_pwmPin, motor1_encoderPin1, motor1_encoderPin2);
BricktronicsMotor motor2(motor2_enPin, motor2_dirPin, motor2_pwmPin, motor2_encoderPin1, motor2_encoderPin2);

NxtVehicle vehicle(&motor2, &motor1, steering_mode_pin, center_steering_pin, steering_seinsitivity_pin);

RemoteControl remote_control(drive_channel_interrupt_pin, steering_channel_interrupt_pin);

RCVehicle rc_vehicle(&vehicle, &remote_control);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting NXT ESC...\n");

  if (rc_vehicle.begin())
  {
    Serial.println("NXT ESC ready.\n");
  }
  else
  {
    Serial.println("Failed to start NXT ESC.\n");
  }

}

long last_power_value = 0;

void loop() {
  rc_vehicle.on_loop();
}
