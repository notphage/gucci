// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017D
// *********************************

#pragma once

enum
{
	hitgroup_generic,
	hitgroup_head,
	hitgroup_chest,
	hitgroup_stomach,
	hitgroup_leftarm,
	hitgroup_rightarm,
	hitgroup_leftleg,
	hitgroup_rightleg,
	hitgroup_gear = 10
};

/*
 * player_old_flags
 */
struct player_old_flags
{
	int flags;
	float curtime;
};

/*
 * player_prediction_data
 */
struct player_prediction_data
{
	void reset()
	{
		prediction_stage = 0 , tickbase = 0;
		random_seed = 0;
		in_prediction = false;
		curtime = 0.f , frametime = 0.f;
		prediction_random_seed = nullptr;
	}

	int prediction_stage = 0, tickbase = 0;
	unsigned random_seed = 0;
	bool in_prediction = false;
	float curtime = 0.f, frametime = 0.f;
	unsigned* prediction_random_seed = nullptr;
	player_old_flags non_predicted;
};

/*
 * player_hitbox
 */
enum player_hitbox
{
	hitbox_head = 0,
	hitbox_neck,
	hitbox_lower_neck,
	hitbox_pelvis,
	hitbox_body,
	hitbox_thorax,
	hitbox_chest,
	hitbox_r_thigh,
	hitbox_l_thigh,
	hitbox_r_calf,
	hitbox_l_calf,
	hitbox_r_foot,
	hitbox_l_foot,
	hitbox_r_hand,
	hitbox_l_hand,
	hitbox_r_upperarm,
	hitbox_r_forearm,
	hitbox_l_upperarm,
	hitbox_l_forearm,
	hitbox_max,
};

/*
 * player_info
 */
struct player_info
{
	PAD(0x8)
	int xuidlow;
	int xuidhigh;
	char name[128];
	int userid;
	char guid[33];
	PAD(0x17B)
};

/*
 * player_team
 */
enum player_team
{
	TEAM_SPECTATOR = 1,
	TEAM_T = 2,
	TEAM_CT = 3,
};

/*
 * player_movetype
 */
enum player_movetype
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

/*
 * player_flags
 */
enum player_flags
{
	FL_ONGROUND = 1 << 0,
	FL_DUCKING = 1 << 1,
	FL_WATERJUMP = 1 << 2,
	FL_ONTRAIN = 1 << 3,
	FL_INRAIN = 1 << 4,
	FL_FROZEN = 1 << 5,
	FL_ATCONTROLS = 1 << 6,
	FL_CLIENT = 1 << 7,
	FL_FAKECLIENT = 1 << 8,
	FL_INWATER = 1 << 9,
	FL_FLY = 1 << 10,
	FL_SWIM = 1 << 11,
	FL_CONVEYOR = 1 << 12,
	FL_NPC = 1 << 13,
	FL_GODMODE = 1 << 14,
	FL_NOTARGET = 1 << 15,
	FL_AIMTARGET = 1 << 16,
	FL_PARTIALGROUND = 1 << 17,
	FL_STATICPROP = 1 << 18,
	FL_GRAPHED = 1 << 19,
	FL_GRENADE = 1 << 20,
	FL_STEPMOVEMENT = 1 << 21,
	FL_DONTTOUCH = 1 << 22,
	FL_BASEVELOCITY = 1 << 23,
	FL_WORLDBRUSH = 1 << 24,
	FL_OBJECT = 1 << 25,
	FL_KILLME = 1 << 26,
	FL_ONFIRE = 1 << 27,
	FL_DISSOLVING = 1 << 28,
	FL_TANSRAGDOLL = 1 << 29,
	FL_UNBLOCKABLE_BY_PLAYER = 1 << 30,
	IN_ATTACK = 1 << 0,
	IN_JUMP = 1 << 1,
	IN_DUCK = 1 << 2,
	IN_FORWARD = 1 << 3,
	IN_BACK = 1 << 4,
	IN_USE = 1 << 5,
	IN_CANCEL = 1 << 6,
	IN_LEFT = 1 << 7,
	IN_RIGHT = 1 << 8,
	IN_MOVELEFT = 1 << 9,
	IN_MOVERIGHT = 1 << 10,
	IN_ATTACK2 = 1 << 11,
	IN_RUN = 1 << 12,
	IN_RELOAD = 1 << 13,
	IN_ALT1 = 1 << 14,
	IN_ALT2 = 1 << 15,
	IN_SCORE = 1 << 16,
	IN_SPEED = 1 << 17,
	IN_WALK = 1 << 18,
	IN_ZOOM = 1 << 19,
	IN_WEAPON1 = 1 << 20,
	IN_WEAPON2 = 1 << 21,
	IN_BULLRUSH = 1 << 22,
	IN_GRENADE1 = 1 << 23,
	IN_GRENADE2 = 1 << 24
};

/*
 * frame_stage
 */
enum frame_stage
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

/*
 * C_Player_Animation_State
 */
class C_Player_Animation_State
{
	PAD(0x80)
public:
	float goal_feet_yaw;
};
