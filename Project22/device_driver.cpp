#include <stdexcept>
#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int ret = 0, tmp, failed = 0;

    ret = (int)(m_hardware->read(address));
    for (int i = 0; i < 4; i++) {
        tmp = (int)(m_hardware->read(address));
        if (ret != tmp) {
            failed = 1;
        }
    }
    if (failed == 1)
        throw ReadFailException("Five Read Failed");
    // TODO: implement this method properly
    return ret;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}