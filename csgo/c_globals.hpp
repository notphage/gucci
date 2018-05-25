// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

/*
 * G
 * Global namespace that allows variables and classes to be broadcasted everywhere
 */
namespace G
{
	// Utilities
	extern C_Console console;
	extern C_InterfaceList interfaces;
	extern C_HookList hooks;
	extern C_NetVarScanner netvars;
	extern C_SignatureScanner signature;
	extern C_Math math;
	extern C_Module modules;
	extern C_MenuSettings settings;

	// Variables / Other
	extern C_BaseEntity* me;
	extern antiban_state_data antiban_data;
	extern player_prediction_data prediction_data;
	extern int player_shots[64];
	extern int resolve_ticks[64];
	extern C_Player_Record player_lag_records[64];
	extern C_Resolve_Record player_resolve_records[64];
	extern std::vector<Vector3> walkbot_points;
	extern round_gameflags round_flags;
	extern int reloading_data[1];
	extern float autowall_damage;
	extern bool breaking_lag_compensation;
	extern C_UserCmd* cmd;
	extern C_UserCmd original_cmd;
	extern Vector3 last_sent_origin;
}
