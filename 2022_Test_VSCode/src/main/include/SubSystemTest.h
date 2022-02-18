#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>

class SolenoidShit : public frc2::SubsystemBase{
  public:
    SolenoidShit();
  //Methods
  void ExtendAll();
  void RetractAll();

  private:
    frc::DoubleSolenoid DoubleSolenoid{6,frc::PneumaticsModuleType::CTREPCM,2,3};

};