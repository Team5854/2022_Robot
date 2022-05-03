#include "subsystems/Drivetrain.h"
#include <frc2/command/CommandScheduler.h>

Drivetrain::Drivetrain(int leftLead, int leftFollow, int rightLead, int rightFollow, std::initializer_list<bool> motorInverts)
  : m_leftLead{leftLead}, m_leftFollow{leftFollow}, m_rightLead{rightLead}, m_rightFollow{rightFollow}
  {
  m_leftLead.SetInverted(motorInverts.begin()[0]);
  m_leftFollow.SetInverted(motorInverts.begin()[1]);
  m_rightLead.SetInverted(motorInverts.begin()[2]);
  m_rightFollow.SetInverted(motorInverts.begin()[3]);
  m_leftFollow.Follow(m_leftLead);
  m_rightFollow.Follow(m_rightLead);
  m_leftLead.SetNeutralMode(NeutralMode::Brake);
  m_leftFollow.SetNeutralMode(NeutralMode::Brake);
  m_rightLead.SetNeutralMode(NeutralMode::Brake);
  m_rightFollow.SetNeutralMode(NeutralMode::Brake);
  frc2::CommandScheduler::GetInstance().RegisterSubsystem(this);
  m_rightLead.Config_kF(0,.05,50);
  m_rightLead.Config_kP(0,.02,50);
  m_rightLead.ConfigClosedloopRamp(.25, 50);
  m_rightLead.ConfigAllowableClosedloopError(0,150,50);
  m_leftLead.Config_kF(0,.05,50);
  m_leftLead.Config_kP(0,.02,50);
  m_leftLead.ConfigClosedloopRamp(.25, 50);
  m_leftLead.ConfigAllowableClosedloopError(0,150,50);
}

void Drivetrain::Set(double forward, double rotation){// Sets the speed of the motor groups based off of forward and rotational values
  /* The values are set using a formula of substracting the rotational speed from -1 to 1 for left to right from the forward speed motors on the turn side. The motors on the non turnside
  (e.g. when turning left this would be the right side motors) have the rotational speed added to their forward speed.
  The if else statement checks for if the robot is moving forward or backwards and inverts the rotation to create car like behavioxr when turning while moving backwards.*/
  if((forward > 1 || forward < -1) || (rotation > 1 || rotation < -1)){
    std::cout<<"Invalid Tankdrive Set() parameters"<<std::endl;
    throw 1;
  }
  else{ 
    m_leftLead.Set(ControlMode::PercentOutput, Drivetrain::PercentRange(forward-rotation)); //Left side + rotation (slows when negative meaning left turn, and speeds up for positive)
    m_rightLead.Set(ControlMode::PercentOutput, Drivetrain::PercentRange(forward+rotation)); //Right side - rotation (reverse of above)
  }
}

void Drivetrain::DiffSet(double leftSpeed, double rightSpeed) {// Sets the left and right group motor speeds to the values passed
  if((leftSpeed > 1 || leftSpeed < -1) || (rightSpeed > 1 || rightSpeed < -1)){
    std::cout<<"Invalid Tankdrive DiffSet() parameters"<<std::endl;
    throw 1;
  }
  else{
    m_leftLead.Set(ControlMode::PercentOutput, leftSpeed);
    m_rightLead.Set(ControlMode::PercentOutput, rightSpeed);
  }
}

double Drivetrain::PercentRange(double in){// Constrains the input to a range of -1 to 1 to prevent errors in motor speed
  if(in > 1) return 1;
  else if(in < -1) return -1;
  else return in;
}

double Drivetrain::NonLinear(double in){
  if(abs(in)<.7){
    return in;
  }
  else return pow(in,3);
}

double Drivetrain::GetLeftEncoders(){
  return m_leftLead.GetSelectedSensorPosition(0);
}

double Drivetrain::GetRightEncoders(){
  return m_rightLead.GetSelectedSensorPosition(0);
}

void Drivetrain::velocitySet(double leftVelocity, double rightVelocity){
  m_leftLead.Set(ControlMode::Velocity, leftVelocity);
  m_rightLead.Set(ControlMode::Velocity, rightVelocity);
}

void Drivetrain::brakeSet(bool on){
  if(on){
    m_leftLead.SetNeutralMode(NeutralMode::Brake);
    m_leftFollow.SetNeutralMode(NeutralMode::Brake);
    m_rightLead.SetNeutralMode(NeutralMode::Brake);
    m_rightFollow.SetNeutralMode(NeutralMode::Brake);
  }
  else{
    m_leftLead.SetNeutralMode(NeutralMode::Coast);
    m_leftFollow.SetNeutralMode(NeutralMode::Coast);
    m_rightLead.SetNeutralMode(NeutralMode::Coast);
    m_rightFollow.SetNeutralMode(NeutralMode::Coast);
  }
}