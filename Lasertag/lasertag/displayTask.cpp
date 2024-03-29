#include "displayTask.hpp"

displayTask::displayTask(hwlib::window_ostream & display):
	task("Display task"),
	display(display),
	timeLeftPool("Time left pool"),
	timeLeftFlag(this, "Time left flag"),
	ammoPool("Ammo pool"),
	ammoFlag(this, "Ammo flag"),
	weaponNamePool("Weapon Pool"),
	showWeaponFlag(this, "Show weapon flag"),
	healthPool("Health pool"),
	healthFlag(this, "Health flag"),
	messageFlag(this, "Custom message flag"),
	messagePool("Custom message pool"),
	enemyWeaponNamePool("Enemy weapon pool"),
	enemyPlayerIdPool("Enemy player ID pool"),
	shotByFlag(this, "Shot by flag"),
	shotByClock(this, 5'000'000, "Shot by timeout clock"),
	choicePool("Choosing weapon or player ID"),
	choiceFlag(this, "Set weapon or player ID flag"),
	playerIdPool("Player id pool"),
	idleFlag(this, "Go back to idle flag"),
	numberPool("Pool to show a number on the screen"),
	numberFlag(this, "Flag to read number")
{}

void displayTask::main(){
	bool first = true;
	while(true){
		switch(state_d){
			case IDLE:{
				//hwlib::cout << "back in idle\n";
				auto display_event = wait(timeLeftFlag + ammoFlag + showWeaponFlag + healthFlag + messageFlag + shotByFlag + choiceFlag);
				if(display_event == timeLeftFlag){
					time = timeLeftPool.read();
					state_d = SHOW;
				}else if(display_event == ammoFlag){
					ammo = ammoPool.read();
					if (first){
						ammoStr = ammo;
						first = false;
					}
					state_d = SHOW;
				}else if(display_event == showWeaponFlag){
					weaponName = weaponNamePool.read();
					state_d = SHOW;
				}else if(display_event == healthFlag){
					health = healthPool.read();
					state_d = SHOW;
				}else if(display_event == messageFlag){
					msg = messagePool.read();
					state_d = MESSAGE;
				}else if(display_event == shotByFlag){
					enemyWeaponName = enemyWeaponNamePool.read();
					enemy_player_id = enemyPlayerIdPool.read();
					state_d = SHOT;
				}
				else if(display_event == choiceFlag){
					//hwlib::cout << "choiceflag\n";
					screen = choicePool.read();
					state_d = CHOICE;
				}
				break;
			}
			case SHOW:{
				display << "\f"
						<< "\t0000" << "HP: " << health
						<< "\t1100" << time.getMin() << ":" << time.getSec()
						<< "\t0006" << weaponName
						<< "\t0007" << "Ammo: " << ammo
						<< '/' << ammoStr
						<< hwlib::flush;
				state_d = IDLE;
				break;
			}
			case SHOT:{
				display << "\f"
						<< "\t0000" << "HP: " << health
						<< "\t1100" << time.getMin() << ":" << time.getSec()
						<< "\t0002" << "Shot by: " << enemy_player_id
						<< "\t0003" << "\\w: " << enemyWeaponName
						<< "\t0006" << weaponName
						<< "\t0007" << "Ammo: " << ammo
						<< hwlib::flush;
				//wait(shotByClock);
				hwlib::wait_ms(2000); // Show the shot by message for 2 seconds
				state_d = SHOW;
				break;
			}
			case MESSAGE:{
				display << "\f"
						<< "\t0203" << msg
						<< hwlib::flush;
				wait(idleFlag);
				state_d = IDLE;
				break;
			}
			case CHOICE:{
				if(screen == 0){
					display << "\f"
						<< "\t0000" << "Choose ID: "
						<< "\t0002" << "[PID]> "
						<< hwlib::flush;
					wait(numberFlag);
					display << "\t0702" << numberPool.read() << hwlib::flush; // display first number
					wait(numberFlag);
					display << "\t0802" << numberPool.read() << hwlib::flush; // display second number
					
				}else if (screen == 1){
					display << "\f"
						<< "\t0000" << "Choose a weapon:"
						<< "\t0002" << "[W]> "
						<< hwlib::flush;
					wait(numberFlag);
					display << "\t0502" << numberPool.read() << hwlib::flush;
					
				}else if (screen == 2){
					display << "\f"
					<< "\t0400" << "  MENU:"
					<< "\t0002" << "[A]: Player ID"
					<< "\t0004" << "[B]: Weapon ID"
					<< "\t0006" << "[#]: Done"
					<< hwlib::flush;
				}
				state_d = IDLE;
				//display << hwlib::flush;
				break;
			}
				
		}
	}
}
void displayTask::showGameTime(const Time & t){
	timeLeftPool.write(t);
	timeLeftFlag.set();
}
void displayTask::showAmmo(const uint16_t & ammo){
	ammoPool.write(ammo);
	ammoFlag.set();
}
void displayTask::showWeapon(hwlib::string<40> weapon){
	weaponNamePool.write(weapon);
	showWeaponFlag.set();
}
void displayTask::showHealth(const uint16_t & hp){
	healthPool.write(hp);
	healthFlag.set();
}
void displayTask::showString(hwlib::string<40> msg){
	messagePool.write(msg);
	messageFlag.set();
}
void displayTask::returnIdle(void){
	idleFlag.set();
}
void displayTask::shotBy(const uint16_t & player_id, hwlib::string<40> w_name){
	enemyWeaponNamePool.write(w_name);
	enemyPlayerIdPool.write(player_id);
	shotByFlag.set();
}

/* make a display menu, show weapon or player ID choice. */
/* set the bool true for weapon or false for player ID   */
void displayTask::showChoice(const int & screen){
	choicePool.write(screen);
	choiceFlag.set();
}

void displayTask::setNumber(const char & number){
	numberPool.write(number);
	numberFlag.set();
}
