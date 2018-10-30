#include <cstdint>
struct Weapon{
	const char* name;
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

/* ----- WEAPON DEFINITIONS ----- */

Weapon weapon;
Player player;

/* ----- WEAPON PARAMETERS ----- */

/*enum weapon_id = {p90, ak47, m1911, rpg, m107, bfg};
weapon_id id;*/
void setWeapon(int weaponID){
	enum weapon_id {p90, ak47, m1911, rpg, m107, bfg};
	switch(weaponID){
		case p90:
			weapon.name = "FN-P90 (SMG)";
			weapon.damage = 10;
			weapon.ammo = 50;
			weapon.fire_rate = 400;
			break;
		case ak47:
			weapon.name = "AK-47 (AR)";
			weapon.damage = 25;
			weapon.ammo = 30;
			weapon.fire_rate = 1'000;
			break;
		case m1911:
			weapon.name = "M1911 (pistol)";
			weapon.damage = 15;
			weapon.ammo = 14;
			weapon.fire_rate = 500;
			break;
		case rpg:
			weapon.name = "RPG (Launcher)";
			weapon.damage = 100;
			weapon.ammo = 2;
			weapon.fire_rate = 7'000;
			break;
		case m107:
			weapon.name = "Barrett M107A1 (Sniper)";
			weapon.damage = 60;
			weapon.ammo = 10;
			weapon.fire_rate = 2'500;
			break;
		case bfg:
			weapon.name = "Big Fucking Gun 9000";
			weapon.damage = 100;
			weapon.ammo = 1;
			weapon.fire_rate = 8'000;
			break;
		default:
			weapon.name = "UNKNOWN";
			weapon.damage = 0;
			weapon.ammo = 999;
			weapon.fire_rate = 100;
	}
}

/*struct weapon{
	string name;
	int damage;
	int ammo;
	int fire_rate;
};*/

/*struct weapons{
	weapon P90;
	weapon AK-47;
	weapon m1911;
	weapon RPG;
	weapon M107;
	weapon bfg;
	weapon default;
};

weapons = {{"P90", 10, 50, 400}, { "AK-47 (AR)", 25, 30, 1'000}, {"M1911 (pistol)", 15, 14, 500}, {"RPG (Launcher)", 100, 2, 7'000}, 
{"Barrett M107A1 (Sniper)", 60, 10, 2'500}, {"Big Fucking Gun 9000", 100, 1, 8'000}, {"UNKNOWN", 0, 999, 100}};*/



/* Functions */

void setPlayer(int playerID){
	player.p_id = playerID;
}