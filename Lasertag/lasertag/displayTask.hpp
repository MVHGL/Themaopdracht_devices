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
	rtos::flag gameOverFlag;
	rtos::pool<hwlib::string<40>> enemyWeaponNamePool;
	rtos::pool<uint16_t> enemyPlayerIdPool;
	rtos::flag shotByFlag;
	rtos::clock shotByClock;
	rtos::pool<bool> choicePool;
	rtos::flag choiceFlag;
	rtos::pool<uint16_t> playerIdPool;
	rtos::flag startNewGameFlag;
	enum display_state {IDLE, SHOW, SHOT, GAME_OVER, CHOICE};
	display_state state_d = IDLE;
	// Variables
	uint16_t ammo = 0;
	uint16_t ammoStr = ammo;
	uint16_t health = 0;
	uint16_t enemy_player_id = 0;
	uint16_t player_id[2];
	uint16_t weapon_id[1];
	bool weapon_or_player;
	Time time;
	hwlib::string<40> enemyWeaponName, weaponName;
public:
	displayTask(hwlib::window_ostream & display);
	void main() override;
	void showGameTime(const Time & t);
	void showAmmo(const uint16_t & ammo);
	void showWeapon(hwlib::string<40> weapon);
	void showHealth(const uint16_t & hp);
	void gameOver(void);
	void shotBy(const uint16_t & player_id, hwlib::string<40> w_name);
	void showChoice(const bool & weapon_or_player);
};
#endif
