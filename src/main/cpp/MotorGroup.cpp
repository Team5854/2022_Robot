#include "ctre/Phoenix.h"
#include <vector>
#include <initializer_list>

class MotorGroup{
  private:
    std::vector<TalonSRX*> talons;
  public:
    MotorGroup(std::initializer_list<int> talonIds){
      for (int id : talonIds) talons.push_back(new TalonSRX(id));
      for (unsigned int i = 1; i < talons.size(); i++){
        talons[i]->Follow(*talons[0]);
      }
    }
};
