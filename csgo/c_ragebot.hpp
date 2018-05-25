// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

#include "ragebot.hpp"

class C_RageBot
{
public:
	C_AutoWall autowall;

	static bool can_hit_hitbox(C_BaseEntity* entity, Vector3 hitbox_position, int hitbox);
	ragebot_record get_best_target(C_UserCmd* cmd) const;
	static Vector3 get_entity_hitbox(C_BaseEntity* entity, int* hitbox = nullptr);
	float get_entity_hitchance(Angle angle, C_BaseEntity* entity) const;
	static Vector3 resolve_entity(C_BaseEntity* entity, Vector3 vector);
	static bool can_aimbot();
	static bool can_aimbot_player(C_BaseEntity* entity);
	bool run(C_UserCmd* cmd, bool& send_packet) const;
};
