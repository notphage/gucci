// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

#define PITCH 0
#define YAW 1

class C_GameEvent;

class C_Resolve_Record
{
public:
	C_Resolve_Record()
	{
	}

	~C_Resolve_Record()
	{
	}

	Angle resolved_angle;
	Angle original_angle;
	Angle hit_angle;
	Angle shot_angle;

	bool yaw_lby = false;
	bool yaw_hit_lby = false;
	bool yaw_lby_ran = false;
	int yaw_resolver = 0;
	int yaw_hit_resolver = 0;
	int last_shot_ticks = 0;
	int last_hit_ticks = 0;
	int shot_ticks_lby = 0;
	int ticks_lby = 0;
};

class C_Resolver
{
public:
	bool resolve_pitch(C_BaseEntity* entity) const;
	bool resolve_yaw(C_BaseEntity* entity) const;
	float resolve(C_BaseEntity * entity, int resole_part) const;
	void fire_game_event(C_GameEvent* game_event) const;
};
