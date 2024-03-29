#include "initDisplayTask.hpp"

initDisplayTask::initDisplayTask(hwlib::window_ostream & oled_display):
	task("displayTask"),
	timeFlag(this, "timeFlag"),
	timePool("timePool"),
	commandFlag(this, "commandFlag"),
	commandPool("commandPool"),
	stateFlag(this, "stateFlag"),
	statePool("statePool"),
	oled_display(oled_display)
	{}

void initDisplayTask::main(){
	oled_display << '\f' << hwlib::flush;
	while(true){
		switch(state_display){
			case IDLE:
			{
				auto event = wait(timeFlag + commandFlag + stateFlag);
				if(event == timeFlag){
					time = timePool.read();
					state_display = DISPLAY;
					break;
				}
				if(event == commandFlag){
					c = commandPool.read();
					state_display = DISPLAY;
					break; 
				}
				if(event == stateFlag){
					state = statePool.read();
					state_display = DISPLAY;
					break;
				}
			}

			case DISPLAY:
			{
				if(state == 1){
					oled_display 
					<<"\f" << "\t0000" << "Game Time: .."
					<< "\t0003" << "[C] to set play"
					<< "\t0005" << "time." <<
					hwlib::flush;
					state_display = IDLE;
					break;
				}
				if(state == 2){
					oled_display 
					<<"\f" << "\t0000" << "Game Time: " << time
					/*<< "\t0002" << "command: "<< c*/ 
					<< "\t0004" << "[#]to send Time"
					<< "\t0005" << "[*]to start game "
					<< "\t0006" << "[D] exit" 
					<<
					hwlib::flush;
					state_display = IDLE;
					break;
				}
				if(state == 3){
					oled_display 
					<<"\f" << "\t0000" << "Game Time: " << time
					<< "\t0003" <<"[*] start the"
					<<"\t0004" <<"game"
					<< "\t0006" << "[D] exit" <<
					hwlib::flush;
					state_display = IDLE;
					break;
				}
				if(state==4)  // Menu for setting the first digit of time
				{
					oled_display 
					<<"\f" << "\t0000" << "Game Time: " <<time
					<< "\t0003" << "Give first time"
					<< "\t0004" << "digit (0-2)."
					<< "\t0007" << "[D] exit"<<
					hwlib::flush;
					state_display = IDLE;
					break;
				}
				if (state==5) // Menu for second time digit
				{
					oled_display 
					<<"\f" << "\t0000" << "Game Time: " << time
					/*<< "\t0002" << "command: "<< c */
					<< "\t0003" << "Give second time"
					<< "\t0004" << "digit (0-9)." 
					<< "\t0006" << "[#] to send" 
					<< "\t0007" << "[D] exit"<<
					hwlib::flush;
					state_display = IDLE;
					break;
				}
				if (state==6){
					oled_display 
					<<"\f" << "\t0000" << "Game Time:.."
					/*<< "\t0002" << "command: "<< c */
					<< "\t0003" << "Wrong input!!"
					<<
					hwlib::flush;
					hwlib::wait_ms(2000);
					state_display = IDLE;
					break;
				}
				if (state==7)
				{
					oled_display 
					<<"\f" << "\t0000" << "Game Time: " //<< time
					<< "\t0003" << "Timed Out"
					<<
					hwlib::flush;
					hwlib::wait_ms(2000);
					state_display = IDLE;
					break;
				}
				else{
					state_display=IDLE;
					break;
				}
				}
			}
		}
}

void initDisplayTask::showTime(const int & t){
	timePool.write(t);
	timeFlag.set();
};

void initDisplayTask::showCommand(const char & c){
	commandPool.write(c);
	commandFlag.set();
};

void initDisplayTask::showState(const int & s){
	statePool.write(s);
	stateFlag.set();
}