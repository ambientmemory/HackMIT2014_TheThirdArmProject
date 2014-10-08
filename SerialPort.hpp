#pragma once

#define ARDUINO_WAIT_TIME 2000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class SerialPort
{
public:
    SerialPort(const char *portName);
    ~SerialPort();

    int ReadData(char *buffer, unsigned int nbChar);
    bool WriteData(char *buffer, unsigned int nbChar);
    bool IsConnected();

private:
    HANDLE hSerial;
    bool connected;
    COMSTAT status;
    DWORD errors;
};
