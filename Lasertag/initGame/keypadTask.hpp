#ifndef KEYPADTASK_HPP
#define KEYPADTASK_HPP

#include "rtos.hpp"
#include "hwlib.hpp"
#include "initGame.hpp"

class keypadTask : public rtos::task<>
{
private:
	hwlib::target::pin_oc( hwlib::target::pins::a0 ) out0;
	hwlib::target::pin_oc( hwlib::target::pins::a1 ) out1;
	hwlib::target::pin_oc( hwlib::target::pins::a2 ) out2;
	hwlib::target::pin_oc( hwlib::target::pins::a3 ) out3;

	hwlib::target::pin_in( hwlib::target::pins::a4 ) in0;
	hwlib::target::pin_in( hwlib::target::pins::a5 ) in1;
	hwlib::target::pin_in( hwlib::target::pins::a6 ) in2;
	hwlib::target::pin_in( hwlib::target::pins::a7 ) in3;

	hwlib::port_oc_from_pins( out0, out1, out2, out3 ) out_port;
	hwlib::port_in_from_pins( in0,  in1,  in2,  in3  ) in_port;
	hwlib::matrix_of_switches( out_port, in_port ) & matrix;
	hwlib::keypad<16>( matrix, "123A456B789C*0#D" ) & keypad;
	initGame & initgameTask;
	enum state_t {IDLE, BUTTON_PRESSED);
	state_t state = IDLE;
	
public:
	keypadTask();
	void main();

};

#endif // KEYPADTASK_HPP
