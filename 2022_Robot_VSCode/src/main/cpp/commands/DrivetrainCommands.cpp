// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#define _USE_MATH_DEFINES
#include "commands/DrivetrainCommands.h"
#include <iostream>
#include <cmath>

CommandUserDrive::CommandUserDrive(Drivetrain* drivetrain, frc::GenericHID& controller)
    : m_drivetrain{drivetrain}, m_controller{controller}{
      AddRequirements(drivetrain);
    }

void CommandUserDrive::Execute(){
  accelSpeed += (Drivetrain::NonLinear(m_controller.GetRawAxis(accelerationAxis)) - accelSpeed)*accelRamp/100;
  turnSpeed += (Drivetrain::NonLinear(m_controller.GetRawAxis(steeringAxis)) - turnSpeed)*turnRamp/100;

  if(m_controller.GetRawButton(brakeButton)){
    accelSpeed = 0;
    turnSpeed = 0;
    m_drivetrain->brakeSet(true);
  }
  else{
    m_drivetrain->brakeSet(false);
  }

  if(m_controller.GetRawButton(boostButton)){
    m_drivetrain->Set(Drivetrain::PercentRange(-1*boost*accelMod*accelSpeed), Drivetrain::PercentRange(-1*turnMod*turnSpeed));
  }
  else{
    m_drivetrain->Set(Drivetrain::PercentRange(-1*accelMod*accelSpeed), Drivetrain::PercentRange(-1*turnMod*turnSpeed));
  }
}

void CommandUserDrive::End(bool interrupted){
  m_drivetrain->Set(0,0);
}

autoDrive::autoDrive(Drivetrain* drivetrain, double distance)
    : m_drivetrain{drivetrain}, m_distance{distance}{
      AddRequirements(drivetrain);
      if(distance > 0) m_distance -= 2;
      else m_distance +=2;
    }

void autoDrive::Initialize(){
  leftStart = m_drivetrain->GetLeftEncoders();
  rightStart = m_drivetrain->GetRightEncoders();
  leftEnd = leftStart - (m_distance * 60.0 / 11.0 * 30.0 / 18.0 * 2048.0 / 6.0 / M_PI);
  rightEnd = rightStart + (m_distance * 60.0 / 11.0 * 30.0 / 18.0 * 2048.0 / 6.0 / M_PI);
}

void autoDrive::Execute(){
  double leftVelocity = 0;
  double rightVelocity = 0;
  if(m_distance > 0){
    leftVelocity = getVelocity(abs(leftEnd-leftStart),leftStart - m_drivetrain->GetLeftEncoders());
    rightVelocity = getVelocity(abs(rightEnd-rightStart), rightStart - m_drivetrain->GetRightEncoders());

    if(abs(rightEnd - m_drivetrain->GetRightEncoders()) < 1000) rightVelocity = 0;
    if(abs(leftEnd - m_drivetrain->GetLeftEncoders()) < 1000) leftVelocity = 0;
  }
  else{
    leftVelocity = -1*getVelocity(abs(leftEnd-leftStart), leftStart - m_drivetrain->GetLeftEncoders());
    rightVelocity = -1*getVelocity(abs(rightEnd-rightStart), rightStart - m_drivetrain->GetRightEncoders());

    if(abs(rightEnd - m_drivetrain->GetRightEncoders()) < 1000) rightVelocity = 0;
    if(abs(leftEnd - m_drivetrain->GetLeftEncoders()) < 1000) leftVelocity = 0;
  }
  m_drivetrain->velocitySet(leftVelocity, rightVelocity);
}

void autoDrive::End(bool interrupted){
  m_drivetrain->velocitySet(0,0);
}

bool autoDrive::IsFinished(){
  if(abs(rightEnd - m_drivetrain->GetRightEncoders()) < 1000 || abs(leftEnd - m_drivetrain->GetLeftEncoders()) < 1000) return true;
  else return false;
}


double autoDrive::getVelocity(double distance, double point){
  double lowTicVel = m_drivetrain->Vlow.GetDouble(k_Vlow)*((60.0/11.0)*(30.0/18.0)*(2048.0/10.0)*(1.0/(6.0*M_PI)));
  double highTicVel = m_drivetrain->Vhigh.GetDouble(k_Vhigh)*((60.0/11.0)*(30.0/18.0)*(2048.0/10.0)*(1.0/(6.0*M_PI)));
  double accelRate = (highTicVel - lowTicVel)/m_drivetrain->accelDis.GetDouble(k_accelDis);
  
  if(point > (distance - m_drivetrain->accelDis.GetDouble(k_accelDis)) && point > (distance/2)){
    return -1*accelRate*(point - (distance - m_drivetrain->accelDis.GetDouble(k_accelDis))) + highTicVel;
  }
  else if(point < m_drivetrain->accelDis.GetDouble(k_accelDis) && point > 0){
    return accelRate*point + lowTicVel;
  }
  else if(point < 0) return lowTicVel;
  else return highTicVel;
}

autoTurn::autoTurn(Drivetrain* drivetrain, double angle)
    : m_drivetrain{drivetrain}, m_angle{angle*(M_PI/180)}{
      AddRequirements(drivetrain);
    }

void autoTurn::Initialize(){
  double scale = abs(550*m_angle);
  leftStart = m_drivetrain->GetLeftEncoders();
  rightStart = m_drivetrain->GetRightEncoders();
  leftEnd = leftStart + (m_angle * 13.225 * 60.0 / 11.0 * 30.0 / 18.0 * 2048.0 / 6.0 / M_PI) + scale;
  rightEnd = rightStart + (m_angle * 13.225 * 60.0 / 11.0 * 30.0 / 18.0 * 2048.0 / 6.0 / M_PI) + scale;
}

void autoTurn::Execute(){
  double leftVelocity = 0;
  double rightVelocity = 0;
  if(m_angle > 0){
    leftVelocity = -1*getVelocity(abs(leftEnd-leftStart), m_drivetrain->GetLeftEncoders() - leftStart);
    rightVelocity =  getVelocity(abs(rightEnd-rightStart), m_drivetrain->GetRightEncoders() - rightStart);
  }
  else{
    leftVelocity = getVelocity(abs(leftEnd-leftStart), leftStart - m_drivetrain->GetLeftEncoders());
    rightVelocity = -1*getVelocity(abs(rightEnd-rightStart), rightStart - m_drivetrain->GetRightEncoders());
  }
  if(abs(rightEnd - m_drivetrain->GetRightEncoders()) < 1000) rightVelocity = 0;
  if(abs(leftEnd - m_drivetrain->GetLeftEncoders()) < 1000) leftVelocity = 0;
  
  m_drivetrain->velocitySet(leftVelocity, rightVelocity);
}

void autoTurn::End(bool interrupted){
  m_drivetrain->velocitySet(0,0);
}

bool autoTurn::IsFinished(){
  if(abs(rightEnd - m_drivetrain->GetRightEncoders()) < 1000 || abs(leftEnd - m_drivetrain->GetLeftEncoders()) < 1000) return true;
  else return false;
}


double autoTurn::getVelocity(double distance, double point){
  double lowTicVel = m_drivetrain->Vlow.GetDouble(k_Vlow)*((60.0/11.0)*(30.0/18.0)*(2048.0/10.0)*(1.0/(6.0*M_PI)));
  double highTicVel = m_drivetrain->Vhigh.GetDouble(k_Vhigh)*((60.0/11.0)*(30.0/18.0)*(2048.0/10.0)*(1.0/(6.0*M_PI)));
  double accelRate = (highTicVel - lowTicVel)/m_drivetrain->accelDis.GetDouble(k_accelDis);
  
  if(point > (distance - m_drivetrain->accelDis.GetDouble(k_accelDis)) && point > (distance/2)){
    return -1*accelRate*(point - (distance - m_drivetrain->accelDis.GetDouble(k_accelDis))) + highTicVel;
  }
  else if(point < m_drivetrain->accelDis.GetDouble(k_accelDis) && point > 0){
    return accelRate*point + lowTicVel;
  }
  else if(point < 0) return lowTicVel;
  else return highTicVel;
}