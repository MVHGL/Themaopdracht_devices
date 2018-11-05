#ifndef _DISPLAYTASK_HPP
#define _DISPLAYTASK_HPP
#include "hwlib.hpp"
#include "rtos.hpp"
#include "time.hpp"
class displayTask : public rtos::task<>
{
private:
	hwlib::window_ostream & display;
	rtos::pool<Time> timeLeftPool;
	rtos::flag timeLeftFlag;
	rtos::pool<uint16_t> ammoPool;
	rtos::flag ammoFlag;
	rtos::pool<hwlib::string<40>> weaponNamePool;
	rtos::flag showWeaponFlag;
	rtos::pool<uint16_t> healthPool;
	rtos::flag healthFlag;
	rtos::flag messageFlag;
	rtos::pool<hwlib::string<40>> messagePool;
	rtos::pool<hwlib::string<40>> enemyWeaponNamePool;
	rtos::pool<uint16_t> enemyPlayerIdPool;
	rtos::flag shotByFlag;
	rtos::clock shotByClock;
	rtos::pool<int> choicePool;
	rtos::flag choiceFlag;
	rtos::pool<uint16_t> playerIdPool;
	rtos::flag idleFlag;
	rtos::pool<char> numberPool;
	rtos::flag numberFlag;
	enum display_state {IDLE, SHOW, SHOT, MESSAGE, CHOICE};
	display_state state_d = IDLE;
	// Variables
	uint16_t ammo = 0;
	uint16_t ammoStr = ammo;
	uint16_t health = 0;
	uint16_t enemy_player_id = 0;
	uint16_t player_id[2];
	uint16_t weapon_id[1];
	int screen; // which menu screen to show at beginning of game
	Time time;
	hwlib::string<40> enemyWeaponName, weaponName, msg;
public:
	displayTask(hwlib::window_ostream & display);
	void main() override;
	void showGameTime(const Time & t);
	void showAmmo(const uint16_t & ammo);
	void showWeapon(hwlib::string<40> weapon);
	void showHealth(const uint16_t & hp);
	void showString(hwlib::string<40> msg);
	void returnIdle(void);
	void shotBy(const uint16_t & player_id, hwlib::string<40> w_name);
	void showChoice(const int & screen);
	void setNumber(const char & number);
};
#endif
