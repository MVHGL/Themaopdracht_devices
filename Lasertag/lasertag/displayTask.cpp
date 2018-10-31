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
	gameOverFlag(this, "Game over flag"),
	enemyWeaponNamePool("Enemy weapon pool"),
	playerIdPool("Player ID pool"),
	shotByFlag(this, "Shot by flag"),
	shotByClock(this, 5'000'000, "Shot by timeout clock")
	
{}

void displayTask::main(){
	while(true){
		switch(state_d){
			case IDLE:{
				auto display_event = wait(timeLeftFlag + ammoFlag + showWeaponFlag + healthFlag + gameOverFlag + shotByFlag);
				if(display_event == timeLeftFlag){
					time = timeLeftPool.read();
					state_d = SHOW;
				}else if(display_event == ammoFlag){
					ammo = ammoPool.read();
					state_d = SHOW;
				}else if(display_event == showWeaponFlag){
					weaponName = weaponNamePool.read();
					state_d = SHOW;
				}else if(display_event == healthFlag){
					health = healthPool.read();
					state_d = SHOW;
				}else if(display_event == gameOverFlag){
					state_d = GAME_OVER;
				}else if(display_event == shotByFlag){
					enemyWeaponName = enemyWeaponNamePool.read();
					player_id = playerIdPool.read();
					state_d = SHOT;
				}
				break;
			}
			case SHOW:{
				display << "\f"
						<< "\t0000" << "HP: " << health
						<< "\t1100" << time.getMin() << ":" << time.getSec()
						<< "\t0006" << weaponName
						<< "\t0007" << "Ammo: " << ammo
						<< hwlib::flush;
				state_d = IDLE;
				break;
			}
			case SHOT:{
				display << "\f"
						<< "\t0000" << "HP: " << health
						<< "\t1100" << time.getMin() << ":" << time.getSec()
						<< "\t0002" << "Shot by: " << player_id
						<< "\t0003" << "\\w: " << enemyWeaponName
						<< "\t0006" << weaponName
						<< "\t0007" << "Ammo: " << ammo
						<< hwlib::flush;
				wait(shotByClock);
				state_d = SHOW;
				break;
			}
			case GAME_OVER:{
				display << "\f"
						<< "\t0303" << "GAME OVER!"
						<< hwlib::flush;
				state_d = IDLE;
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
void displayTask::gameOver(void){
	gameOverFlag.set();
}
void displayTask::shotBy(const uint16_t & player_id, hwlib::string<40> w_name){
	enemyWeaponNamePool.write(w_name);
	playerIdPool.write(player_id);
	shotByFlag.set();
}