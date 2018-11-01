#ifndef _INITGAME_HPP
#define _INITGAME_HPP
#include "rtos.hpp"
#include "ir_transmitter.hpp"

class initGame : public rtos::task<> {
private:
	rtos::channel<char, 5> keypadChannel;
	displayTask& display
public:
	initGame(displayTask& display);
	void buttonPressed(hwlib::istream & keypad);
	
}


#endif