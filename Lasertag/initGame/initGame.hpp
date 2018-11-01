#ifndef _INITGAME_HPP
#define _INITGAME_HPP
#include "rtos.hpp"

class initGame : public rtos::task<> {
	rtos::channel<char, 5> keyPresses;
	
}

#endif