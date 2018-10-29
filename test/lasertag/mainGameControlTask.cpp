#include "mainGameControlTask.hpp"

mainGameControlTask::mainGameControlTask()
{
}

void mainGameControlTask::IRMessageReceived(const uint16_t& playerID, const uint16_t& data) {
	messages.write(playerID);
	messages.write(data);
}
