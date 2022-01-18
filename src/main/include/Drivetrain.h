#ifndef DRIVETRAIN
#define DRIVETRAIN

#include "MotorGroup.h"
#include <iostream>
#include <initializer_list>

class Drivetrain {// Abstract class defining basic control modes for the drivetrain subclasses
  public:
    virtual void Set(){} //Set movement for the drivetrain
    virtual void DiffSet(){}// Control as a differential drive
    static double PercentRange(double in);// Constrains the input to a range of -1 to 1 to prevent errors in motor speed
};

class TankDrive: public Drivetrain {// Derives Drivetrain to implement a tank drive style drivetrain
  public:
    MotorGroup left;
    MotorGroup right;
    TankDrive(std::initializer_list<int> leftMotors, std::initializer_list<int> rightMotors);// Initializes the right and left motor groups with ids given by the constructor
    void Set(double forward, double rotation);// Sets the speed of the motor groups based off of forward and rotational values
    void DiffSet(double leftSpeed, double rightSpeed); // Sets the left and right group motor speeds to the values passed
};

#endif // Drivetrain include guard