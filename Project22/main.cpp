#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};
/*
TEST(DeviceDriver, ReadFromHW) {
	// TODO : replace hardware with a Test Double
	FlashMemoryDevice* hardware = nullptr;
	DeviceDriver driver{ hardware };
	int data = driver.read(0xFF);
	EXPECT_EQ(0, data);
}
*/

TEST(DeviceDriver, FiveRead) {
	FlashMock mock;

	EXPECT_CALL(mock, read((long)0xB))
		.Times(5);

	DeviceDriver driver{ &mock };

	int data = driver.read(0xB);
}

TEST(DeviceDriver, FiveRead1fail) {
	FlashMock mock;

	EXPECT_CALL(mock, read((long)0xB))
		.Times(5)
		.WillOnce(Return(4))
		.WillRepeatedly(Return(5));

	DeviceDriver driver{ &mock };

	//int data = driver.read(0xB);

	EXPECT_THROW({ driver.read(0xB); }, ReadFailException);
}


int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}