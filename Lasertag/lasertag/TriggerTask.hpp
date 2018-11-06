/// @file TriggerTask.hpp
#ifndef _TRIGGERTASK_HPP
#define _TRIGGERTASK_HPP
#include "rtos.hpp"
#include "hwlib.hpp"
#include "mainGameControlTask.hpp"

/// \brief
/// TriggerTask class
/// \details
/// This task will check for buttun (trigger) presses.
class TriggerTask : public rtos::task<> {
private:
	hwlib::pin_in& trigger;
	mainGameControlTask& mainGame;
	rtos::clock clock;
public:
	/// \brief
	/// TriggerTask constructor.
	/// \details
	/// This constructor requires a reference to a trigger (hwlib::pin_in) and a mainGameControlTask.
	TriggerTask(hwlib::pin_in& trigger, mainGameControlTask& mainGame);
	/// \brief
	/// Main implementation.
	/// \details
	/// This method implements the main method inherited from rtos::task<>.
	void main() override;
};
#endif
