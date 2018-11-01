// simple IR signal detector
#include "hwlib.hpp"
#include "ir_transmitter.hpp"
#include "ir_receiver.hpp"
#include "mainGameControlTask.hpp"
#include "gameTimeControl.hpp"
#include "displayTask.hpp"
#include "TriggerTask.hpp"

int main( void ){
   // kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
   
	namespace target	= hwlib::target;
	auto tsop_signal	= target::pin_in(target::pins::d10);
	auto ir_led			= target::d2_36kHz();
	auto trigger		= target::pin_in(target::pins::d9);
	
	// Display configuration
	auto scl			= hwlib::target::pin_oc(hwlib::target::pins::scl);
	auto sda			= hwlib::target::pin_oc(hwlib::target::pins::sda);
	auto i2c			= hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
	auto oled			= hwlib::glcd_oled(i2c, 0x3c);
	auto font			= hwlib::font_default_8x8();
	auto screen			= hwlib::window_ostream(oled, font);
	
	hwlib::wait_ms(500); 
	ir_transmitter transmitter(ir_led);
	displayTask display(screen);
	gameTimeControl control(display);
	mainGameControlTask mainGame(transmitter, display, control);
	TriggerTask triggerTask(trigger, mainGame);
	ir_receiver receiver(tsop_signal, mainGame);
	rtos::run();
}

