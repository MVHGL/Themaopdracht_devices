/// @file ir_receiver.hpp
#ifndef _IR_RECEIVER_HPP
#define _IR_RECEIVER_HPP
#include <cstdint>
#include "rtos.hpp"
#include "ir_decoder.hpp"
#include "mainGameControlTask.hpp"

/// \brief
/// ir_receiver class.
/// \details
/// ir_receiver class which is used to receive IR messages. Implements rtos::task<>.
class ir_receiver : public rtos::task<>
{
private:
	hwlib::pin_in & receiver;
	ir_decoder decoder;
	int pause_count;
	rtos::clock clock;
	rtos::channel<int, 33> pauses;
	rtos::mutex mutex;
	int counter;
	enum state_t {IDLE, SIGNAL, MESSAGE};
	state_t state = IDLE;
	
	void putMessage();
	void pause_detected(const int& n);
	void get();
public:
	/// \brief
	/// ir_receiver constructor.
	/// \details
	/// ir_receiver constructor which requres a reference to a hwlib::pin_in and a mainGameControlTask.
	ir_receiver(hwlib::pin_in & receiver, mainGameControlTask& mainGame);
	/// \brief
	/// Main implemenation
	/// \details
	/// Implements the main method inherited from rtos::task<>.
	void main() override;
};
#endif

