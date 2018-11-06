#include "initKeypadTask.hpp"

initKeypadTask::initKeypadTask(initGame & initGameTask):
	task("KeypadTask"),
	initGameTask(initGameTask)
	{}


void initKeypadTask::main(){
	while(1){
		switch(state){
			case IDLE:
			{
				c = keypad.getc();	//poll keypad for keypress.
				//hwlib::cout << "button pressed: " << c << " \n";
				state = BUTTON_PRESSED;
				break;
			}
			case BUTTON_PRESSED:
			{
				initGameTask.buttonPressed(c); //write to channel & to display.
				state = IDLE;
				break;
			}
		}
	}
};