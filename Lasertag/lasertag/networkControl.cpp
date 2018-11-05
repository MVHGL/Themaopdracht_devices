#include "networkControl.hpp"

networkControl::networkControl(hwlib::pin_out & tx_data, hwlib::pin_out & tx_clock):
	task("Network control task"),
	tx_data(tx_data),
	tx_clock(tx_clock),
	enemyPlayerChannel(this, "Enemy player channel"),
	weaponDamageChannel(this, "Weapon damage channel"),
	sendFlag(this, "Send flag"),
	mutex("Network control mutex")
{}
void networkControl::sendMessage(const uint16_t & enemyPlayerId, const uint16_t & weaponDamage){
	enemyPlayerChannel.write(enemyPlayerId);
	weaponDamageChannel.write(weaponDamage);
	sendFlag.set();
}
void networkControl::handleMessage(void){
	mutex.wait();
	uint16_t enemyPlayer = enemyPlayerChannel.read();
	uint16_t weaponDamage = weaponDamageChannel.read();
	hwlib::cout << "Sending data!\n";
	tx_clock.set(0);
	//Send enemyPlayer data
	for (uint16_t i = 0; i <16; i++) {
		tx_data.set(((enemyPlayer >> i) & 1));
		hwlib::wait_ms((1000 / tx_rate) / 2);
		tx_clock.set(1); // Pulse clock
		hwlib::wait_ms((1000 / tx_rate) / 2);
		tx_clock.set(0);
	}
	//Send weaponDamage data
	for (uint16_t i = 0; i < 16; i++) {
		tx_data.set(((weaponDamage >> i) & 1));
		hwlib::wait_ms((1000 / tx_rate) / 2);
		tx_clock.set(1); // Pulse clock
		hwlib::wait_ms((1000 / tx_rate) / 2);
		tx_clock.set(0);
	}
	mutex.signal();
}


void networkControl::main(){
	state = IDLE;
	while(true){
		switch(state){
			case IDLE:{
				wait(sendFlag);
				state = SEND;
				break;
			}
			case SEND:{
				handleMessage();
				state = IDLE;
				break;
			}
		}
	}
}

