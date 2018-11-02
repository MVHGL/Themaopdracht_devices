#include "initGame.hpp"

initGame::initGame(displayTask& displayControl, ir_transmitter & transmitterControl):
	task("initGameTask"),
	keypadChannel(this, "keyPadChannel"),
	displayControl(displayControl),
	initTimer(this, "initTimer"),
	transmitterControl(transmitterControl)
	{}

void initGame::buttonPressed(const char c){
	keypadChannel.write(c);
};


void initGame::main() {
	//enum voor de states. 
	enum state_t {IDLE, ADJUST_TIME, BUTTON_PRESSED_TWO, SEND_IR_TIME, START_GAME};
	state_t state = IDLE;
	//integers voor de tijd. 
	int min_tientallen=0;
	int min=0;
	int time=0; 
	
	//de loop
	while(1){
		switch(state){
		case IDLE:									//IDLE state  (program starts here
			wait(keypadChannel); 
			if (keypadChannel.read()=='C'){				//Wait for a C character. 
				state= ADJUST_TIME; 
				break; 
			}
		case ADJUST_TIME: 								// Waits for time from keypad input.  
		{
			initTimer.set(20);
			auto event = wait(initTimer + keypadChannel);
			if (event == keypadChannel){
			min_tientallen= int(keypadChannel.read()-48);			// Char to int minus the assci value gives a number between 0 and 9 
				if (min_tientallen >=0 && min_tientallen <10)		//Checks for right input
				{
					min_tientallen *=10;							//Makes the first input 10 times bigger because the first given nummer represenst time per 10 minuts
					state = BUTTON_PRESSED_TWO; 
					break;
				}
			}
			else if (event== initTimer){ 						// When the timer and the input is timedout and program returns to IDLE
				state=IDLE;
				break;
			}
		}
		case BUTTON_PRESSED_TWO: // This state waits for the second time input in minutes 
		{
 								
			auto event = wait(initTimer + keypadChannel);
			if(event == keypadChannel){							//checks for write input
				min = int(keypadChannel.read() - 48); 				// Char to int minus the assci value gives a number between 0 and 9 
				if (min >= 0 && min <10)
				{
					time= min_tientallen + min ; 				//adds the two given time variabeles togheter 
					state= SEND_IR_TIME;
					break; 
				}
			}
			else if (event == initTimer) 							// When the timer and the input is timedout and program returns to IDLE
			{
				state=IDLE;
				break;
			} 
		}
		case SEND_IR_TIME:										//Sends the time to players when # pressed
		{
			if (keypadChannel.read()=='#')
			{
				transmitterControl.send(0,time);
			}
			else if (keypadChannel.read()=='*')						//If * is pressed go to startgame state
			{
				state= START_GAME; 
				break; 
			}
		}
			
		case START_GAME:									//State to start the game
		{
			transmitterControl.send(0,0); 
			if(keypadChannel.read()=='D')					// With D pressed go back to IDLE
			{
				state=IDLE; 
				break; 
			}
			else if(keypadChannel.read()=='*')				// if * is pressed the start message will be send again. 
			{
				break; 
			}
		}
		}
	}
}
