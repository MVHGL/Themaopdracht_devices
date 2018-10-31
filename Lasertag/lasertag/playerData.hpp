#ifndef _PLAYERDATA_HPP
#define _PLAYERDATA_HPP
#include "hwlib.hpp"
struct Weapon {
	hwlib::string<40> name;
	uint16_t damage;
	uint16_t ammo;
	uint16_t fire_rate;
};

struct Player{
	uint16_t p_id = 99;
	uint16_t hp = 100;
	uint16_t shield = 0;
	uint16_t score = 0;
};

void weaponLookup(const int & weaponID, Weapon& weapon);
#endif