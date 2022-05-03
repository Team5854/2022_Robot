// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#ifndef CONSTANTS
#define CONSTANTS


const bool pidEnabled = true;
const bool sensorsDefaulted = false;

// Acceleration mods
const double accelMod = .65; //Temp tuning enabled .7
const double accelRamp = 8; //Temp tuning enabled 8
const double turnMod = .3; //Temp tuning enabled .3
const double turnRamp = 20; //Temp tuning enabled 20
const double boost = 2; // 2
const double k_accelDis = 60000;
const double k_Vlow = 28;
const double k_Vhigh = 40;

//Gamepad bindings
enum gamePadConfig {
  port = 0,
  accelerationAxis = 1,
  steeringAxis = 2,
  leftDriveAxis = 1,
  rightDriveAxis = 3,
  boostButton = 8,
  brakeButton = 12,
  intakeButton = 6,
  shootButton = 7,
  defaultSensorButton = 5
};

//CAN Ids and solenoid ports
enum canIds {
  climberLeadId = 1,
  climberFollowId = 2,
  climberRotateId = 3,
  stage1TalonId = 5,
  stage2TalonId = 4,
  stage3LeadSparkId = 6,
  stage3FollowSparkId = 7,
  leftFalconLeadId = 13,
  leftFalconFollowId = 12,
  rightFalconLeadId = 11,
  rightFalconFollowId = 10,
  compressorId = 8,
  solenoidPort = 0
};

//Climber things
enum climbBinds{
  climbAxis = 1,
  rotateAxis = 2,
  startClimbButton = 13,//13,
  climbFinishedButton = 14//14
};

const double climbSpeed = .85; //Temp tuning enabled
const double rotateSpeed = .375; //Temp tuning enabled
const double holdSpeed = .1;
const double climbDriveSpeed = .13;
const double climbRotateSpeed = .1125;


//Shooter parameters
const double intakeBeltSpeed = .9;
const double shootBeltSpeed = .65;
const double k_shootSpeed = 1000;
const double k_shootSpeedHigh = 4020;
const double k_shootNoPid = .65;
const int intakeTimeout = 1500;
const int k_shootStartTime = 900;
const int k_shotDelay = 1000;
const int shootTimeout = 1200;
const int autoShootTime = 750;
const int autoIntakeTimeout = 3000;

const double shooter_kF = .00019;
const double shooter_kP = .00014;
const double shooter_kI = 0.0000001;
const double shooter_kD = .00041;

//Auto parameters
const int initialMovement = 2000;

#endif