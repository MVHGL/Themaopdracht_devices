/// @file mainGameControlTask.hpp
#ifndef _MAINGAMECONTROLTASK_HPP
#define _MAINGAMECONTROLTASK_HPP
#include "rtos.hpp"
#include "ir_transmitter.hpp"
#include "displayTask.hpp"
#include "playerData.hpp"
#include "gameTimeControl.hpp"

/// \brief
/// mainGameControlTask class
/// \details
/// mainGameControlTask class which implements the rtos::task<> class. It is used to control the game.
class mainGameControlTask : public rtos::task<> {
private:
	ir_transmitter& transmitter;
	displayTask& display;
	gameTimeControl& timerControl;
	rtos::channel<int, 2> messages;
	rtos::flag timeCompletedFlag;
	rtos::flag triggerFlag;
	rtos::pool<uint16_t> playerIdPool;
	rtos::pool<uint16_t> weaponIdPool;
	rtos::flag setPlayerParamsFlag;
	rtos::flag channelFullFlag;
	enum state_t {REGISTER_GAME, REGISTER_TIME, IDLE, TRIGGER, MESSAGE_RECEIVE, GAME_OVER};
	state_t state;
	uint16_t ownWeaponID;
	Weapon enemyWeapon;
	Weapon ownWeapon;
	Player player;
	bool validTime, validStart;
	void handleMessageReceived();
	void handleTriggerButton();
public:
	/// \brief
	/// mainGameControlTask constructor.
	/// \details
	/// mainGameControlTask constructor. It requires a reference to an ir_transmitter, displayTask and a gameTimeControl.
	mainGameControlTask(ir_transmitter& transmitter, displayTask& display, gameTimeControl& timerControl);
	/// \brief
	/// Gets an IR message.
	/// \details
	/// This function is called when an IR message is received. The playerID and data will be written in the channel.
	void IRMessageReceived(const uint16_t& playerID, const uint16_t& data);
	/// \brief
	/// Trigger function.
	/// \details
	/// This function is called when a trigger (switch) is pressed.
	void triggered();
	/// \brief
	/// gameOver method.
	/// \details
	/// Called when a game is over (for e.g. when the time is up, or the lifepoints are lower or equal to zero).
	void gameOver();
	/// \brief
	/// Sets player parameters.
	/// \details
	/// This method is called to write the player parameters.
	void setPlayerParams(const uint16_t& playerID, const uint16_t& weaponID);
	/// \brief
	/// Main method
	/// Implements the main method inherited from rtos::task<>.
	void main() override;
};
#endif
