// simple IR signal detector
#include "hwlib.hpp"
#include "ir_transmitter.hpp"
#include "ir_receiver.hpp"
int main( void ){
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   namespace target = hwlib::target;
   
   auto tsop_signal = target::pin_in( target::pins::d8 );
   auto ir_led	    = target::d2_36kHz();
   hwlib::wait_ms(500); 
   
   ir_receiver receiver(tsop_signal);
   rtos::run();
}

