#include "ir_transmitter.hpp"
#include "hwlib.hpp"
#include "rtos.hpp"
//#include "keypad.hpp"



int main() {
	//Keypad . 
	auto out0 = hwlib::target::pin_oc( hwlib::target::pins::a0 );
	auto out1 = hwlib::target::pin_oc( hwlib::target::pins::a1 );
	auto out2 = hwlib::target::pin_oc( hwlib::target::pins::a2 );
	auto out3 = hwlib::target::pin_oc( hwlib::target::pins::a3 );

	auto in0  = hwlib::target::pin_in( hwlib::target::pins::a4 );
	auto in1  = hwlib::target::pin_in( hwlib::target::pins::a5 );
	auto in2  = hwlib::target::pin_in( hwlib::target::pins::a6 );
	auto in3  = hwlib::target::pin_in( hwlib::target::pins::a7 );

	auto out_port = hwlib::port_oc_from_pins( out0, out1, out2, out3 );
	auto in_port  = hwlib::port_in_from_pins( in0,  in1,  in2,  in3  );
	auto matrix   = hwlib::matrix_of_switches( out_port, in_port );
	auto keypad   = hwlib::keypad< 16 >( matrix, "123A456B789C*0#D" );
	
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
	
	initGame initGameTask(oled);
	displayTask displaytask(oled);
	//task task task(keypad)
	//rtos::run();
}