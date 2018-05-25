// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

/*
 * C_BaseEntity
 * Base Entity class for entities
 */
class C_BaseEntity
{
public:
	PAD(0x64)
	int index;

	/*
	 * read
	 * Reads data
	 */
	template <typename T>
	T& read(uintptr_t offset)
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

	enum Index
	{
		GET_OBBMINS = 1,
		GET_OBBMAXS = 2,
		GET_INDEX = 10,
		GET_WEAPON_ENT_NAME = 370,
		GET_WEAPON_NAME = 371,
		GET_ABS_ORIGIN = 10,
		GET_ABS_ANGLES = 11,
		IS_SELF_ANIMATING = 152,
		GET_MODEL = 8,
		UPDATE_CLIENTSIDE_ANIMATIONS = 218,
		SETUP_BONES = 13,
		GET_VIEW_PUNCH = 100,
		GET_AIM_PUNCH = 112,
		IS_DORMANT = 9,
	};

	/*
	 * get_renderable
	 * Returns the renderable
	 */
	void* get_renderable()
	{
		return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + 0x4);
	}

	/*
	 * get_networkable
	 * Returns the networkable
	 */
	void* get_networkable()
	{
		return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + 0x8);
	}

	/*
	 * get_weapon
	 * Returns a pointer to the players base weapon class
	 */
	C_BaseWeapon* get_weapon()
	{
		auto active_weapon = read<DWORD>(G::netvars.m_NetVars["DT_CSPlayer"_crc]["m_hActiveWeapon"_crc]) & 0xFFF;
		return reinterpret_cast<C_BaseWeapon*>(G::interfaces.entitylist->get_client_entity(active_weapon));
	}

	/*
	 * get_rgflcoordinateframe
	 * Returns the rgfl coordinates frames
	 */
	Matrix3x4 get_rgflcoordinateframe()
	{
		return read<Matrix3x4>(0x440);
	}

	/*
	 * get_health
	 * Returns the players health
	 */
	int& get_health()
	{
		return read<int>(G::netvars.m_NetVars["DT_BasePlayer"_crc]["m_iHealth"_crc]);
	}

	/*
	 * get_team
	 * Returns the players team
	 */
	player_team& get_team()
	{
		return read<player_team>(G::netvars.m_NetVars["DT_CSPlayer"_crc]["m_iTeamNum"_crc]);
	}

	/*
	 * get_entity_flags
	 * Returns the players entity flags
	 */
	int& get_entity_flags()
	{
		return read<int>(G::netvars.m_NetVars["DT_CSPlayer"_crc]["m_fFlags"_crc]);
	}

	/*
	 * get_animation_state
	 * Returns the players animation state
	 */
	C_Player_Animation_State* get_animation_state()
	{
		return read<C_Player_Animation_State*>(0x3894);
	}

	/*
	 * get_move_type
	 * Returns the players movetype
	 */
	player_movetype& get_move_type()
	{
		return read<player_movetype>(0x258);
	}

	/*
	 * get_ammo
	 * Returns the players ammo
	 */
	int& get_ammo()
	{
		return read<int>(G::netvars.m_NetVars["DT_BasePlayer"_crc]["m_iAmmo"_crc]);
	}

	/*
	 * get_armor
	 * Returns the players armor
	 */
	int& get_armor()
	{
		return read<int>(G::netvars.m_NetVars["DT_CSPlayer"_crc]["m_ArmorValue"_crc]);
	}

	/*
	 * get_index
	 * Returns the players index
	 */
	int get_index()
	{
		auto pNetwork = get_networkable();

		return vtable<int(__thiscall*)(void*)>(pNetwork, GET_INDEX)(pNetwork);
	}

	/*
	 * get_sequence
	 * Returns the weapons operation sequence
	 */
	int& get_sequence()
	{
		return read<int>(G::netvars.m_NetVars["DT_BaseAnimating"_crc]["m_nSequence"_crc]);
	}

	/*
	 * get_cycle
	 * Returns the players cycle
	 */
	float& get_cycle()
	{
		return read<float>(G::netvars.m_NetVars["DT_BaseAnimating"_crc]["m_flCycle"_crc]);
	}

	/*
	 * get_info
	 * Returns the players information
	 */
	player_info get_info()
	{
		player_info info;
		G::interfaces.engine->get_playerinfo(get_index(), &info);

		return info;
	}

	/*
	 * get_collision
	 * Returns the collision class pointer
	 */
	void* get_collision()
	{
		return read<void*>(G::netvars.m_NetVars["DT_BasePlayer"_crc]["m_Collision"_crc]);
	}

	/*
	 * get_obbmins
	 * Returns the players obbmins vector
	 */
	Vector3& get_obbmins()
	{
		return read<Vector3>(G::netvars.m_NetVars["DT_BaseEntity"_crc]["m_vecMins"_crc]);
	}

	/*
	 * get_obbmaxs
	 * Returns the players obbmins vector
	 */
	Vector3& get_obbmaxs()
	{
		return read<Vector3>(G::netvars.m_NetVars["DT_BaseEntity"_crc]["m_vecMaxs"_crc]);
	}

	/*
	 * get_abs_origin
	 * Returns the players origin
	 */
	Vector3& get_abs_origin()
	{
		return vtable<Vector3&(__thiscall*)(void*)>(this, GET_ABS_ORIGIN)(this);
	}

	/*
	 * get_abs_eye_angles
	 * Returns the players absolute angles
	 */
	Angle& get_abs_eye_angles()
	{
		return vtable<Angle&(__thiscall*)(void*)>(this, GET_ABS_ANGLES)(this);
	}

	/*
	 * set_abs_origin
	 * Sets the players absolute origin
	 */
	void set_abs_origin(const Vector3& origin)
	{
		static auto setabsorigin_ptr = G::signature.find_signature("client.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8 ? ?");
		reinterpret_cast<void(__thiscall*)(C_BaseEntity*, const Vector3&)>(setabsorigin_ptr)(this, origin);
	}


	/*
	 * set_abs_angles
	 * Sets the players absolute angles
	 */
	void set_abs_angles(const Angle& origin)
	{
		static auto setabsangles_ptr = G::signature.find_signature("client.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1 E8");
		reinterpret_cast<void(__thiscall*)(C_BaseEntity*, const Angle&)>(setabsangles_ptr)(this, origin);
	}


	/*
	 * get_origin
	 * Returns the players origin
	 */
	Vector3& get_origin()
	{
		return read<Vector3>(G::netvars.m_NetVars["DT_BasePlayer"_crc]["m_vecOrigin"_crc]);
	}

	/*
	 * get_velocity
	 * Returns the players velocity
	 */
	Vector3& get_velocity()
	{
		return read<Vector3>(G::netvars.m_NetVars["DT_CSPlayer"_crc]["m_vecVelocity[0]"_crc]);
	}

	/*
	 * get_eye_offset
	 * Returns the players eye offset
	 */
	Vector3 get_eye_offset()
	{
		return read<Vector3>(G::netvars.m_NetVars["DT_BasePlayer"_crc]["m_vecViewOffset[0]"_crc]);
	}

	/*
	 * get_eye_origin
	 * Returns the players eye origin
	 */
	Vector3 get_eye_origin()
	{
		return get_origin() + get_eye_offset();
	}

	/*
	 * get_eye_angles
	 * Returns the players eye angles
	 */
	Angle& get_eye_angles()
	{
		return read<Angle>(G::netvars.m_NetVars["DT_CSPlayer"_crc]["m_angEyeAngles"_crc]);
	}

	/*
	 * get_view_punch
	 * Returns the players view punch
	 */
	Angle& get_view_punch()
	{
		return read<Angle>(G::netvars.m_NetVars["DT_BasePlayer"_crc]["m_Local"_crc] + GET_VIEW_PUNCH);
	}

	/*
	 * get_aim_punch
	 * Returns the players aim punch
	 */
	Angle& get_aim_punch()
	{
		return read<Angle>(G::netvars.m_NetVars["DT_BasePlayer"_crc]["m_Local"_crc] + GET_AIM_PUNCH);
	}

	/*
	 * get_lowerbody_yaw
	 * Returns the players lowerbody yaw
	 */
	float& get_lower_body_yaw()
	{
		return read<float>(G::netvars.m_NetVars["DT_CSPlayer"_crc]["m_flLowerBodyYawTarget"_crc]);
	}

	/*
	 * get_simulation_time
	 * Returns the players simulation time
	 */
	float& get_simulation_time()
	{
		return read<float>(G::netvars.m_NetVars["DT_BaseEntity"_crc]["m_flSimulationTime"_crc]);
	}

	/*
	 * get_next_primary_attack
	 * Returns the next primary attack time
	 */
	float& get_next_attack()
	{
		return read<float>(G::netvars.m_NetVars["DT_CSPlayer"_crc]["m_flNextAttack"_crc]);
	}

	/*
	 * get_ragdoll_pos
	 * Returns an array of rag positions
	 */
	std::array<float, 24>& get_ragdoll_pos()
	{
		return read<std::array<float, 24>>(G::netvars.m_NetVars["DT_Ragdoll"_crc]["m_ragPos"_crc]);
	}

	/*
	 * get_pose_paramaters
	 * Returns an array of pose paramaters
	 */
	std::array<float, 24>& get_pose_paramaters()
	{
		return read<std::array<float, 24>>(G::netvars.m_NetVars["DT_CSPlayer"_crc]["m_flPoseParameter"_crc]);
	}

	/*
	 * get_pose_paramater_range
	 * Returns the pose paramater range of the pose paramater index
	 */
	void get_pose_paramater_range(int _index, float& minValue, float& maxValue)
	{
		static auto pose_paramater_range_ptr = G::signature.find_signature("client.dll", "55 8B EC 56 8B F1 83 BE 3C 29 00 00 00 75 14 8B 46 04 8D 4E 04 FF 50 20 85 C0 74 07 8B CE E8 ? ? ? ? 8B 8E 3C 29 00 00 5E 85 C9 74 48 83 39 00 74 43 8B 55 08 85 D2 78 3C 8B 41 04 85 C0 75 12 8B 01 85 C0 74 08");

		reinterpret_cast<bool(__thiscall*)(C_BaseEntity*, int, float&, float&)>(pose_paramater_range_ptr)(this, _index, minValue, maxValue);
	}

	/*
	 * set_pose_paramater
	 * Overwrites the players given pose paramater with the given time
	 */
	void set_pose_paramater(int _index, float p)
	{
		static auto pose_paramater_game_ptr = G::signature.find_signature("client.dll", "55 8B EC 51 56 8B F1 0F 28 C2 57 F3 0F 11 45 FC 83 BE 3C 29 00 00 00 75 19 8B 46 04 8D 4E 04");
		static auto pose_paramater_data_cache_set_ptr = *reinterpret_cast<uintptr_t*>(G::signature.find_signature("client.dll", "8B 35 ? ? ? ? 8B CE 8B 06 FF 90 80 00 00 00 FF 73 04 F3 0F 10 55 FC 8B CF") + 2);

		float flMin, flMax;
		get_pose_paramater_range(_index, flMin, flMax);

		auto scaledValue = (p - flMin) / (flMax - flMin);

		auto dc = *reinterpret_cast<uintptr_t*>(pose_paramater_data_cache_set_ptr);
		auto me = reinterpret_cast<uintptr_t>(this);

		uintptr_t calladdr = pose_paramater_game_ptr;

		__asm
		{
			mov esi, dc
			mov ecx, esi
			mov eax, [esi]
			call[eax + 0x80]
			push _index
			movss xmm2, scaledValue
			mov ecx, me
			call calladdr
			mov eax, [esi]
			mov ecx, esi
			call[eax + 0x84]
		}
	}

	/*
	 * get_tick_base
	 * Returns the players tick base
	 */
	int& get_tick_base()
	{
		return read<int>(G::netvars.m_NetVars["DT_CSPlayer"_crc]["m_nTickBase"_crc]);
	}

	/*
	 * get_hitbox_set
	 * Returns the hitbox set
	 */
	int& get_hitbox_set()
	{
		return read<int>(G::netvars.m_NetVars["DT_BaseAnimating"_crc]["m_nHitboxSet"_crc]);
	}

	/*
	 * can_fire
	 * Returns if you can fire
	 */
	bool can_fire()
	{
		C_BaseWeapon* weapon_handle;

		if ((weapon_handle = get_weapon()) == nullptr)
			return false;

		if (weapon_handle->get_clip_1() < 1)
			return false;

		if (G::interfaces.globaldata->curtime < G::me->get_next_attack() || G::interfaces.globaldata->curtime < weapon_handle->get_next_primary_attack())
			return false;

		//if (weapon_handle->get_index() == WEAPON_REVOLVER && weapon_handle->get_ready_time() > 0 && weapon_handle->get_ready_time() < G::interfaces.globaldata->curtime && G::cmd->buttons & IN_ATTACK)
		//	return false;

		return true;
	}

	/*
	 * is_animating
	 * Returns if the player is animating
	 */
	bool& is_animating()
	{
		return read<bool>(G::netvars.m_NetVars["DT_BaseAnimating"_crc]["m_bClientSideAnimation"_crc]);
	}

	/*
	 * is_self_animating
	 * Returns if the player is self animating
	 */
	bool& is_self_animating()
	{
		return vtable<bool&(__thiscall*)(void*)>(this, IS_SELF_ANIMATING)(this);
	}

	/*
	 * get_shots_fired
	 * Returns the players shots fired
	 */
	int& get_shots_fired()
	{
		return read<int>(G::netvars.m_NetVars["DT_CSPlayer"_crc]["m_iShotsFired"_crc]);
	}

	/*
	 * has_helmet
	 * Returns if the player has a helmet
	 */
	bool& has_helmet()
	{
		return read<bool>(G::netvars.m_NetVars["DT_CSPlayer"_crc]["m_bHasHelmet"_crc]);
	}

	/*
	 * has_attackable_weapon
	 * Returns if the player has an attackable weapon
	 */
	bool has_attackable_weapon()
	{
		auto weapon_type = get_weapon()->get_weapon_data()->m_weapon_type;

		return weapon_type == WEAPONTYPE_MACHINEGUN || weapon_type == WEAPONTYPE_PISTOL || weapon_type == WEAPONTYPE_RIFLE || weapon_type == WEAPONTYPE_SHOTGUN || weapon_type == WEAPONTYPE_SNIPER_RIFLE || weapon_type == WEAPONTYPE_SUBMACHINEGUN;
	}

	/*
	 * get_model
	 * Returns the players model
	 */
	C_Model* get_model()
	{
		auto renderable = get_renderable();

		return vtable<C_Model*(__thiscall*)(void*)>(renderable, GET_MODEL)(renderable);
	}

	/*
	 * force_bone_recalculation
	 * Forces all bones and hitboxes for the specific player to be recalculated so that pvs will be void.
	 */
	void force_bone_recalculation()
	{
		/*
			string: "current: %d" = C_CSPlayer::ClientThink
			scroll down to a call = C_CSPlayer::ReevauluateAnimLOD

			0xA30 = last_occlusiontime
			0xA28 = occlusion_flags
		*/

		write<int>(0xA30, G::interfaces.globaldata->framecount); // last_occlusiontime
		write<int>(0xA28, 0); // m_bCanUseFastPath
		write<int>(G::netvars.m_NetVars["DT_BaseAnimating"_crc]["m_nForceBone"_crc] + 0x20, 0); // writable bones
		write<int>(G::netvars.m_NetVars["DT_BaseAnimating"_crc]["m_nForceBone"_crc] + 0x4, -1); // m_iMostRecentModelBoneCounter
	}

	/*
	 * update_clientside_animations
	 * Forces the client to be reanimated
	 */
	void update_clientside_animations()
	{
		return vtable<void(__thiscall*)(void*)>(this, UPDATE_CLIENTSIDE_ANIMATIONS)(this);
	}

	/*
	 * client_side_animation
	 * Returns if client sided animation
	 */
	bool& client_side_animation()
	{
		return read<bool>(G::netvars.m_NetVars["DT_BaseAnimating"_crc]["m_bClientSideAnimation"_crc]);
	}

	/*
	 * get_hitbox_handle
	 * Returns the hitbox handle
	 */
	studio_hitbox_set* get_hitbox_handle(Matrix3x4 matrix[128])
	{
		force_bone_recalculation(); // Fixes pvs related issues & invalidates cache

		if (!setup_bones(matrix, 128, 0x100, G::interfaces.globaldata->curtime))
			return nullptr;

		auto model = get_model();

		if (model == nullptr)
			return nullptr;

		auto studio = G::interfaces.modelinfo->get_studio_model(model);

		if (studio == nullptr)
			return nullptr;

		auto hitbox_set = studio->get_hitboxset(get_hitbox_set());

		if (hitbox_set == nullptr)
			return nullptr;

		return hitbox_set;
	}

	/*
	 * get_hitbox_position
	 * Returns the players hitbox position
	 */
	Vector3 get_hitbox_position(int _hitbox)
	{
		Matrix3x4 matrix[128];

		auto hitbox_handle = get_hitbox_handle(matrix);

		if (hitbox_handle == nullptr)
			return Vector3();

		return G::math.calc_hitbox(matrix, hitbox_handle->get_hitbox(_hitbox));
	}

	/*
	 * is_alive
	 * Returns if the player is alive
	 */
	bool is_alive()
	{
		return get_health() > 0;
	}

	/*
	 * is_dormant
	 * Returns if the player is dormant
	 */
	bool is_dormant()
	{
		auto network = get_networkable();

		return vtable<bool(__thiscall*)(void*)>(network, IS_DORMANT)(network);
	}

	/*
	 * is_bot
	 * Returns if the player is a bot
	 */
	bool is_bot()
	{
		return get_info().guid == static_cast<std::string>("BOT");
	}

	/*
	 * is_thirdperson
	 * Returns if the player is thirdperson
	 */
	static bool is_thirdperson()
	{
		return *reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(G::interfaces.cmdinput) + 0xA5);
	}

	/*
	 * is_spawn_protected
	 * Returns if the player is spawn protected
	 */
	bool& is_spawn_protected()
	{
		return read<bool>(G::netvars.m_NetVars["DT_CSPlayer"_crc]["m_bGunGameImmunity"_crc]);
	}

	/*
	 * setup_bones
	 * Sets up the players bones to that they be accessed
	 */
	bool setup_bones(Matrix3x4* bone, int max, int mask, float seed)
	{
		auto renderable = get_renderable();

		return vtable<bool(__thiscall*)(void*, Matrix3x4*, int, int, float)>(renderable, SETUP_BONES)(renderable, bone, max, mask, seed);
	}
};
