#ifndef _DISPLAYTASK_HPP
#define _DISPLAYTASK_HPP

#include "rtos.hpp"
#include "hwlib.hpp"

class displayTask : public rtos::task<> {
private:
	rtos::flag stateFlag;
	rtos::pool<int> statePool;
	rtos::channel<char, 5> displayChannel;
	hwlib::window_ostream &oled_display;
	int state = 0;
	enum state_t {IDLE, DISPLAY};
	state_t state_display = IDLE;
	
public:
	displayTask(hwlib::window_ostream &oled_display);
	void main();
	void showState(const int state);
	void setState(const int state);
	void show(char c);

};

#endif // DISPLAYTASK_HPP
