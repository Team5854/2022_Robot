#include "ctre/Phoenix.h"
#include <vector>
#include <initializer_list>

class MotorGroup{
  public:
    std::vector<TalonSRX*> talons;
    MotorGroup(std::initializer_list<int> talonIds){
      for (int id : talonIds) talons.push_back(new TalonSRX(id));
      for (unsigned int i = 1; i < talons.size(); i++){
        talons[i]->Follow(*talons[0]);
      }
    }
    Set(double speed){
      if(speed <= -1 || speed >= 1){
        throw 1;
      }
      else{
        *talons[0].Set(TalonSRXControlMode.PercentOutput, speed);
      }
};
