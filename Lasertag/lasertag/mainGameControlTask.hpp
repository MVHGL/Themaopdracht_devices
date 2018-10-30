#pragma once
#include "rtos.hpp"
#include "ir_transmitter.hpp"

class mainGameControlTask : public rtos::task<> {
private:
	rtos::channel<int, 2> messages;
	ir_transmitter& transmitter;
	enum state_t {IDLE, SET_PLAYER, SET_WEAPON, TRIGGER, MESSAGE_RECEIVE, GAME_OVER};
	state_t state = IDLE;
public:
	mainGameControlTask(ir_transmitter& transmitter);
	void IRMessageReceived(const uint16_t& playerID, const uint16_t& data);
	void handleMessageReceived();
	void gameOver();
	void main() override;
};

