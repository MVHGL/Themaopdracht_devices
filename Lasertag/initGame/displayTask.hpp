#ifndef DISPLAYTASK_HPP
#define DISPLAYTASK_HPP
#include "rtos.hpp"

class displayTask : public rtos::task<> {
private:
	rtos::flag stateFlag;
	rtos::pool<int> statePool;
	rtos::channel<char, 5> displayChannel;
public:
	displayTask();
	void main();

};

#endif // DISPLAYTASK_HPP
