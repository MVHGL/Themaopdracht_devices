#pragma once
#include "hwlib.hpp"

class ir_protocol
{
private:
	hwlib::pin_in & reciever;		//The module's signal pin that gets the IR-signal
	hwlib::pin_out & transmitter;	//The IR led that send's the signal
public:
	ir_protocol(hwlib::pin_in & reciever, hwlib::pin_out & transmitter);
	void send(const int & player_id, const int & )
};

