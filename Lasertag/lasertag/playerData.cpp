#include "playerData.hpp"
void weaponLookup(const int & weaponID, Weapon& weapon){
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