#include "hwlib.hpp"
#include "KeyPad.hpp"
#include "KeyPadController.hpp"
int main() {
	WDT->WDT_MR = WDT_MR_WDDIS;
	hwlib::wait_ms(500);
	
	hwlib::target::pin_in row0(hwlib::target::pins::d23);
	hwlib::target::pin_in row1(hwlib::target::pins::d25);
	hwlib::target::pin_in row2(hwlib::target::pins::d27);
	hwlib::target::pin_in row3(hwlib::target::pins::d29);
	
	hwlib::target::pin_out column0(hwlib::target::pins::d31);
	hwlib::target::pin_out column1(hwlib::target::pins::d33);
	hwlib::target::pin_out column2(hwlib::target::pins::d35);
	hwlib::target::pin_out column3(hwlib::target::pins::d37);
	
	std::array<hwlib::pin_in*, 4> rows = { &row0, &row1, &row2, &row3 };
	std::array<hwlib::pin_out*, 4> columns = { &column0, &column1, &column2, &column3 };
	
	KeypadController controller(rows, columns);
	
	rtos::run();
}