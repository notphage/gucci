// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

/*
 * weapon_type
 */
enum weapon_type
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN,
};

/*
 * weapon_weapons
 */
enum weapon_weapons
{
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T_SIDE = 5028,
	GLOVE_CT_SIDE = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_WRAP = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034
};

/*
 * weapon_info
 */
class weapon_info
{
	PAD(0x4)
public:
	bool m_parsed_script;
	bool m_loaded_hud_elements;
	char m_class_name[80];
	char m_print_name[80];
	char m_view_model[80];
	char m_world_model[80];
	char m_bullet_type[32];
	char m_world_dropped_model[80];
	char m_animation_prefix[16];
private:
	PAD(0x2);
public:
	int m_slot;
	int m_position;
	int m_max_clip1;
	int m_max_clip2;
	int m_default_clip1;
	int m_default_clip2;
	int m_weight;
	int m_rumble_effect;
	bool m_auto_switch_to;
	bool m_auto_switch_from;
private:
	PAD(0x2)
public:
	int m_flags;
	char m_ammo1[16];
	char m_ammo2[16];
	char m_ai_addon[80];
	char m_shoot_sounds[17][80];
private:
	PAD(0x50)
public:
	int m_ammo_type;
	int m_ammo2_type;
	bool m_melee_weapon;
	bool m_built_right_handed;
	bool m_allow_flipping;
private:
	PAD(0x1)
public:
	int m_sprite_count;
	C_HudTexture* m_icon_active;
	C_HudTexture* m_icon_inactive;
	C_HudTexture* m_icon_ammo;
	C_HudTexture* m_icon_ammo2;
	C_HudTexture* m_icon_crosshair;
	C_HudTexture* m_icon_autoaim;
	C_HudTexture* m_icon_zoomed_crosshair;
	C_HudTexture* m_icon_zoomed_autoaim;
	C_HudTexture* m_icon_small;
	bool m_show_usage_hint;
private:
	PAD(0x3)
public:
	int m_weapon_type;
	int m_team;
	int m_weapon_id;
	bool m_is_full_auto;
	float m_health_per_shot;
	int m_ingame_price;
	float m_armor_ratio;
	float m_max_player_speed;
	float m_max_player_speed_alt;
	int m_crosshair_min_distance;
	int m_crosshair_delta_distance;
	float m_penetration;
	int m_damage;
	float m_range;
	float m_range_modifier;
	int m_bullets;
	float m_cycle_time;
	float m_cycle_time_alt;
	char m_heat_effect[80];
	float m_smoke_color[3];
	char m_muzzle_flash_effect_firstperson[80];
	char m_muzzle_flash_effect_thirdperson[80];
	char m_eject_brass_effect[80];
	char m_tracer_effect[80];
	int m_tracer_frequency;
	float m_spread;
	float m_spread_alt;
	float m_inaccuracy_crouch;
	float m_inaccuracy_crouch_alt;
	float m_inaccuracy_stand;
	float m_inaccuracy_stand_alt;
	float m_inaccuracy_jump;
	float m_inaccuracy_jump_alt;
	float m_inaccuracy_land;
	float m_inaccuracy_land_alt;
	float m_inaccuracy_ladder;
	float m_inaccuracy_ladder_alt;
	float m_inaccuracy_fire;
	float m_inaccuracy_fire_alt;
	float m_inaccuracy_move;
	float m_inaccuracy_move_alt;
	float m_recovery_time_stand;
	float m_recovery_time_crouch;
	float m_inaccuracy_reload;
	float m_inaccuracy_reload_alt;
	float m_recoil_angle;
	float m_recoil_angle_alt;
	float m_recoil_angle_variance;
	float m_recoil_angle_variance_alt;
	float m_recoil_magnitude;
	float m_recoil_magnitude_alt;
	float m_recoil_magnitude_variance;
	float m_recoil_magnitude_variance_alt;
	int m_recoil_seed;
	float m_flinch_velocity_modifier_large;
	float m_flinch_velocity_modifier_small;
	float m_time_to_idle;
	float m_idle_interval;
	float m_recoil_table[2][128];
	int m_zoom_levels;
	int m_zoom_fov[3];
	float m_zoom_time[3];
	bool m_hide_viewmodel_zoomed;
	char m_zoom_in_sound[80];
	char m_zoom_out_sound[80];
private:
	PAD(0x3)
public:
	float m_bot_audible_range;
	bool m_can_use_with_shield;
	char m_wrong_team_message[32];
	char m_anim_prefix[16];
	char m_shield_viewmodel[64];
	char m_addon_model[80];
	char m_addon_location[80];
	char m_silencer_model[80];
private:
	PAD(0x3)
public:
	float m_addon_scale;
	float m_throw_velocity;
	int m_kill_award;
private:
	PAD(0x8)
};
