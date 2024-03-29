#include "mainGameControlTask.hpp"

mainGameControlTask::mainGameControlTask(ir_transmitter& transmitter, displayTask& display, gameTimeControl& timerControl):
	task("Maingame control task"),
	transmitter(transmitter),
	display(display),
	timerControl(timerControl),
	messages(this, "Main game task messages channel"),
	timeCompletedFlag(this, "Time completed flag"),
	triggerFlag(this, "Triggerflag"),
	playerIdPool("playerId pool"),
	weaponIdPool("WeaponId pool"),
	setPlayerParamsFlag(this, "Set player params flag"),
	channelFullFlag(this, "Message channel full")
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
	//hwlib::cout << "PLAYER_ID: " << playerID << "\nDATA: " << data << '\n';
	if(playerID == 0 && data == 31 && validTime){
		timerControl.startGameTimer();
		validStart = true;
	}else if(playerID == 0 && data > 0 && data < 30){
		timerControl.setTime(Time(data, 0));
		validTime = true;
	}else if(playerID > 0 && playerID != player.p_id){
		weaponLookup(data, enemyWeapon); // check enemy weapon, and edit the struct by reference
		player.hp -= enemyWeapon.damage;
		if (player.hp > 0 && player.hp <= 100) {
			display.showHealth(player.hp);
			display.shotBy(playerID, enemyWeapon.name);
		} else {
			gameOver();
		}
	}else{
		hwlib::cout << "{ERROR}: invalid message received\n";
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
	validStart = false;
	validTime = false;
	while (true) {
		switch (state) {
			case REGISTER_GAME:{
				wait(setPlayerParamsFlag);
				player.p_id = playerIdPool.read();
				ownWeaponID = weaponIdPool.read();
				//hwlib::cout << "PLAYER ID: " << player.p_id << "\nWEAPON ID: " << ownWeaponID << '\n';
				weaponLookup(ownWeaponID, ownWeapon);
				display.showAmmo(ownWeapon.ammo);
				display.showWeapon(ownWeapon.name);
				display.showHealth(player.hp);
				state = REGISTER_TIME;
				break;
			}
			case REGISTER_TIME:{
				display.showString("Waiting for\n   game time");
				wait(channelFullFlag); // Wait for a message to set time
				handleMessageReceived(); // Handle the message
				display.returnIdle();
				if(!validTime){
					hwlib::cout << "{ERROR}: invalid time message recieved, try again!\n";
					break;
				}
				display.showString("Waiting for\n    start");
				wait(channelFullFlag); // Wait for a message to start the game
				handleMessageReceived(); // Handle the message
				display.returnIdle();
				if(validStart){
					state = IDLE;
				}
				break;
			}
			case IDLE:{
				if (timerControl.isGameTimeOver()) {
					state = GAME_OVER;
					break;
				}
				auto event = wait(channelFullFlag + timeCompletedFlag + triggerFlag);
				if 		(event == channelFullFlag) 		state = MESSAGE_RECEIVE;
				else if (event == timeCompletedFlag) 	state = GAME_OVER;
				else if (event == triggerFlag)			state = TRIGGER;
				break;
			}
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
				display.showString("GAME OVER");
				break;
		}
	}
}