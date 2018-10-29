#pragma once
#include <cstdint>
#include "rtos.hpp"
#include "ir_decoder.hpp"

class ir_receiver : public rtos::task<>
{
private:
	hwlib::pin_in & receiver;
	ir_decoder decoder;
	int pause_count;
	rtos::clock clock;
	rtos::channel<int, 33> pauses;
	int counter;
	enum state_t {IDLE, SIGNAL, MESSAGE};
	state_t state = IDLE;
	
	void pause_detected(const int& n);
	void get();
public:
	ir_receiver(hwlib::pin_in & receiver);
	void putMessage();
	void main() override;
};

