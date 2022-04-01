#include "subsystems/ShooterIntake.h"
#include "Constants.h"

ShooterIntake::ShooterIntake(int shooterLead,int shooterFollow, int stage2, int stage1, frc::Compressor& compressor, int solenoid,Arduino& ledController, int breakbeam1, int breakbeam2, std::initializer_list<bool> motorConfigs):
    m_shooterLead{shooterLead,rev::CANSparkMaxLowLevel::MotorType::kBrushless},
    m_shooterFollow{shooterFollow,rev::CANSparkMax::MotorType::kBrushless},
    m_stage2{stage2}, m_stage1{stage1}, m_compressor{compressor},
    m_solenoid{compressorId, frc::PneumaticsModuleType::CTREPCM, solenoid},
    m_ledController{ledController}, m_breakBeam1{breakbeam1}, m_breakBeam2{breakbeam2},
    m_PIDController{m_shooterLead.GetPIDController()}, m_Encoder{m_shooterLead.GetEncoder()}
{
    m_shooterLead.RestoreFactoryDefaults();
    m_shooterFollow.RestoreFactoryDefaults();
    m_shooterFollow.Follow(m_shooterLead,motorConfigs.begin()[1]);
    m_stage2.SetInverted(motorConfigs.begin()[2]);
    m_stage2.SetNeutralMode(NeutralMode::Brake);
    m_stage1.SetInverted(motorConfigs.begin()[3]);
    m_stage1.SetNeutralMode(NeutralMode::Brake);
    m_compressor.EnableDigital();
    frc::SmartDashboard::PutNumber("Shooter Speed", m_Encoder.GetVelocity());
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
    m_shooterLead.Set(speed);}

int ShooterIntake::setLeds(int state){
    if(state == 0) return m_ledController.sendState('i');
    else if(state == 1) return m_ledController.sendState('I');
    else if(state == 2) return m_ledController.sendState('n');
    else return m_ledController.sendState('s');
}

bool ShooterIntake::getBreakBeam1(){
    return !m_breakBeam1.Get();
}

bool ShooterIntake::getBreakBeam2(){
    return !m_breakBeam2.Get();
}

void ShooterIntake::setPid(double kF, double kP, double kI, double kD){
    m_PIDController.SetP(kP);
    m_PIDController.SetI(kI);
    m_PIDController.SetD(kD);
    m_PIDController.SetFF(kF);
    m_PIDController.SetOutputRange(0, 1);
}

void ShooterIntake::setMotorPoint(double setpoint){
    m_PIDController.SetReference(setpoint, rev::ControlType::kVelocity);
}

void ShooterIntake::Periodic(){
    frc::SmartDashboard::PutNumber("Shooter Speed", m_Encoder.GetVelocity());
}