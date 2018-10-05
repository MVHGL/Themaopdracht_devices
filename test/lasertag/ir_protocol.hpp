#pragma once
#include "hwlib.hpp"
#include <cstdint>

class ir_protocol
{
private:
	hwlib::pin_in& reciever;		//The module's signal pin that gets the IR-signal
	hwlib::pin_out& transmitter;	//The IR led that send's the signal
	
	uint16_t get_checksum(const uint16_t&, const uint16_t&);
	void send_bit(const bool& value);
public:

	ir_protocol(hwlib::pin_in & reciever, hwlib::pin_out & transmitter);
	void send(const uint16_t & player_id, const uint16_t & data);
};

