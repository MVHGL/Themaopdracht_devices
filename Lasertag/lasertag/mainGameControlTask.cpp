#include "mainGameControlTask.hpp"
#include "playerData.hpp"

mainGameControlTask::mainGameControlTask():
	task("Maingame control task"),
	messages(this, "Main game task messages channel")
{
}

void mainGameControlTask::IRMessageReceived(const uint16_t& playerID, const uint16_t& data) {
	messages.write(playerID);
	messages.write(data);
}

void mainGameControlTask::handleMessageReceived() {
	/*int read = messages.read();
	player.hp -= weapons[];
	break;
			
	}*/
}


void mainGameControlTask::main() {
	while (true) {
		switch (state) {
			case IDLE:
				// auto event = wait(messages + ... + ... + ...);
				// if (event == messages)
				wait(messages);
				state = MESSAGE_RECEIVE;
				break;
			case SET_PLAYER: 
				//wait(playerFlag);
				//int playerID = playerPool.read();
				//setPlayer(playerID);
				break;
			case SET_WEAPON: 
				//wait(weaponFlag);
				//int weapon = weaponPool.read();
				//setWeapon(weapon);
				break;
			case TRIGGER: 
				//wait(triggerFlag);
				//transmitterController.send(player.p_id, weapon.id); // data klopt nog niet(tweede parameter)
				break;
			case MESSAGE_RECEIVE:
				//handleMessageReceveived();
				break;
			case GAME_OVER:
				//wait(timeCompletedFlag);
				//gameOver();
				break;
		}
	}
}