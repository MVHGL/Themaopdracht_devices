/// @file DisplayTask.hpp
#ifndef _DISPLAYTASK_HPP
#define _DISPLAYTASK_HPP
#include "hwlib.hpp"
#include "rtos.hpp"
#include "time.hpp"

/// \brief
/// Display control
/// \details
/// This class implements the rtos::task<> class and controls a 128x64 OLED display.
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
	/// \brief
	/// displayTask constructor
	/// \details
	/// This constructor requires a reference to a hwlib::window_ostream object.
	displayTask(hwlib::window_ostream & display);
	/// \brief
	/// displayTask's main method
	/// \details
	/// This method implements the rtos::task<> method.
	void main() override;
	/// \brief
	/// Shows the current game time
	/// \details
	/// This method shows the current game time according to its parameters passed.
	void showGameTime(const Time & t);
	/// \brief
	/// Shows the current ammunition
	/// \details
	/// Shows the current ammunition according to its parameters passed.
	void showAmmo(const uint16_t & ammo);
	/// \brief
	/// Shows the current weapon
	/// \details
	/// Shows the current weapon according to the parameters hwlib::string<40> passed.
	void showWeapon(hwlib::string<40> weapon);
	/// \brief
	/// Shows current health
	/// \details
	/// This method shows the current health according to its parameters passed.
	void showHealth(const uint16_t & hp);
	/// \brief
	/// Shows a message
	/// \details
	/// This method shows a string on the screen according to its parameters passed.
	void showString(hwlib::string<40> msg);
	/// \brief
	/// Returns to idle state
	/// \details
	/// This function is used to return to the idle state. Use this method in combination with showString.
	void returnIdle(void);
	/// \brief
	/// Shows who shot you
	/// \details
	/// This method shows who you were shot by, according to its parameters passed.
	void shotBy(const uint16_t & player_id, hwlib::string<40> w_name);
	/// \brief
	/// Shows a choice menu
	/// \details
	/// Shows a choice menu according to which screen number is passed by.
	void showChoice(const int & screen);
	/// \brief
	/// Sets a number on the screen
	/// \details
	/// This method will show a number on the scree according to its parameters passed by.
	void setNumber(const char & number);
};
#endif
