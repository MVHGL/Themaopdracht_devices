#pragma once
#include "rtos.hpp"

class mainGameControlTask : public rtos::task<> {
	rtos::channel<int, 10> messages;
public:
	mainGameControlTask();
	void IRMessageReceived(const uint16_t& playerID, const uint16_t& data);

};

