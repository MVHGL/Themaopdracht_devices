#ifndef DISPLAYTASK_HPP
#define DISPLAYTASK_HPP
#include "rtos.hpp"

class displayTask : public rtos::task<> {
private:
	rtos::flag stateFlag;
	rtos::pool<int> statePool;
	rtos::channel<char, 5> displayChannel;
	int state = 0;
public:
	displayTask();
	void main();
	void showState(const int state);
	void setState(const int state);

};

#endif // DISPLAYTASK_HPP
