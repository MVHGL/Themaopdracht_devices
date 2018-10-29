#pragma once
#include "rtos.hpp"

class mainGameControlTask : public rtos::task<> {
	rtos::channel<int, 10> messages;
	enum state_t {IDLE, SET_PLAYER, SET_WEAPON, TRIGGER, MESSAGE_RECEIVE, GAME_OVER};
	state_t state = IDLE;
public:
	mainGameControlTask();
	void IRMessageReceived(const uint16_t& playerID, const uint16_t& data);
	void main() override;
};

