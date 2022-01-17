#include "MotorGroup.cpp"

class Drivetrain {// Abstract class defining basic control modes for the drivetrain subclasses
  public:
    virtual void Set(){} //Set movement for the drivetrain
    static double PercentRange(double in){// Constrains the input to a range of -1 to 1 to prevent errors in motor speed
      if(in > 1) return 1;
      else if(in < -1) return -1;
      else return in;
    }
};

class TankDrive: public Drivetrain {// Derives Drivetrain to implement a tank drive style drivetrain
  public:
    MotorGroup left;
    MotorGroup right;
    TankDrive(std::initializer_list<int> leftMotors, std::initializer_list<int> rightMotors): left(leftMotors), right(rightMotors) {}// Initializes the right and left motor groups with ids given by the constructor
    void Set(double forward, double rotation){// Sets the speed of the motor groups based off of forward and rotational values
      /* The values are set using a formula of substracting the rotational speed from -1 to 1 for left to right from the forward speed motors on the turn side. The motors on the non turnside
       (e.g. when turning left this would be the right side motors) have the rotational speed added to their forward speed.
       The if else statement checks for if the robot is moving forward or backwards and inverts the rotation to create car like behavior when turning while moving backwards.*/
      if((forward > 1 || forward < -1) || (rotation > 1 || rotation < -1)){
        std::cout<<"Invalid Tankdrive Set() parameters"<<endl;
        throw 1;
      }
      else{
        if(forward >= 0){
          left.Set(Drivetrain::PercentRange(forward+rotation));
          right.Set(Drivetrain::PercentRange(forward-rotation));
        }
        else{
          left.Set(Drivetrain::PercentRange(forward-rotation));
          right.Set(Drivetrain::PercentRange(forward+rotation));
        }
      }
    }
};
