/// @file gameTimeControl.hpp
#ifndef _GAMETIMECONTROL_HPP
#define _GAMETIMECONTROL_HPP

#include <functional>
#include "time.hpp"
#include "rtos.hpp"
#include "displayTask.hpp"

/// \brief
/// gameTimeControl class
/// \details
/// Class for controlling the main game, which implements the rtos::task<> class.
class gameTimeControl : public rtos::task<> {
private:
	Time time;
	rtos::clock clock;
	rtos::flag timeStart;
	displayTask& display;
	enum state_t { IDLE, KEEP_TIME };
	state_t state = IDLE;
	
	void checkTime();
public:
	/// \brief
	/// gameTimeControl constructor
	/// \details
	/// This is the constructor for the gameTimeControl task, which requires a reference to a display.
	gameTimeControl(displayTask& display);
	/// \brief
	/// Sets the time.
	/// \details
	/// Sets the time according to its parameter passed.
	void setTime(const Time& time);
	/// \brief
	/// Checks if game time is over.
	/// \details
	/// This method checks if the game time is over. True if it is over, false otherwise.
	bool isGameTimeOver();
	/// \brief
	/// Starts game timer
	/// \details
	/// Starts the game timer according to the time which should have been set earlier.
	void startGameTimer();
	/// \brief
	/// Main implementation
	/// \details
	/// This method overrides the rtos::task<> virtual function.
	void main() override;
};
#endif
