// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

// Acceleration mods
const double accelMod = .35;
const double turnMod = .3;
const double boost = 1.6;

//Gamepad bindings
enum gamePadConfig {
  port = 0,
  accelerationAxis = 1,
  steeringAxis = 0,
  leftDriveAxis = 1,
  rightDriveAxis = 3,
  boostButton = 6,
  intakeButton = 2,
  shootButton = 1
};

//CAN Ids and solenoid ports
enum canIds {
  climberLeadId = 1,
  climberFollowId = 2,
  climberRotateId = 3,
  stage1TalonId = 5,
  stage2TalonId = 4,
  stage3SparkId = 6,
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

const double climbSpeed = .2;
const double rotateSpeed = .5;
const double holdSpeed = .1;
const double climbDriveSpeed = .05;
const double climbRotateSpeed = .05;



//Shooter parameters
const double intakeBeltSpeed = .5;
const double shootBeltSpeed = .4;
const double shootSpeed = 1;
const int intakeTimeout = 1800;
const int shootStartTime = 2000;
const int shootTimeout = 1200;