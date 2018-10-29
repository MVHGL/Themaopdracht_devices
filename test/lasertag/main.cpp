// simple IR signal detector
#include "hwlib.hpp"
#include "ir_transmitter.hpp"
#include "ir_receiver.hpp"
#include "mainGameControlTask.hpp"

int main( void ){
   // kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
   
	namespace target = hwlib::target;
   
	auto tsop_signal = target::pin_in( target::pins::d10 );
	auto ir_led	    = target::d2_36kHz();
	hwlib::wait_ms(500); 
	mainGameControlTask mainGame;
	
	ir_receiver receiver(tsop_signal, mainGame);
	rtos::run();
    
	while(true){
		auto transmitter = ir_transmitter(ir_led);
		transmitter.send(31,31);
		hwlib::wait_ms(3000);
	}
}

