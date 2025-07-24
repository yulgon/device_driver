#include <iostream>
#include <vector>
#include "device_driver.h"

using namespace std;

class RealDevice : public FlashMemoryDevice
{
public:
	virtual unsigned char read(long address) = 0;
	virtual void write(long address, unsigned char data) = 0;
};

void readAndPrint(FlashMemoryDevice *mock, long startAddr, long endAddr)
{
	DeviceDriver driver{ mock };
	vector<int> arr;

	for (long addr = startAddr; addr <= endAddr ; addr++)
		arr.push_back(driver.read(startAddr));

	for (int val : arr) {
		cout << "0x" << hex << val << " ";
	}

	cout << '\n';
}

void writeAll(FlashMemoryDevice* mock, int value)
{
	DeviceDriver driver{ mock };

	for (long addr = 0x00; addr <= 0x04; addr++)
		driver.write(addr, value);
}

