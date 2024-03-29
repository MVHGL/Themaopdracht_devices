/// @file ir_transmitter.hpp
#ifndef _IR_TRANSMITTER_HPP
#define _IR_TRANSMITTER_HPP
#include "hwlib.hpp"
#include <cstdint>
#include "rtos.hpp"

/// \brief
/// ir_transmitter class
/// \details
/// ir_transmitter class which is used to send IR messages. Implements rtos::task<>.
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
	/// \brief
	/// ir_transmitter constructor.
	/// \details
	/// ir_transmitter constructor which requires a reference to a hwlib::pint_out.
	ir_transmitter(hwlib::pin_out & transmitter);
	/// \brief
	/// Sends a message.
	/// \details
	/// Sends an IR message according to the two parameters given. Player_id and data may not be larger than 31.
	void send(const uint16_t & player_id, const uint16_t & data);
	/// \brief
	/// Main implementation
	/// \details
	/// Main implementation inherited from rtos::task<>.
	void main() override;
};
#endif