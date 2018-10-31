#ifndef _IR_DECODER_HPP
#define _IR_DECODER_HPP
#include "rtos.hpp"
#include "mainGameControlTask.hpp"

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
	ir_decoder(mainGameControlTask& mainGame);
	void write_message(const int& message1, const int& message2);
	void main() override;
};
#endif
