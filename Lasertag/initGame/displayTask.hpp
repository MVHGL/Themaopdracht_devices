#ifndef _DISPLAYTASK_HPP
#define _DISPLAYTASK_HPP

#include "rtos.hpp"

class displayTask : public rtos::task<> {
private:
	rtos::flag stateFlag;
	rtos::pool<int> statePool;
	rtos::channel<char, 5> displayChannel;
	int state = 0;
	enum state_t {IDLE, DISPLAY};
	state_t state_display = IDLE;
	
public:
	displayTask(hwlib::window_ostream &display);
	void main();
	void showState(const int state);
	void setState(const int state);
	void show(char c);

};

#endif // DISPLAYTASK_HPP
