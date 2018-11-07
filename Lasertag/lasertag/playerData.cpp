#include "playerData.hpp"
void weaponLookup(const int & weaponID, Weapon& weapon){
	enum weapon_id {p90, ak47, m1911, rpg, m107, bfg};
	switch(weaponID){
		case p90:
			weapon.name = "FN-P90";
			weapon.damage = 10;
			weapon.ammo = 50;
			break;
		case ak47:
			weapon.name = "AK-47";
			weapon.damage = 25;
			weapon.ammo = 30;
			break;
		case m1911:
			weapon.name = "M1911";
			weapon.damage = 15;
			weapon.ammo = 14;
			break;
		case rpg:
			weapon.name = "RPG";
			weapon.damage = 100;
			weapon.ammo = 5;
			break;
		case m107:
			weapon.name = "Barrett .50 cal";
			weapon.damage = 60;
			weapon.ammo = 10;
			break;
		case bfg:
			weapon.name = "BFG 9000";
			weapon.damage = 100;
			weapon.ammo = 3;
			break;
		default:
			weapon.name = "UNKNOWN";
			weapon.damage = 0;
			weapon.ammo = 999;
	}
}