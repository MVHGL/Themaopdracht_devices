/// @file playerData.hpp

#ifndef _PLAYERDATA_HPP
#define _PLAYERDATA_HPP
#include "hwlib.hpp"
/// \brief
/// Weapon struct.
/// \details
/// Basic Weapon struct for saving its weapon name, damage and ammo.
struct Weapon {
	/// \brief
	/// Weapon name.
	hwlib::string<40> name;
	/// \brief
	/// Weapon damage.
	uint16_t damage;
	/// \brief
	/// Weapon ammunition.
	uint16_t ammo;
};
/// \brief
/// Player struct.
/// \details
/// Basic Player struct for saving its player ID, health and shield.
struct Player{
	/// \brief
	/// Player id, default is 99.
	uint16_t p_id = 99;
	/// \brief
	/// Player hp. Is always 100.
	uint16_t hp = 100;
	uint16_t shield = 0;
	uint16_t score = 0;
};
/// \brief
/// weaponLookup function.
/// \details
/// This function is used to check what weapon the enemy was using. It requres a weapon ID and a reference to a Weapon struct.
void weaponLookup(const int & weaponID, Weapon& weapon);
#endif