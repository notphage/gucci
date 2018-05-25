// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_BaseWeapon
{
public:
	/*
	 * read
	 * Reads data
	 */
	template <typename T>
	T read(uintptr_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

	/*
	 * write
	 * Writes data to the offset from the entity specified
	 */
	template <typename T>
	void write(uintptr_t offset, T data)
	{
		*reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset) = data;
	}

	/*
	 * get_next_primary_attack
	 * Returns the next primary attack time
	 */
	float get_next_primary_attack()
	{
		return read<float>(G::netvars.m_NetVars["DT_BaseCombatWeapon"_crc]["m_flNextPrimaryAttack"_crc]);
	}

	/*
	 * get_ready_time
	 * Returns the next time the weapon is ready for fire
	 */
	float get_ready_time()
	{
		return read<float>(G::netvars.m_NetVars["DT_WeaponCSBase"_crc]["m_flPostponeFireReadyTime"_crc]);
	}

	/*
	 * get_recoil_index
	 * Returns the weapons recoil index
	 */
	float get_recoil_index()
	{
		return read<float>(G::netvars.m_NetVars["DT_WeaponCSBase"_crc]["m_flRecoilIndex"_crc]);
	}

	/*
	 * get_clip_1
	 * Returns the players clip
	 */
	int get_clip_1()
	{
		return read<int>(G::netvars.m_NetVars["DT_WeaponCSBase"_crc]["m_iClip1"_crc]);
	}

	/*
	 * get_burst_shots_remaining
	 * Returns the players burst shots remaining
	 */
	int get_burst_shots_remaining()
	{
		return read<int>(G::netvars.m_NetVars["DT_WeaponCSBaseGun"_crc]["m_iBurstShotsRemaining"_crc]);
	}

	/*
	 * get_grenade_throw_time
	 * Returns the grenades throw time 
	 */
	float get_grenade_throw_time()
	{
		return read<float>(G::netvars.m_NetVars["DT_BaseCSGrenade"_crc]["m_fThrowTime"_crc]);
	}

	/*
	 * get_index
	 * Returns the weapons index
	 */
	int get_index()
	{
		return read<int>(0x2F88);
	}

	/*
	 * get_sequence
	 * Returns the weapons operation sequence
	 */
	int get_sequence()
	{
		return read<int>(G::netvars.m_NetVars["DT_BaseAnimating"_crc]["m_nSequence"_crc]);
	}

	/*
	 * is_grenade
	 * Returns if the weapon is a grenade
	 */
	bool is_grenade()
	{
		return get_type() == WEAPONTYPE_GRENADE;
	}

	/*
	 * was_pin_pulled
	 * Returns if the grenades pin was pulled
	 */
	bool was_pin_pulled()
	{
		return read<bool>(G::netvars.m_NetVars["DT_BaseCSGrenade"_crc]["m_bPinPulled"_crc]);
	}

	/*
	 * get_type
	 * Returns the weapons type
	 */
	weapon_type get_type()
	{
		return static_cast<weapon_type>(get_weapon_data()->m_weapon_type);
	}

	/*
	 * get_weapon_data
	 * Returns the players weapon data
	 */
	weapon_info* get_weapon_data()
	{
		return vtable<weapon_info*(__thiscall*)(void*)>(this, 456)(this);
	}

	/*
	 * get_name
	 * Returns the players weapon name
	 */
	const char* get_name()
	{
		return vtable<const char*(__thiscall*)(void*)>(this, 378)(this);
	}

	/*
	 * get_weapon_name
	 * Returns the players weapon name
	 */
	char* get_weapon_name()
	{
		switch (get_index())
		{
			case WEAPON_DEAGLE:
				return "Deagle";
			case WEAPON_REVOLVER:
				return "Revolver";
			case WEAPON_ELITE:
				return "Dual-Elites";
			case WEAPON_FIVESEVEN:
				return "Five-Seven";
			case WEAPON_GLOCK:
				return "Glock";
			case WEAPON_AK47:
				return "AK47";
			case WEAPON_AUG:
				return "AUG";
			case WEAPON_AWP:
				return "AWP";
			case WEAPON_FAMAS:
				return "Famas";
			case WEAPON_G3SG1:
				return "G3SG1";
			case WEAPON_GALILAR:
				return "Galil";
			case WEAPON_M249:
				return "M249";
			case WEAPON_M4A1:
				return "M4A1";
			case WEAPON_M4A1_SILENCER:
				return "M4A1-S";
			case WEAPON_MAC10:
				return "MAC-10";
			case WEAPON_P90:
				return "P90";
			case WEAPON_UMP45:
				return "UMP-45";
			case WEAPON_XM1014:
				return "XM1014";
			case WEAPON_BIZON:
				return "Bizon";
			case WEAPON_MAG7:
				return "MAG-7";
			case WEAPON_NEGEV:
				return "Negev";
			case WEAPON_SAWEDOFF:
				return "Sawed-Off";
			case WEAPON_TEC9:
				return "Tec-9";
			case WEAPON_TASER:
				return "Taser";
			case WEAPON_HKP2000:
				return "HKP2000";
			case WEAPON_MP7:
				return "MP7";
			case WEAPON_MP9:
				return "MP9";
			case WEAPON_NOVA:
				return "Nova";
			case WEAPON_P250:
				return "P250";
			case WEAPON_USP_SILENCER:
				return "USP-S";
			case WEAPON_SCAR20:
				return "SCAR-20";
			case WEAPON_SG556:
				return "SG-556";
			case WEAPON_SSG08:
				return "SSG-08";
			case WEAPON_KNIFE:
			case WEAPON_KNIFE_T:
			case WEAPON_KNIFE_BAYONET:
			case WEAPON_KNIFE_FLIP:
			case WEAPON_KNIFE_GUT:
			case WEAPON_KNIFE_KARAMBIT:
			case WEAPON_KNIFE_M9_BAYONET:
			case WEAPON_KNIFE_TACTICAL:
			case WEAPON_KNIFE_FALCHION:
			case WEAPON_KNIFE_SURVIVAL_BOWIE:
			case WEAPON_KNIFE_BUTTERFLY:
			case WEAPON_KNIFE_PUSH:
				return "Knife";
			case WEAPON_C4:
				return "C4";
			case WEAPON_FLASHBANG:
				return "Flashbang";
			case WEAPON_HEGRENADE:
				return "Grenade";
			case WEAPON_SMOKEGRENADE:
				return "Smoke-Grenade";
			case WEAPON_MOLOTOV:
				return "Molotov";
			case WEAPON_INCGRENADE:
				return "Incendiary";
			case WEAPON_DECOY:
				return "Decoy-Grenade";
			default:
				return "Unknown";
		}
	}

	/*
	 * get_spread
	 * Returns the weapons spread
	 */
	float get_spread()
	{
		return vtable<float(__thiscall*)(void*)>(this, 483)(this);
	}

	/*
	 * get_cone
	 * Returns the weapons cone
	 */
	float get_cone()
	{
		return vtable<float(__thiscall*)(void*)>(this, 484)(this);
	}

	/*
	 * update_accuracy_penalty
	 * Updates the accuracy penalty
	 */
	void update_accuracy_penalty()
	{
		return vtable<void(__thiscall*)(void*)>(this, 485)(this);
	}
};
