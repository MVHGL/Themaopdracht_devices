#ifndef _REGISTER_GAME_HPP
#define _REGISTER_GAME
#include "mainGameControlTask.hpp"
#include "displayTask.hpp"

class registerGameControl : public rtos::task<> {
private:
	mainGameControlTask & mainGame;
	displayTask & display;
	rtos::channel<char, 10> keypadChannel;
	enum state_t {IDLE, GET_PLAYER_ID, GET_WEAPON};
public:
	registerGameControl(mainGameControlTask & mainGame, displayTask & display);
	void buttonPressed(const char & c);
	void main();
};
#endif
