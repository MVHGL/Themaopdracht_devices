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
	channelFullFlag(this, "Message channel full"),
	timerControl(timerControl)
	{}

void mainGameControlTask::IRMessageReceived(const uint16_t& playerID, const uint16_t& data) {
	messages.write(playerID);
	messages.write(data);
	channelFullFlag.set();
}

void mainGameControlTask::handleTriggerButton() {
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
}

void mainGameControlTask::triggered() {
	triggerFlag.set();
}

void mainGameControlTask::handleMessageReceived() {
	uint16_t playerID = messages.read();
	uint16_t data = messages.read();
	
	weaponLookup(data, enemyWeapon); // check enemy weapon, and edit the struct by reference
	player.hp -= enemyWeapon.damage;
	
	if (player.hp > 0 && player.hp <= 100) {
		display.showHealth(player.hp);
		display.shotBy(playerID, enemyWeapon.name);
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
	state = REGISTER_GAME;
	timerControl.setTime(Time(10,0));
	/*ownWeaponID = 2;
	weaponLookup(ownWeaponID, ownWeapon);
	display.showAmmo(ownWeapon.ammo);
	display.showWeapon(ownWeapon.name);
	display.showHealth(player.hp);
	player.p_id = 3;*/
	while (true) {
		switch (state) {
			case REGISTER_GAME:{
				hwlib::cout << "Now registering a game!\n";
				wait(setPlayerParamsFlag);
				player.p_id = playerIdPool.read();
				ownWeaponID = weaponIdPool.read();
				weaponLookup(ownWeaponID, ownWeapon);
				display.showAmmo(ownWeapon.ammo);
				display.showWeapon(ownWeapon.name);
				display.showHealth(player.hp);
				break;
			}
			case IDLE:{
				timerControl.startGameTimer();
				if (!timerControl.isGameTimeOver()) {
					/*display.showHealth(player.hp);
					display.showAmmo(ownWeapon.ammo);
					display.showWeapon(ownWeapon.name);
					display.shotBy(2, enemyWeapon.name);*/
				} else {
					state = GAME_OVER;
				}
				auto event = wait(channelFullFlag + timeCompletedFlag + triggerFlag);
				if 		(event == channelFullFlag) 		state = MESSAGE_RECEIVE;
				else if (event == timeCompletedFlag) 	state = GAME_OVER;
				else if (event == triggerFlag)			state = TRIGGER;
				break;
			}
			case SET_PLAYER: 
				break;
			case SET_WEAPON: 
				break;
			case TRIGGER:
				handleTriggerButton();
				break;
			case MESSAGE_RECEIVE:
				if (!timerControl.isGameTimeOver()) { 
					handleMessageReceived();
				} else {
					state = GAME_OVER;
				}
				state = IDLE;
				break;
			case GAME_OVER:
				display.gameOver();
				break;
		}
	}
}