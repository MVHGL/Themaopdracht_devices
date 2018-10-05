// simple IR signal detector

#include "hwlib.hpp"
#include "ir_protocol.hpp"
int main( void ){
   
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   namespace target = hwlib::target;
   
   auto tsop_signal = target::pin_in( target::pins::d8 );
   auto ir_led	    = target::d2_36kHz();
   hwlib::wait_ms(500); // omdat hwlib kkkk skeer is
   
   ir_protocol p(tsop_signal, ir_led);
   p.send(32, 27);
}

