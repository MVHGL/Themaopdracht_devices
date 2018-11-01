#include "ir_transmitter.hpp"
#include "hwlib.hpp"
//#include "keypad.hpp"


int main() {
	//Keypad . 
	auto out0 = hwlib::target::pin_oc( hwlib::target::pins::a0 );
	auto out1 = hwlib::target::pin_oc( hwlib::target::pins::a1 );
	auto out2 = hwlib::target::pin_oc( hwlib::target::pins::a2 );
	auto out3 = hwlib::target::pin_oc( hwlib::target::pins::a3 );

	auto in0  = hwlib::target::pin_in( hwlib::target::pins::a4 );
	auto in1  = hwlib::target::pin_in( hwlib::target::pins::a5 );
	auto in2  = hwlib::target::pin_in( hwlib::target::pins::a6 );
	auto in3  = hwlib::target::pin_in( hwlib::target::pins::a7 );

	auto out_port = hwlib::port_oc_from_pins( out0, out1, out2, out3 );
	auto in_port  = hwlib::port_in_from_pins( in0,  in1,  in2,  in3  );
	auto matrix   = hwlib::matrix_of_switches( out_port, in_port );
	auto keypad   = hwlib::keypad< 16 >( matrix, "123A456B789C*0#D" );
	
	//display 
	auto scl= hwlib::target::pin_oc(hwlib::target::pins::d9);
	auto sda = hwlib::target::pin_oc(hwlib::target::pins::d8);
	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl,sda);
	auto display = hwlib::glcd_oled_buffered(i2c_bus, 0x3c);
	auto font = hwlib::font_default_8x8(); 
	auto oled= hwlib::window_ostream(display, font);
	
	//pin voor het verzenden van ir signal. 
	auto IRLed= hwlib::target::pin_out(hwlib::target::pins::d5);
	auto transmitter = ir_transmitter(IRLed); 
	
	enum state_t= {IDLE, ADJUST_TTIME, BUTTON_PRESSED, SEND_IR_TIME, START_GAME};
	state= state_t; 
	state=IDLE;
	int min_tientallen=0;
	int min=0;
	int time=0; 
	while(1){
		switch(state){
		case IDLE: 
			if (keypad.getc()=='C'){
				state= ADJUST_TIME; 
				break; 
			}
		case ADJUST_TIME: 
			buttonTimer.set(20);
			min_tientallen= int(keypad.getc()-48);
			if (min_tientallen >=0 && min_tientallen <10)
			{
				min_tientallen *=10;
				state= BUTTON_PRESSED_TWO; 
				break
			}
			//als timer timed out is : state= idle 
		case BUTTON_PRESSED_TWO: 
			min = int(keypad.getc()-48); 
			if (min >= 0 && min <10)
			{
				time= min_tientallen + min ; 
				state= SEND_IR_TIME;
				break; 
			}
			//als timer timed out is : state= idle 
		case SEND_IR_TIME:
			if (keypad.getc()=='#')
			{
				transmitter.send(0,time);
			}
			else if (keypad.getc()=='*')
			{
				state= START_GAME; 
				break; 
			}
		case START_GAME:
			transmitter.send(0,0); 
			if(keypad.getc()=='D')
			{
				state=IDLE; 
				break; 
			}
			else if(keypad.getc()=='*')
			{
				break; 
			}
		}
		
		
		
		
		
		
		
		
		
		
		
		if (c =='C'){
			while(1){
				if(keypad.getc()=='#'){
					transmitter.send(10, 10);
					hwlib::wait_ms(100);
					oled << "\f " << '#' << "\t0001" << "Geef spelduur:.." << "\t0002" << hwlib::flush;
					min_tientallen = int((keypad.getc()-48))*10;
					oled << "\f " << '#' << "\t0001" << "Geef spelduur:"<<min_tientallen<<"." << "\t0002" << hwlib::flush;
					min= int((keypad.getc()-48));
					oled << "\f " << '#' << "\t0001" << "Geef spelduur:"<<min_tientallen<<min <<"Druk op # om de tijd instellen" << "\t0002" << hwlib::flush;
					if 
				}
				if(keypad.getc()=='*'){
					oled << "\f " << '*' << "\t0002" <<"Nothing send."<<"\t0003" << "returning to menu." << hwlib::flush;
					break;
				}
			}
		}
		
	}
}
