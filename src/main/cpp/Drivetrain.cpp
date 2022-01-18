#include "Drivetrain.h"

double Drivetrain::PercentRange(double in){// Constrains the input to a range of -1 to 1 to prevent errors in motor speed
  if(in > 1) return 1;
  else if(in < -1) return -1;
  else return in;
}

TankDrive:: TankDrive(std::initializer_list<int> leftMotors, std::initializer_list<int> rightMotors): left(leftMotors), right(rightMotors) {}// Initializes the right and left motor groups with ids given by the constructor

void TankDrive::Set(double forward, double rotation){// Sets the speed of the motor groups based off of forward and rotational values
  /* The values are set using a formula of substracting the rotational speed from -1 to 1 for left to right from the forward speed motors on the turn side. The motors on the non turnside
  (e.g. when turning left this would be the right side motors) have the rotational speed added to their forward speed.
  The if else statement checks for if the robot is moving forward or backwards and inverts the rotation to create car like behavioxr when turning while moving backwards.*/
  if((forward > 1 || forward < -1) || (rotation > 1 || rotation < -1)){
    std::cout<<"Invalid Tankdrive Set() parameters"<<std::endl;
    throw 1;
  }
  else{
    if(forward >= 0){
      left.Set(Drivetrain::PercentRange(forward+rotation)); //Left side + rotation (slows when negative meaning left turn, and speeds up for positive)
      right.Set(Drivetrain::PercentRange(forward-rotation)); //Right side - rotation (reverse of above)
    }
    else{ // The same as above but flipped so rotation is inverted
      left.Set(Drivetrain::PercentRange(forward-rotation));
      right.Set(Drivetrain::PercentRange(forward+rotation));
    }
  }
}

void TankDrive::DiffSet(double leftSpeed, double rightSpeed){ // Sets the left and right group motor speeds to the values passed
  if((leftSpeed > 1 || leftSpeed < -1) || (rightSpeed > 1 || rightSpeed < -1)){
    std::cout<<"Invalid Tankdrive DiffSet() parameters"<<std::endl;
    throw 1;
  }
  else{
    left.Set(leftSpeed);
    right.Set(rightSpeed);
  }
}