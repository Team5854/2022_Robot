#include "subsystems/Climber.h"
#include "Constants.h"

Climber::Climber (int leadClimb, int followClimb, int rotate, Arduino& ledController, std::initializer_list<bool> motorConfigs):
    m_leadClimb{leadClimb}, m_followClimb{followClimb}, m_rotate{rotate}, m_ledController{ledController}
{
    m_leadClimb.SetInverted(motorConfigs.begin()[0]);
    m_followClimb.SetInverted(motorConfigs.begin()[1]);
    m_rotate.SetInverted(motorConfigs.begin()[2]);
    m_followClimb.Follow(m_leadClimb);
    m_leadClimb.SetNeutralMode(NeutralMode::Brake);
    m_followClimb.SetNeutralMode(NeutralMode::Brake);
    m_rotate.SetNeutralMode(NeutralMode::Brake);
}

void Climber::rotate(double rate){
    m_rotate.Set(ControlMode::PercentOutput, rate);
}

void Climber::climb(double rate){
    m_leadClimb.Set(ControlMode::PercentOutput, rate);
}

int Climber::setLeds(bool state){
    if(state) return m_ledController.sendState('l');
    else return m_ledController.sendState('c');
}
int Climber::getClimbLimit(){
    if(m_leadClimb.IsFwdLimitSwitchClosed()){
        return 1;
    }
    else if(m_leadClimb.IsRevLimitSwitchClosed()){
        return -1;
    }
    else return 0;
}
int Climber::getRotateLimit(){
    if(m_rotate.IsFwdLimitSwitchClosed()){
        return 1;
    }
    else if(m_rotate.IsRevLimitSwitchClosed()){
        return -1;
    }
    else return 0;
}