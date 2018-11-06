/// @file registerGameControl.hpp
#ifndef _REGISTER_GAME_HPP
#define _REGISTER_GAME
#include "mainGameControlTask.hpp"
#include "displayTask.hpp"

/// \brief
/// registerGameControl class.
/// \details
/// registerGameControl class, used to register game params. It implements the rtos::task<>.
class registerGameControl : public rtos::task<> {
private:
	mainGameControlTask & mainGame;
	displayTask & display;
	rtos::channel<char, 10> keypadChannel;
	enum state_t {IDLE, GET_PLAYER_ID, GET_WEAPON};
public:
	/// \brief
	/// registerGameControl constructor.
	/// \details
	/// registerGameControl constructor, it requires a reference to a mainGameControlTask and a displayTask.
	registerGameControl(mainGameControlTask & mainGame, displayTask & display);
	/// \brief
	/// buttonPressed method.
	/// \details
	/// This method is called when a key is pressed. c will be written into registerGameControl's channel.
	void buttonPressed(const char & c);
	/// \brief
	/// Main implementation.
	/// \details
	/// This method implements the main method inherited from rtos::task<>.
	void main();
};
#endif
