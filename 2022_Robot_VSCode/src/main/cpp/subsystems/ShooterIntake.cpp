#include "subsystems/ShooterIntake.h"
#include "Constants.h"

ShooterIntake::ShooterIntake(int shooter, int stage2, int stage1, frc::Compressor& compressor, int solenoid, int breakbeam1, int breakbeam2, std::initializer_list<bool> motorConfigs):
    m_shooter{shooter,rev::CANSparkMaxLowLevel::MotorType::kBrushless}, m_stage2{stage2}, m_stage1{stage1}, m_compressor{compressor},
    m_solenoid{compressorId, frc::PneumaticsModuleType::CTREPCM, solenoid}, m_breakBeam1{breakbeam1}, m_breakBeam2{breakbeam2} 
{
    m_shooter.SetInverted(motorConfigs.begin()[0]);
    m_stage2.SetInverted(motorConfigs.begin()[1]);
    m_stage2.SetNeutralMode(NeutralMode::Brake);
    m_stage1.SetInverted(motorConfigs.begin()[2]);
    m_stage1.SetNeutralMode(NeutralMode::Brake);
    m_compressor.EnableDigital();
}

void ShooterIntake::setIntake(bool upDown){
    m_solenoid.Set(upDown);
}

void ShooterIntake::stage1Run(double speed){
    m_stage1.Set(ControlMode::PercentOutput, speed);
}

void ShooterIntake::stage2Run(double speed){
    m_stage2.Set(ControlMode::PercentOutput, speed);
}

void ShooterIntake::shootRun(double speed){
    m_shooter.Set(speed);
}

bool ShooterIntake::getBreakBeam1(){
    return !m_breakBeam1.Get();
}

bool ShooterIntake::getBreakBeam2(){
    return !m_breakBeam2.Get();
}