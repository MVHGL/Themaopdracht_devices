struct Weapon{
	uint16_t w_id = 999;
	char[] name = "Unknown";
	uint16_t damage = 0;
	uint16_t ammo = 0;
	uint16_t fire_rate = 100;
}

struct player{
	uint16_t p_id = 99;
	uint16_t hp = 100;
	uint16_t shield = 0;
	uint16_t score = 0;
}

/* ----- WEAPON DEFINITIONS ----- */

Weapon p_90;
Weapon ak47;
Weapon m1911;
Weapon rpg;
Weapon m107;


/* ----- WEAPON PARAMETERS ----- */

p_90.name = "FN-P90 (SMG)";
p_90.damage = 10;
p_90.ammo = 50;
p_90.fire_rate = 400;

ak47.name = "AK-47 (AR)";
ak47.damage = 25;
ak47.ammo = 30;
ak47.fire_rate = 1'000;

m1911.name = "M1911 (pistol)";
m1911.damage = 15;
m1911.ammo = 14;
m1911.fire_rate = 500;

rpg.name = "RPG (Launcher)";
rpg.damage = 100;
rpg.ammo = 2;
rpg.fire_rate = 7'000;

m107.name = "Barrett M107A1 (Sniper)";
m107.damage = 60;
m107.ammo = 10;
m107.fire_rate = 2'500;






