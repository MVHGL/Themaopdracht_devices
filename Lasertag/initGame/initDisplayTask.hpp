/// @file initDisplayTask.hpp
#ifndef _INITDISPLAYTASK_HPP
#define _INITDISPLAYTASK_HPP

#include "rtos.hpp"
#include "hwlib.hpp"

/// \brief
/// InitDisplaytask class
/// \details
/// The class implements the rtos::task<> class and controls a 128x64 OLED Display. 
class initDisplayTask : public rtos::task<> {
private:
	rtos::flag timeFlag;
	rtos::pool<int> timePool;
	rtos::flag commandFlag;
	rtos::pool<char> commandPool;
	rtos::flag stateFlag;
	rtos::pool<int> statePool;
	int time = 0;
	int state = 1;
	char c = ' ';
	hwlib::window_ostream &oled_display;
	enum state_t {IDLE, DISPLAY};
	state_t state_display = IDLE;
	
public:
	/// \brief
	/// The constructor for the initDisplayTask 
	/// \details
	/// This constructor needs a refrence to hwlib::window_ostream object. 
	initDisplayTask(hwlib::window_ostream & oled_display);
	/// \brief
	/// initDisplayTask's main method. 
	/// \details
	/// This method implements the rtos::task<> method. 
	void main();
	/// \brief
	/// Method to update time.
	/// \detials
	/// method to update the time on the display. 
	void showTime(const int &t);
	/// \brief 
	/// Function to write a character in pool
	/// \details
	/// A function to write a character in the initDisplayTasks pool.
	void showCommand(const char &c);
	/// \brief
	/// Change display state.
	/// \details
	/// Change the state of what the display is showing. 
	void showState(const int & s);

};

#endif // DISPLAYTASK_HPP
