#include "ir_protocol.hpp"

ir_protocol::ir_protocol(hwlib::pin_in & reciever, hwlib::pin_out & transmitter):
	reciever(reciever),
	transmitter(transmitter)
{};



