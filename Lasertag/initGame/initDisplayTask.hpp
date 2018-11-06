#ifndef _INITDISPLAYTASK_HPP
#define _INITDISPLAYTASK_HPP

#include "rtos.hpp"
#include "hwlib.hpp"

class initDisplayTask : public rtos::task<> {
private:
	rtos::flag timeFlag;
	rtos::pool<int> timePool;
	rtos::flag commandFlag;
	rtos::pool<char> commandPool;
	rtos::flag stateFlag;
	rtos::pool<int> statePool;
	int time = 0;
	int state = 1;
	char c = ' ';
	hwlib::window_ostream &oled_display;
	enum state_t {IDLE, DISPLAY};
	state_t state_display = IDLE;
	
public:
	initDisplayTask(hwlib::window_ostream & oled_display);
	
	void main();
	void showTime(const int &t);
	void showCommand(const char &c);
	void showState(const int & s);

};

#endif // DISPLAYTASK_HPP
