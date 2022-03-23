// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#ifndef CONSTANTS
#define CONSTANTS


const bool pidEnabled = false;

// Acceleration mods
const double accelMod = .65; //Temp tuning enabled .7
const double accelRamp = 8; //Temp tuning enabled 8
const double turnMod = .3; //Temp tuning enabled .3
const double turnRamp = 20; //Temp tuning enabled 20
const double boost = 2; // 2

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
  startClimbButton = 13,
  climbFinishedButton = 14
};

const double climbSpeed = .75; //Temp tuning enabled
const double rotateSpeed = .375; //Temp tuning enabled
const double holdSpeed = .1;
const double climbDriveSpeed = .1;
const double climbRotateSpeed = .075;


//Shooter parameters
const double intakeBeltSpeed = .9;
const double shootBeltSpeed = .7;
const double shootSpeed = 0.42; //Temp tuning enabled
const int intakeTimeout = 1500; //Used to be 1500
const int shootStartTime = 2000;
const int shootTimeout = 1200;  //Used to be 1200

//Auto parameters
const int initialMovement = 2000;

#endif