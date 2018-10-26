#pragma once
#include "rtos.hpp"

class ir_decoder : public rtos::task<> {
private:
	rtos::channel<int, 2> messages;
	
	void check_message();
	uint16_t get_checksum(const uint16_t& player_id, const uint16_t& data);
	uint16_t extract(const int& message);
	uint16_t checksum, player_id, data;
	enum state_t {IDLE, DECODING};
public:
	ir_decoder();
	void write_message(const int& message1, const int& message2);
	void main() override;
};

