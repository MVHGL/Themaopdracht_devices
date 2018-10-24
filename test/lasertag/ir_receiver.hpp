#pragma once
#include <cstdint>
#include "rtos.hpp"
#include "PauseListener.hpp"

class ir_receiver : public rtos::task<>
{
private:
	hwlib::pin_in & receiver;
	PauseListener& pauseListener;
	rtos::clock clock;
	enum state_t {IDLE, SIGNAL};
	state_t state = IDLE;
	int pauseCounter;
public:
	ir_receiver(PauseListener& pauseListener, hwlib::pin_in & receiver);
	void main() override;
};

