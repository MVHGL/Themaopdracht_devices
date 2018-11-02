#ifndef _INITGAME_HPP
#define _INITGAME_HPP

#include "displayTask.hpp"
#include "rtos.hpp"
#include "../lasertag/ir_transmitter.hpp"

class initGame : public rtos::task<> {
private:
	rtos::channel<char, 5> keypadChannel;
	displayTask & displayControl;
	rtos::timer initTimer;
	ir_transmitter & transmitterControl;
	
public:
	initGame(displayTask& displayControl, ir_transmitter & transmitterControl);
	void buttonPressed(const char c);
	void main();
	
};

#endif