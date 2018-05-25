// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

/*
 * C_UserCmd
 * User command structure
 */
struct C_UserCmd
{
	virtual ~C_UserCmd()
	{
	}

	int command_number;
	int tick_count;
	Angle viewangles;
	Vector3 aimdirection;
	Vector3 move;
	int buttons;
	byte impulse;
	int weaponselect;
	int weaponsubtype;
	int random_seed;
	short mousedx;
	short mousedy;
	bool hasbeenpredicted;
	char _[24];
};
