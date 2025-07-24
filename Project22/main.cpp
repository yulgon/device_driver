#include "gmock/gmock.h"
#include "device_driver.h"
#include "app.cpp"

using namespace testing;
using namespace std;

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

TEST(DeviceDriver, WriteSuccess) {
	FlashMock mock;

	EXPECT_CALL(mock, read((long)0xB))
		.WillOnce(Return(0xFF))
		.WillOnce(Return(0xFF))
		.WillOnce(Return(0xFF))
		.WillOnce(Return(0xFF))
		.WillOnce(Return(0xFF))
		.WillRepeatedly(Return(0x77));

	DeviceDriver driver{ &mock };

	//int data = driver.read(0xB);
	driver.write(0xB, 0x77);

	EXPECT_THAT(0x77, Eq(driver.read(0xB)));
}

TEST(DeviceDriver, WriteFailed) {
	FlashMock mock;

	EXPECT_CALL(mock, read((long)0xB))
		.WillRepeatedly(Return(0xB));

	DeviceDriver driver{ &mock };

	//int data = driver.read(0xB);

	EXPECT_THROW({ driver.write(0xB, 0x77); }, WriteFailException);
}

TEST(DeviceDriver, readAndPrint) {
	FlashMock mock;

	EXPECT_CALL(mock, read(_))
		.WillRepeatedly(Return(0x77));

	DeviceDriver driver{ &mock };

	//int data = driver.read(0xB);
	readAndPrint(&mock, 0x0, 0x4);

	EXPECT_THAT(0x77, Eq(driver.read(0)));
	EXPECT_THAT(0x77, Eq(driver.read(1)));
	EXPECT_THAT(0x77, Eq(driver.read(2)));
	EXPECT_THAT(0x77, Eq(driver.read(3)));
	EXPECT_THAT(0x77, Eq(driver.read(4)));
	//EXPECT_THROW({ driver.write(0xB, 0x77); }, WriteFailException);
}

TEST(DeviceDriver, writeAll) {
	FlashMock mock;

	EXPECT_CALL(mock, read(_))
		.WillRepeatedly(Return(0x77));

	DeviceDriver driver{ &mock };
	writeAll(&mock, 0x77);
	//int data = driver.read(0xB);
	EXPECT_THAT(0x77, Eq(driver.read(0)));
	EXPECT_THAT(0x77, Eq(driver.read(1)));
	EXPECT_THAT(0x77, Eq(driver.read(2)));
	EXPECT_THAT(0x77, Eq(driver.read(3)));
	EXPECT_THAT(0x77, Eq(driver.read(4)));
	//EXPECT_THROW({ driver.write(0xB, 0x77); }, WriteFailException);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}