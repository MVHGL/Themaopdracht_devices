registerGameControl::registerGameControl(mainGameControlTask & mainGame, displayTask & display):
	task("Register game parameters"),
	mainGame(mainGame),
	registerTimer(this, "timeout timer for registering"),
	keypadChannel(this, "channel for user input"),
	display(display)
	{}


void registerGameControl::buttonPressed(hwlib::istream & keypad){
		keypadChannel.write(keypad.getc());
}

void registerGameControl::main(){
	uint16_t player_id = 0;
	uint16_t weapon_id = 0;
	state_t state = IDLE;
	while (1){
		switch(state){
			/* this state will wait on the keypad until it receives */
			/* either a command to set the player ID or weapon ID.  */
			/* else it can send these parameters to the game with # */
			case IDLE:
				auto input = (keypadChannel.read());
				if (input == 'a'){ 	// this command means we want a player ID
					state = GET_PLAYER_ID;
				}
				else if (input == 'b'){	// this command means we want to choose a weapon
					state = GET_WEAPON;
				}
				else if (input == '#'){
					mainGameControlTask.setPlayerParams(player_id, weapon_id); // set the player parameters
				}
				break;


			/* this state loops two times to get the player ID. this means */
			/* that if the player wants ID 1 he or she should push 0 first */
			/* and 1 second (eventually followed by # in the IDLE state)   */
			case GET_PLAYER_ID:
				registerTimer.set(10'000'000); // set timer for 10 seconds
				for(int i=0; i<2; i++){ // trying to read two chars from channel
					displayTask.showChoice(false); // show it on the oled
					auto event = wait(registerTimer + keypadChannel);
					if (event == keypadChannel){   // new key was pressed
						auto input = keypadChannel.read();
						if (input >= '0' && input <= '9'){ // input was numeric
							player_id += uint16_t(input-48); //typecast to int
							if (i=0){
								player_id * 10; // first num is base 10
							}
						}
						else{
							hwlib::cout << "{DEBUG}: non numeric input given when numeric was expected!\n";
							player_id = 0; // reset player ID
						}
					}
				}

				state = IDLE;
				break;


			/* this state will do the same as GET_PLAYER_ID */
			/* except it wil only take 1 number and set the */
			/* weapon ID.                                   */
			case GET_WEAPON:
				registerTimer.set(10'000'000); // set timer for 10 seconds
				auto event = (registerTimer + keypadChannel;
				displayTask.showChoice(true);
				if (event == keypadChannel){ // new key was pressed
					auto input = keypadChannel.read();
					if (input >= '0' && input <= '9'){ // input was numeric
						weapon_id += uint16_t(input-48); //typecast to int
					}
					else{ // input was not numeric
						hwlib::cout << "{DEBUG}: non numeric input given when numeric was expected!\n";
						weapon_id = 0; // reset weapon ID
					}
				}

				state = IDLE;
				break;
		}
	}
}
