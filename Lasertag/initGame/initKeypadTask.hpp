/// @file initKeypadTask.hpp
#ifndef INITKEYPADTASK_HPP
#define INITKEYPADTASK_HPP

#include "rtos.hpp"
#include "hwlib.hpp"
#include "initGame.hpp"

/// \brief
/// keypad control
/// \details
/// This class implements the rtos::task<> class and reads the input of a 4 by 4 matrix keypad. 
class initKeypadTask : public rtos::task<>
{
private:
	hwlib::target::pin_oc out0 = hwlib::target::pins::a7; 
	hwlib::target::pin_oc out1 = hwlib::target::pins::a6; 
	hwlib::target::pin_oc out2 = hwlib::target::pins::a5; 
	hwlib::target::pin_oc out3 = hwlib::target::pins::a4;

	hwlib::target::pin_in in0 = hwlib::target::pins::a3; 
	hwlib::target::pin_in in1 = hwlib::target::pins::a2; 
	hwlib::target::pin_in in2 = hwlib::target::pins::a1; 
	hwlib::target::pin_in in3 = hwlib::target::pins::a0; 

	hwlib::port_oc_from_pins out_port = hwlib::port_oc_from_pins( out0, out1, out2, out3 );
	hwlib::port_in_from_pins in_port = hwlib::port_in_from_pins( in0,  in1,  in2,  in3  );
	hwlib::matrix_of_switches matrix = hwlib::matrix_of_switches(out_port, in_port); 
	hwlib::keypad<16> keypad = hwlib::keypad<16>(matrix, "123A456B789C*0#D");
	
	enum state_t {IDLE, BUTTON_PRESSED};
	state_t state = IDLE;
	initGame & initGameTask;
	char c;
	
public:
	/// \brief
	/// initKeypadTask constructor
	/// \details
	/// This constructor needs a refrence to initGame object. 
	initKeypadTask(initGame & initGameTask);
	/// \brief
	/// initKeypadTask's main method
	/// \details
	/// This method implements the rto::task<> method 
	void main();

};

#endif // KEYPADTASK_HPP
