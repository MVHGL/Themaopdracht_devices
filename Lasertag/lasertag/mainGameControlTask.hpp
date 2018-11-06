#ifndef _MAINGAMECONTROLTASK_HPP
#define _MAINGAMECONTROLTASK_HPP
#include "rtos.hpp"
#include "ir_transmitter.hpp"
#include "displayTask.hpp"
#include "playerData.hpp"
#include "gameTimeControl.hpp"
class mainGameControlTask : public rtos::task<> {
private:
	ir_transmitter& transmitter;
	displayTask& display;
	gameTimeControl& timerControl;
	rtos::channel<int, 2> messages;
	rtos::flag timeCompletedFlag;
	rtos::flag triggerFlag;
	rtos::pool<uint16_t> playerIdPool;
	rtos::pool<uint16_t> weaponIdPool;
	rtos::flag setPlayerParamsFlag;
	rtos::flag channelFullFlag;
	enum state_t {REGISTER_GAME, REGISTER_TIME, IDLE, SET_PLAYER, SET_WEAPON, TRIGGER, MESSAGE_RECEIVE, GAME_OVER};
	state_t state;
	uint16_t ownWeaponID;
	Weapon enemyWeapon;
	Weapon ownWeapon;
	Player player;
	bool validTime, validStart;
	void handleMessageReceived();
	void handleTriggerButton();
public:
	mainGameControlTask(ir_transmitter& transmitter, displayTask& display, gameTimeControl& timerControl);
	
	void IRMessageReceived(const uint16_t& playerID, const uint16_t& data);
	void triggered();
	void gameOver();
	void setPlayerParams(const uint16_t& playerID, const uint16_t& weaponID);
	void main() override;
};
#endif
