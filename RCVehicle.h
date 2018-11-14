#pragma once


class NxtVehicle;
class RemoteControl;

class RCVehicle
{
  public:
    RCVehicle(NxtVehicle *vehicle, RemoteControl *remote);
    bool begin();
    void on_loop();
  private:
    NxtVehicle *_vehicle;
    RemoteControl *_remote;
};
