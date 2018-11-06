/// @file ir_decoder.hpp
#ifndef _IR_DECODER_HPP
#define _IR_DECODER_HPP
#include "rtos.hpp"
#include "mainGameControlTask.hpp"
/// \brief
/// ir_decoder class
/// ir_decoder class which implements the rtos::task<>, used for decode IR messages.
class ir_decoder : public rtos::task<> {
private:
	rtos::channel<int, 2> messages;
	mainGameControlTask& mainGame;
	
	void check_message();
	uint16_t get_checksum(const uint16_t& player_id, const uint16_t& data);
	uint16_t extract(const int& message);
	uint16_t checksum, player_id, data;
	enum state_t {IDLE, DECODING};
public:
	/// \brief
	/// ir_decoder constructor.
	/// ir_decoder constructor which requires a reference to mainGameControlTask object.
	ir_decoder(mainGameControlTask& mainGame);
	/// \brief
	/// Writes a message
	/// \details
	/// Writes a message to its channel.
	void write_message(const int& message1, const int& message2);
	/// \brief
	/// Main implementation
	/// \details
	/// Main implementation which is inherited from rtos::task<>.
	void main() override;
};
#endif
