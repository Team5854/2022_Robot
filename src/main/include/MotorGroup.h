#include "ctre/Phoenix.h"
#include <vector>
#include <initializer_list>
#include <iostream>

class MotorGroup{// Group multiple talons for basic drive functionality
  public:
    std::vector<TalonSRX*> talons;// Vector of pointers to talon objects
    MotorGroup(std::initializer_list<int> talonIds);
    void Set(double speed);// Set speed of the talons in basic PercentOutput control mode
};