// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

// Acceleration mods
const double accelMod = .35;
const double turnMod = .5;
const double boost = 1.6;

//Gamepad bindings
enum gamePadConfig {
  port = 0,
  accelerationAxis = 1,
  steeringAxis = 2,
  leftDriveAxis = 1,
  rightDriveAxis = 3,
  boostButton = 3,
  intakeButton = 4,
  shootButton = 2
};

//CAN Ids and solenoid ports
enum canIds {
  stage1TalonId = 5,
  stage2TalonId = 4,
  stage3SparkId = 6,
  leftFalconLeadId = 13,
  leftFalconFollowId = 12,
  rightFalconLeadId = 11,
  rightFalconFollowId = 10,
  compressorId = 8,
  solenoidPort = 1
};



//Shooter parameters
const double intakeBeltSpeed = .3;
const double shootBeltSpeed = .5;
const double shootSpeed = .5;
const int intakeTimeout = 750;
const int shootStartTime = 500;
const int shootTimeout = 500;