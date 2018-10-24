#pragma once
#include "PauseListener.hpp"
#include "rtos.hpp"
class MessageDecoder : public rtos::task<>, public PauseListener {
	rtos::channel<int, 32> pauses;
	enum state_t {IDLE, MESSAGE};
	state_t state;
	int message, pause, amount;
	
	void check();
public:
	MessageDecoder();
	void pauseDetected(const int& pause) override;
	void main() override;
};

