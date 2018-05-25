// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017D
// *********************************

#pragma once

/*
 * ragebot_record
 */
struct ragebot_record
{
	bool success = false;
	C_BaseEntity* entity = nullptr;
	Vector3 aim_position = Vector3();
};

/*
 * round_gameflags
 */
enum round_gameflags
{
	ROUND_STARTING = 0,
	ROUND_IN_PROGRESS,
	ROUND_ENDING,
};
