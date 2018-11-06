#include "../lasertag/ir_transmitter.hpp"
#include "hwlib.hpp"
#include "rtos.hpp"
#include "initGame.hpp"
#include "initDisplayTask.hpp"
#include "initKeypadTask.hpp"

int main() {
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
   
	//display 
	auto scl= hwlib::target::pin_oc(hwlib::target::pins::a9);
	auto sda = hwlib::target::pin_oc(hwlib::target::pins::a8);
	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl,sda);
	auto display = hwlib::glcd_oled_buffered(i2c_bus, 0x3c);
	auto font = hwlib::font_default_8x8(); 
	auto oled= hwlib::window_ostream(display, font);
	
	//pin voor het verzenden van ir signal. 
	auto IRLed= hwlib::target::pin_out(hwlib::target::pins::d5);
	auto transmitter = ir_transmitter(IRLed); 
	
	
	initDisplayTask displaytask(oled);
	initGame initGameTask(displaytask, transmitter);
	initKeypadTask keypad_task(initGameTask);
	
	//
	rtos::run();
}