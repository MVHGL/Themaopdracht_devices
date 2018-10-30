#pragma once
#include "rtos.hpp"
#include "ir_transmitter.hpp"
#include "playerData.hpp"

class mainGameControlTask : public rtos::task<> {
private:
	rtos::channel<int, 2> messages;
	rtos::flag timeCompletedFlag;
	ir_transmitter& transmitter;
	rtos::flag triggerFlag;
	
	enum state_t {IDLE, SET_PLAYER, SET_WEAPON, TRIGGER, MESSAGE_RECEIVE, GAME_OVER};
	state_t state = IDLE;
	uint16_t ownWeaponID;
	Weapon enemyWeapon;
	Weapon ownWeapon;
	Player player;
	
	void handleMessageReceived();
public:
	mainGameControlTask(ir_transmitter& transmitter);
	void IRMessageReceived(const uint16_t& playerID, const uint16_t& data);
	void triggered();
	void gameOver();
	void main() override;
};

