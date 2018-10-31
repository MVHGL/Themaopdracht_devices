#ifndef _IR_TRANSMITTER_HPP
#define _IR_TRANSMITTER_HPP
#include "hwlib.hpp"
#include <cstdint>
#include "rtos.hpp"

class ir_transmitter : public rtos::task<>
{
private:
	hwlib::pin_out& transmitter;	//The IR led that send's the signal
	rtos::pool<uint16_t> playerIDPool;
	rtos::pool<uint16_t> dataPool;
	rtos::flag transmitFlag;
	rtos::mutex transmitMutex;
	
	uint16_t get_checksum(const uint16_t&, const uint16_t&);
	void writeIRMessage();
	void send_bit(const bool& value);
	
	enum state_t{IDLE, SEND};
	state_t state;
public:

	ir_transmitter(hwlib::pin_out & transmitter);
	void send(const uint16_t & player_id, const uint16_t & data);
	void main() override;
};
#endif