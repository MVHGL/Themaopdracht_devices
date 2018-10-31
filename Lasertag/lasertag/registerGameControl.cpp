registerGameControl::registerGameControl(mainGameControlTask & mainGame):
	task("Register game parameters"),
	mainGame(mainGame),
	registerTimer(this, "timeout timer for registering"),
	keypadChannel(this, "channel for user input")
	{}


void registerGameControl::buttonPressed(const char & keypad_char){
		keypadChannel.write(keypad_char)
}

void registerGameControl::main(){
	uint16_t player_id = 0;
	uint16_t weapon_id = 0;
	state_t state = IDLE;
	while (1){
		switch(state){
			case IDLE:
				auto input = (keypadChannel.read());
				if (input == 'A'){ 	// this command means we want a player id
					state = GET_PLAYER_ID;
				}
				else if (input == 'B'){	// this command means we want to choose a weapon
					state = GET_WEAPON;
				}
				else if (input == 'C'){
					state = SEND;
				}
				break;

			case GET_PLAYER_ID:
				registerTimer.set(10'000'000); // set timer for 10 seconds
				for(int i=0; i<2; i++){ // trying to read two chars from channel
					auto event = wait(registerTimer + keypadChannel);
					if (event == keypadChannel){   // new key was pressed
						auto input = keypadChannel.read();
						if (input >= '0' && input <= '9'){ // input was numeric
							player_id += input;
						}
					}
				}

				state = IDLE;
				break;

			case GET_WEAPON:
				registerTimer.set(10'000'000); // set timer for 10 seconds
				auto event = (registerTimer + keypadChannel;
				if (event == keypadChannel){ // new key was pressed
					auto input = keypadChannel.read();
					if (input >= 0 && input <= 9){ // input was numeric
						weapon_id += input;
					}
				}

				state = IDLE;
				break;

			case SEND: // pseudo state sending the parameters to the other tasks
				mainGameControlTask.setPlayerParams(); // set the player parameters
				state = IDLE;
				break;
		}
	}
}
