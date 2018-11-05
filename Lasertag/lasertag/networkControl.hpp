#ifndef NETWORKCONTROL_HPP
#define NETWORKCONTROL_HPP
#include "hwlib.hpp"
#include "rtos.hpp"
#include <bitset>
class networkControl : public rtos::task<>
{
private:
	hwlib::pin_out & tx_data;
	hwlib::pin_out & tx_clock;
	rtos::channel<uint16_t, 6> enemyPlayerChannel;
	rtos::channel<uint16_t, 6> weaponDamageChannel;
	rtos::flag sendFlag;
	rtos::mutex mutex;
	enum state_t{IDLE, SEND};
	state_t state;
	uint8_t tx_rate = 100;
	void handleMessage(void);
public:
	networkControl(hwlib::pin_out & tx_data, hwlib::pin_out & tx_clock);
	void sendMessage(const uint16_t & enemyPlayerId, const uint16_t & weaponDamage);
	void main() override;
};

#endif // NETWORKCONTROL_HPP
