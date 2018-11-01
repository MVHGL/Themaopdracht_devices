#include "mainGameControlTask.hpp"

mainGameControlTask::mainGameControlTask(ir_transmitter& transmitter, displayTask& display, gameTimeControl& timerControl):
	task("Maingame control task"),
	messages(this, "Main game task messages channel"),
	timeCompletedFlag(this, "Time completed flag"),
	transmitter(transmitter),
	triggerFlag(this, "Triggerflag"),
	display(display),
	playerIdPool("playerId pool"),
	weaponIdPool("WeaponId pool"),
	setPlayerParamsFlag(this, "Set player params flag"),
	timerControl(timerControl)
	{}

void mainGameControlTask::IRMessageReceived(const uint16_t& playerID, const uint16_t& data) {
	messages.write(playerID);
	messages.write(data);
}

void mainGameControlTask::triggered() {
	triggerFlag.set();
}

void mainGameControlTask::handleMessageReceived() {
	uint16_t playerID = messages.read();
	uint16_t data = messages.read();
	
	weaponLookup(data, enemyWeapon); // check enemy weapon, and edit the struct by reference
	player.hp -= enemyWeapon.damage;
	
	if (player.hp > 0) {
		display.shotBy(playerID, enemyWeapon.name);
		display.showHealth(player.hp);
	} else {
		gameOver();
	}
}

void mainGameControlTask::gameOver() {
	timeCompletedFlag.set();
}

void mainGameControlTask::setPlayerParams(const uint16_t& playerID, const uint16_t& weaponID){
	playerIdPool.write(playerID);
	weaponIdPool.write(weaponID);
	setPlayerParamsFlag.set();
}

void mainGameControlTask::main() {
	timerControl.setTime(Time(10,0));
	weaponLookup(1, ownWeapon);
	display.showAmmo(ownWeapon.ammo);
	display.showWeapon(ownWeapon.name);
	while (true) {
		switch (state) {
			case IDLE:{
				timerControl.startGameTimer();
				if (!timerControl.isGameTimeOver()) {  
					//display.showHealth(player.hp);
					//display.showAmmo(ownWeapon.ammo);
					//display.showWeapon(ownWeapon.name);
					//display.shotBy(2, enemyWeapon.name);
				} else 
					state = GAME_OVER;
				
				auto event = wait(messages + timeCompletedFlag + triggerFlag);
				if 		(event == messages) 			state = MESSAGE_RECEIVE;
				else if (event == timeCompletedFlag) 	state = GAME_OVER;
				else if (event == triggerFlag)			state = TRIGGER;
				break;
			}
			case SET_PLAYER: 
				break;
			case SET_WEAPON: 
				break;
			case TRIGGER:
				if (!timerControl.isGameTimeOver()) {
					if(ownWeapon.ammo > 0){
						transmitter.send(player.p_id, ownWeaponID);
						ownWeapon.ammo -=1;
					}
					display.showAmmo(ownWeapon.ammo);
					state = IDLE;
				} else {
					state = GAME_OVER;
				}
				break;
			case MESSAGE_RECEIVE:
				if (!timerControl.isGameTimeOver()) { /*...*/ } else state = GAME_OVER;
				handleMessageReceived();
				state = IDLE;
				break;
			case GAME_OVER:
				display.gameOver();
				break;
		}
	}
}