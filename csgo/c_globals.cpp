// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * G
 * Global namespace that allows variables and classes to be broadcasted everywhere
 */

C_Console G::console;
C_InterfaceList G::interfaces;
C_HookList G::hooks;
C_NetVarScanner G::netvars;
C_SignatureScanner G::signature;
C_Math G::math;
C_Module G::modules;
C_MenuSettings G::settings;

C_BaseEntity* G::me = nullptr;
antiban_state_data G::antiban_data;
player_prediction_data G::prediction_data;
int G::player_shots[64];
int G::resolve_ticks[64];
C_Player_Record G::player_lag_records[64];
C_Resolve_Record G::player_resolve_records[64];
std::vector<Vector3> G::walkbot_points;
round_gameflags G::round_flags = ROUND_STARTING;
int G::reloading_data[1];
float G::autowall_damage;
bool G::breaking_lag_compensation;
C_UserCmd* G::cmd;
C_UserCmd G::original_cmd;
Vector3 G::last_sent_origin;
