/// @file initGame.hpp
#ifndef _INITGAME_HPP
#define _INITGAME_HPP

#include "initDisplayTask.hpp"
#include "rtos.hpp"
#include "../lasertag/ir_transmitter.hpp"

/// \brief
/// Init Game 
/// \details
/// This class implements the rtos::task<> class.
/// With this class you can send the game time to players and send the start message. 
class initGame : public rtos::task<> {
private:
	rtos::channel<char, 5> keypadChannel;
	initDisplayTask & displayControl;
	rtos::timer initTimer;
	ir_transmitter & transmitterControl;
	char temp;
	int s = 1;
	int minute_tens = 0;
	int min = 0;
	int time = 0; 
	char keyButtonOne,keyButtonTwo;
	hwlib::target::pin_out buzzer =hwlib::target::pins::d6 ;

public:
	/// \brief
	/// Init game constructor. 
	/// \details
	/// The constructor requires a refrence to initDisplayTask and ir_transmitter. 
	initGame(initDisplayTask& displayControl, ir_transmitter & transmitterControl);
	/// \brief
	/// buttonPressed 
	///	\details
	/// This function update the pools and flags on every keypress of the keypad. 
	void buttonPressed(const char c);
	/// \brief
	/// initGame's main method.
	/// \details
	/// This method let you send play time to players and start the game with keypresses. 
	void main();
	
};

#endif