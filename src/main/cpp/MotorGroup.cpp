#include "MotorGroup.h"

MotorGroup::MotorGroup(std::initializer_list<int> talonIds){ 
  for (int id : talonIds) talons.push_back(new TalonSRX(id));// Add a new talon object to the vector for each id given to the constructor
  for (unsigned int i = 1; i < talons.size(); i++){// Set each talon after the first listed to follow the first talon
    talons[i]->Follow(*talons[0]);
  }
}

void MotorGroup::Set(double speed){// Set speed of the talons in basic PercentOutput control mode
  if(speed < -1 || speed > 1){
    std::cout<<"Invalid MotorGroup Set() parameter"<<std::endl;
    throw 1;
  }
  else{
    talons[0]->Set(ControlMode::PercentOutput, speed);
  }
}