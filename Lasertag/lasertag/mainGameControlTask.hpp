#pragma once
#include "rtos.hpp"
#include "ir_transmitter.hpp"
#include "playerData.hpp"
#include "displayTask.hpp"
class mainGameControlTask : public rtos::task<> {
private:
	rtos::channel<int, 2> messages;
	rtos::flag timeCompletedFlag;
	ir_transmitter& transmitter;
	rtos::flag triggerFlag;
	displayTask& display;
	enum state_t {IDLE, SET_PLAYER, SET_WEAPON, TRIGGER, MESSAGE_RECEIVE, GAME_OVER};
	state_t state = IDLE;
	uint16_t ownWeaponID;
	Weapon enemyWeapon;
	Weapon ownWeapon;
	Player player;
	
	void handleMessageReceived();
public:
	mainGameControlTask(ir_transmitter& transmitter, displayTask& display);
	void IRMessageReceived(const uint16_t& playerID, const uint16_t& data);
	void triggered();
	void gameOver();
	void main() override;
};

