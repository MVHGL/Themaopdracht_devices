// simple IR signal detector
#include "hwlib.hpp"
#include "ir_transmitter.hpp"
#include "ir_receiver.hpp"
#include "MessageDecoder.hpp"

int main( void ){
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   namespace target = hwlib::target;
   
   auto tsop_signal = target::pin_in( target::pins::d8 );
   auto ir_led	    = target::d2_36kHz();
   hwlib::wait_ms(500); 
   MessageDecoder decoder;
   ir_receiver receiver(decoder, tsop_signal);
   rtos::run();
}

