#ifndef _INITGAME_HPP
#define _INITGAME_HPP

#include "displayTask.hpp"
#include "rtos.hpp"
#include "../lasertag/ir_transmitter.hpp"

class initGame : public rtos::task<> {
private:
	rtos::channel<char, 5> keypadChannel;
	rtos::timer initTimer;
	displayTask& display;

public:
	initGame(displayTask& display);
	void buttonPressed(hwlib::istream & keypad);
	
}


#endif