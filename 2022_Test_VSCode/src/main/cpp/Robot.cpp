#include <iostream>

#include "Robot.h"
#include "Drivetrain.h"


void Robot::RobotInit() {
  std::cout << "Starting" << std::endl;
  //Compressor.Disable();
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {


}

void Robot::AutonomousPeriodic() {
  //DoubleSolenoid.Set(frc::DoubleSolenoid::kReverse);
  //std::cout << DoubleSolenoid.Get() << std::endl;
}

void Robot::TeleopInit() {

}

void Robot::TeleopPeriodic() {
  //if(driverPad1.GetRawButton(boostButton)) driveTrain.Set(Drivetrain::PercentRange(boost*accelMod*driverPad1.GetRawAxis(accelerationAxis)),Drivetrain::PercentRange(turnMod*driverPad1.GetRawAxis(steeringAxis)));
  //else driveTrain.Set(accelMod*driverPad1.GetRawAxis(accelerationAxis),turnMod*driverPad1.GetRawAxis(steeringAxis));
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {
  time = clock()+(.5*CLOCKS_PER_SEC);
  //shooterMotor.Set(ControlMode::PercentOutput, .1);
  //Compressor.Disable();
  //std::cout << arduino.initComms() << std::endl;
}

void Robot::TestPeriodic() {
  int pos;
  if(driverPad1.GetRawButton(shootButton)) shooterMotor1.Set(.5);
  else shooterMotor1.Set(0);
  if(driverPad1.GetRawButton(piston)) {
    //DoubleSolenoid.Set(frc::DoubleSolenoid::kForward);
  }
  //else DoubleSolenoid.Set(frc::DoubleSolenoid::kReverse);
  if(time <= clock()){
    //pos = shooterMotor.GetSensorCollection().GetIntegratedSensorVelocity()/2048;
    std::cout << pos << std::endl;
    time = clock()+(.5*CLOCKS_PER_SEC);
  }
  //shooterMotor.Set(ControlMode::Velocity, 2000);
  //shooterMotor2.Set(ControlMode::PercentOutput, -1*driverPad1.GetRawAxis(1));
  shooterMotor3.Set(ControlMode::PercentOutput, -1*driverPad1.GetRawAxis(1));
  //if(driverPad1.GetRawButtonPressed(sendT)) arduino.serialPortObj->Write("t");
  //if(driverPad1.GetRawButtonPressed(sendF)) arduino.serialPortObj->Write("f");
  //if(driverPad1.GetRawButtonPressed(12)) arduino.initComms();
}


#ifndef RUNNING_FRC_TESTS

int main() {
  return frc::StartRobot<Robot>();
}
#endif
