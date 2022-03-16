#pragma once

#include <frc/SerialPort.h>

class Arduino{ // Arduino wrapper class using dynamic allocation for the port object to allow reintialization
  public:
    int baud;
    bool awaitingStatus;
    frc::SerialPort::Port port;
    frc::SerialPort *serialPortObj; // Serial port object pointer variable
    Arduino(int baudrate, frc::SerialPort::Port usbPort);
    int initComms(); // Creates new instance of serial port and assigns it to the arduino and does intial handshake
    auto getSensor(char id);
    int sendData(char id, char (&data)[6]);
    int checkStatus();
};