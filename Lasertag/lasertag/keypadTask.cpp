#include "keypadTask.hpp"

keypadTask::keypadTask(registerGameControl & registerGame):
	task("KeypadTask"),
	registerGame(registerGame)
	{}


void keypadTask::main(){
	while(1){
		switch(state){
			case IDLE:
			{
				c = keypad.getc();	//poll keypad for keypress.
				hwlib::cout << "button pressed: " << c << " \n";
				state = BUTTON_PRESSED;
				break;
			}
			case BUTTON_PRESSED:
			{
				registerGame.buttonPressed(c); //write to channel & to display.
				state = IDLE;
				break;
			}
		}
	}
};