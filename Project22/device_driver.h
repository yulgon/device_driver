#pragma once
#include "flash_memory_device.h"
using namespace std;

class ReadFailException :public exception
{
public:
    ReadFailException(string msg) {}
};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};
