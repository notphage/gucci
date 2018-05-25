// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_Trace;

class C_AutoWall
{
public:
	static float hitgroup_damage(int hitgroup);
	static void scale_damage(int hitgroup, C_BaseEntity* ent, float weapon_armor_ratio, float& current_damage);
	static bool trace_to_exit(Vector3& end, Vector3 start, Vector3 dir, C_Trace* enter_trace, C_Trace* exit_trace);
	static bool handle_bullet_penetration(surface_data* enter_surface, C_Trace* enter_trace, Vector3 direction, Vector3* origin, float range, float penetration, int& penetration_count, float& current_damage);
	static void util_clip_trace_to_players_rebuilt(Vector3 end, Vector3 start, C_Trace* oldtrace, C_BaseEntity* ent);
	bool invoke(Vector3 position, C_BaseEntity* entity, bool head, int mindmg, bool& penetrated) const;
};
