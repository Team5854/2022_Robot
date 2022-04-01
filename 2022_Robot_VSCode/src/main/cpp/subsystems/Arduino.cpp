#include "subsystems/Arduino.h"
Arduino::Arduino(int baudrate, frc::SerialPort::Port usbPort): baud(baudrate), port(usbPort){}

int Arduino::initComms(){
  try{
    delete serialPortObj;
    serialPortObj = new frc::SerialPort{baud,port};
    return 1;
  }
  catch(int e){
    return -1;
  }
}

int Arduino::sendState(char data){
  try{
    if(data != state){
      state = data;
      serialPortObj->Write(&state);
    }
    return 1;
  }
  catch(int e){
    return -1;
  }
}