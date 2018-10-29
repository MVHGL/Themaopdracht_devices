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
				break;
			case SET_WEAPON: 
				break;
			case TRIGGER: 
				break;
			case MESSAGE_RECEIVE:
				handleMessageReceveived();
				break;
			case GAME_OVER:
				break;
		}
	}
}