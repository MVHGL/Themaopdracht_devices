#ifndef _REGISTER_GAME_HPP
#define _REGISTER_GAME
#include "mainGameControlTask.hpp"

class registerGameControl : public rtos::task<> {
private:
	mainGameControlTask & mainGame;
	rtos::timer registerTimer;
	rtos::channel<char, 10> keypadChannel;
	displayTask & display;
	enum state_t {IDLE, GET_PLAYER_ID, GET_WEAPON};
public:
	registerGameControl(mainGameControlTask & mainGame);
	void buttonPressed(hwlib::istream & keypad);
	void main();
};
#endif
