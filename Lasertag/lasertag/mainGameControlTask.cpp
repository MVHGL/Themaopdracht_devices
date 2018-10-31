#include "mainGameControlTask.hpp"

mainGameControlTask::mainGameControlTask(ir_transmitter& transmitter, displayTask& display):
	task("Maingame control task"),
	messages(this, "Main game task messages channel"),
	timeCompletedFlag(this, "Time completed flag"),
	transmitter(transmitter),
	triggerFlag(this, "Triggerflag"),
	display(display)
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

void mainGameControlTask::main() {
	while (true) {
		switch (state) {
			case IDLE:{
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
				transmitter.send(player.p_id, ownWeaponID);
				break;
			case MESSAGE_RECEIVE:
				handleMessageReceived();
				state = IDLE;
				break;
			case GAME_OVER:
				
				break;
		}
	}
}