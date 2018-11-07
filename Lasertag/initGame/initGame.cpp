#include "initGame.hpp"

initGame::initGame(initDisplayTask& displayControl, ir_transmitter & transmitterControl):
	task("initGameTask"),
	keypadChannel(this, "keyPadChannel"),
	displayControl(displayControl),
	initTimer(this, "initTimer"),
	transmitterControl(transmitterControl)
	{}

void initGame::buttonPressed(const char c){
	displayControl.showTime(time);
	displayControl.showCommand(c);
	beep(20);
	keypadChannel.write(c);
};
void initGame::beep(const int & msecond){ 
	buzzer.set(1);
	hwlib::wait_ms(msecond);
	buzzer.set(0); 
};
void initGame::main() {
	const bool debug=0;
	//enum voor de states. 
	enum state_t {IDLE, ADJUST_TIME, BUTTON_PRESSED_TWO, SEND_IR_TIME, START_GAME};
	state_t state = IDLE;
	buttonPressed(' ');
	
	//de loop
	while(1){
		switch(state){
		case IDLE:														//IDLE state  (program starts here
		{
			displayControl.showState(1);
			wait(keypadChannel);
			temp = keypadChannel.read();
			if (temp == 'C'){											//Wait for a C character. 
				state= ADJUST_TIME;				
				break; 
			}
			break; 
		}
		case ADJUST_TIME: 												// Waits for time from keypad input.  
		{
			displayControl.showTime(0); 
			if(debug){hwlib::cout << "state: adjust_time " << '\n';}
			displayControl.showState(4);
			auto event = wait(initTimer + keypadChannel);
			if (event == keypadChannel){
				keyButtonOne=keypadChannel.read(); 
				minute_tens = int(keyButtonOne - 48);			// Char to int minus the assci value gives a number between 0 and 9 
				if (keyButtonOne=='D')
				{
					state= IDLE; 
					break; 
				}
				if (debug)hwlib::cout << "min_tiental: " << minute_tens << '\n';
				if (minute_tens >= 0 && minute_tens < 3)			//Checks for right input
				{
					time= (minute_tens * 10);								//Makes the first input 10 times bigger because the first given nummer represents time per 10 minuts
					if (debug)hwlib::cout << "minute_tens: " << minute_tens << '\n';
					displayControl.showTime(time); 
					displayControl.showState(5);
					state = BUTTON_PRESSED_TWO; 
					break;
					
				}
				else{
					if (debug)hwlib::cout << "Input a number.\n";
					displayControl.showState(6);
					minute_tens=0;
					time=0;
					min=0;
					displayControl.showState(6);
					state = ADJUST_TIME;
					break;
				}
			}
		}
		case BUTTON_PRESSED_TWO: 									// This state waits for the second time input in minutes 
		{
			displayControl.showState(5);
 			if(debug)hwlib::cout << "state: Button_pressed_two \n";					
			auto event = wait(initTimer + keypadChannel);
			if(event == keypadChannel){								//checks for write input
				keyButtonTwo =keypadChannel.read();
				min = int(keyButtonTwo - 48); 				// Char to int minus the assci value gives a number between 0 and 9 
				if (keyButtonTwo=='D')
				{
					state= IDLE; 
					break;
				}
				if (keyButtonTwo=='#')
				{
					beep(100);
					transmitterControl.send(0,time);
					state=SEND_IR_TIME;
					
					break; 
				}
				if (min >= 0 && min <10)
				{
					time  += min; 					//adds the two given time variabeles togheter 					
					if(debug)hwlib::cout <<"time: " << time << '\n';
					displayControl.showTime(time);
					
					state= SEND_IR_TIME;
					break; 
				}
				else
				{
					if(debug)hwlib::cout << "Time to big(over 31), returning to BUTTON_PRESSED_TWO.\n";
					displayControl.showState(6);
					min=0;
					break;
				}
			} 
		}
		case SEND_IR_TIME:										//Sends the time to players when # pressed
			{
				
				displayControl.showState(2);
				if(debug)hwlib::cout << "state = SEND_IR_TIME\n";
				wait(keypadChannel);
				auto given= (keypadChannel.read());
				if (given=='#')
				{
					beep(100); 
					if(debug)hwlib::cout << "sending time.\n" <<time;
					transmitterControl.send(0,time);
					break;
				}
				else if (given=='*')						//If * is pressed go to startgame state
				{
					beep(250);
					transmitterControl.send(0,31); 
					if(debug)hwlib::cout << "state = start_game.\n";
					state= START_GAME; 					
					break; 
				}
				else if(given=='D')
				{
					if(debug)hwlib::cout << "returning to IDLE";
					state = IDLE;					
					break;
				}
				else{
					displayControl.showState(6);
					break;
				}
			}
			
		case START_GAME:									//State to start the game
			{
				displayControl.showState(3);
				if(debug)hwlib::cout << "state = START_GAME\n";
				wait(keypadChannel);
				auto in = (keypadChannel.read()); 
				if(in=='*')				// if * is pressed the start message will be send again. 
				{
					beep(250);
					if (debug)hwlib::cout << "sending start_message...\n";
					transmitterControl.send(0,31);
					break;
				}
				else if(in=='D')					// With D pressed go back to IDLE
				{
					if(debug)hwlib::cout << "D pressed. returning to IDLE.\n";
					displayControl.showTime(0); 
					state=IDLE; 
					break; 
				}
				
				else{
					displayControl.showState(6);
					break;
				}
			}
		}
	}
}
