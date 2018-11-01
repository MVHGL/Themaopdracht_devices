#include "initGame.hpp"

initGame::initGame(displayTask& display){
	task("initGameTask");
}

void initGame::buttonPressed(hwlib::istream & keypad){
	keypadChannel.write(keypad.getc())
}


initGame::main() override{
	enum state_t= {IDLE, ADJUST_TTIME, BUTTON_PRESSED, SEND_IR_TIME, START_GAME};
	state= state_t; 
	state=IDLE;
	int min_tientallen=0;
	int min=0;
	int time=0; 
	while(1){
		switch(state){
		case IDLE: 
			wait(keypadChannel); 
			if (keypadChannel.read()=='C'){
				state= ADJUST_TIME; 
				break; 
			}
			
		case ADJUST_TIME: 
			initTimer.set(20);
			auto event = wait(initTimer+keypadChannel);
			if (event == keypadChannel){
			min_tientallen= int(keypadChannel.read()-48);
				if (min_tientallen >=0 && min_tientallen <10)
				{
					min_tientallen *=10;
					state= BUTTON_PRESSED_TWO; 
					break
				}
			}
			else if (event== initTimer) 
			{
				state=IDLE;
				break;
			}
			
		case BUTTON_PRESSED_TWO: 
			auto event = wait(initTimer+keypadChannel);
			min = int(keypadChannel.read()-48); 
			if(event==keypadChannel){
				if (min >= 0 && min <10)
				{
					time= min_tientallen + min ; 
					state= SEND_IR_TIME;
					break; 
				}
			}
			else if (event== initTimer) 
			{
				state=IDLE;
				break;
			} 
			
		case SEND_IR_TIME:
			if (keypadChannel.read()=='#')
			{
				transmitter.send(0,time);
			}
			else if (keypadChannel.read()=='*')
			{
				state= START_GAME; 
				break; 
			}
			
		case START_GAME:
			transmitter.send(0,0); 
			if(keypadChannel.read()=='D')
			{
				state=IDLE; 
				break; 
			}
			else if(keypadChannel.read()=='*')
			{
				break; 
			}
		}
	}
}
