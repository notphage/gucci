// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * fast_reload
 * Uses an exploit to reload the weapon slightly faster
 */
void C_Miscellaneous::fast_reload()
{
	if (!G::settings.visuals_fastreload)
		return;

	auto weapon_handle = G::me->get_weapon();

	if (weapon_handle == nullptr)
		return;

	static auto ammo_count = weapon_handle->get_clip_1(), switch_count = 0;

	if (G::reloading_data[0] == 0)
	{
		ammo_count = weapon_handle->get_clip_1();

		if (ammo_count == 0)
		{
			G::reloading_data[0] = 1;
			G::reloading_data[1] = weapon_handle->get_index();
		}

		return;
	}

	if (switch_count == 0 && G::reloading_data[1] == weapon_handle->get_index())
	{
		if (weapon_handle->get_clip_1() != ammo_count)
			switch_count = 1;

		ammo_count = weapon_handle->get_clip_1();
	}

	if (switch_count > 0)
	{
		if (switch_count == 1)
			G::interfaces.engine->client_cmd("lastinv");
		else if (switch_count == 2)
			G::interfaces.engine->client_cmd("lastinv");

		if (weapon_handle->get_index() != G::reloading_data[1])
			switch_count++;
	}

	if (switch_count >= 2 && weapon_handle->get_index() == G::reloading_data[1])
	{
		switch_count = 0;
		G::reloading_data[0] = 0;
		G::reloading_data[1] = 0;
	}
}

/*
 * auto_hop
 * Automatically hops the players movement
 */
void C_Miscellaneous::auto_hop(C_UserCmd* cmd)
{
	if (G::me == nullptr || cmd == nullptr)
		return;

	if (!(G::me->get_entity_flags() & FL_ONGROUND) && cmd->buttons & IN_JUMP && G::settings.misc_autohop)
		cmd->buttons &= ~IN_JUMP;
}

/*
 * buy_weapons
 * Buys weapons for the player
 */
void C_Miscellaneous::buy_weapons()
{
	switch (G::settings.misc_autobuy)
	{
		case 1:
			G::interfaces.engine->client_cmd("buy vest; buy vesthelm; buy defuser; buy molotov; buy incgrenade; buy smokegrenade; buy flashbang");
			break;
		case 2:
			G::interfaces.engine->client_cmd("buy ak47; buy m4a1; buy deagle; buy vest; buy vesthelm;buy defuser; buy molotov; buy incgrenade; buy smokegrenade; buy flashbang");
			break;
		case 3:
			G::interfaces.engine->client_cmd("buy negev; buy deagle; buy vest; buy vesthelm; buy defuser; buy molotov; buy incgrenade; buy smokegrenade; buy flashbang");
			break;
		case 4:
			G::interfaces.engine->client_cmd("buy g3sg1; buy scar20; buy deagle; buy vest; buy vesthelm; buy defuser; buy molotov; buy incgrenade; buy smokegrenade; buy flashbang");
			break;
		case 5:
			G::interfaces.engine->client_cmd("buy awp; buy deagle; buy vest; buy vesthelm; buy defuser; buy molotov; buy incgrenade; buy smokegrenade; buy flashbang");
			break;
		default:
			break;
	}
}

/*
 * get_anti_aim_pitch
 * Returns the anti aim pitch
 */
float C_Miscellaneous::get_anti_aim_pitch(C_UserCmd* cmd, bool& send_packet)
{
	if (G::me == nullptr || cmd == nullptr)
		return cmd->viewangles.p;

	switch (G::settings.rage_antiaim_pitch)
	{
		case 1:
			return 89.f;
		case 2:
			return -89.f;
		case 3:
			return 179.f;
		case 4:
			return -179.f;
		case 5:
			return -991.f;
		case 6:
			return 991.f;
		case 7:
			return 89.7f;
		case 8:
			return G::math.random_float(-89.f, 89.f);
		default:
			return cmd->viewangles.p;
	}
}

/*
 * get_anti_aim_yaw
 * Returns the anti aim yaw
 */
float C_Miscellaneous::get_anti_aim_yaw(C_UserCmd* cmd, bool& send_packet)
{
	if (G::me == nullptr || cmd == nullptr)
		return cmd->viewangles.p;

	auto auto_edge = [](float& yaw, bool& _send_packet) -> bool
			{
				if (G::settings.rage_antiaim_edge_aa == 0)
					return false;

				C_TraceFilter filter(G::me, TRACE_WORLD_ONLY);

				for (auto degree = 0.f; degree < 360.f; degree += 2.f)
				{
					Vector3 degree_forward, start_origin;
					C_Trace trace;

					G::math.angle_vectors(Angle(0.f, degree, 0.f).normalized(), &degree_forward);

					start_origin = G::me->get_origin();
					start_origin.z += 62.f;

					G::interfaces.trace->trace_ray(ray(start_origin, start_origin + degree_forward * 24.f), mask_solid, &filter, &trace);

					if (trace.fraction == 1.f)
						continue;

					Vector3 left_right, right_right;
					Angle plane_angle, degree_change = Angle(0.f, 30.f, 0.f);
					C_Trace left_trace, right_trace;

					G::math.vector_angles(trace.plane.normal * -1.f, plane_angle);
					plane_angle.normalize();

					G::math.angle_vectors(plane_angle + degree_change, &left_right);
					G::math.angle_vectors(plane_angle - degree_change, &right_right);
					G::interfaces.trace->trace_ray(ray(start_origin, start_origin + left_right * 48.f), mask_solid, &filter, &left_trace);
					G::interfaces.trace->trace_ray(ray(start_origin, start_origin + right_right * 48.f), mask_solid, &filter, &right_trace);

					switch (G::settings.rage_antiaim_edge_aa)
					{
						case 1:
							{
								if (left_trace.fraction == 1.f && right_trace.fraction != 1.f)
									plane_angle.y -= 90.f;
								else if (right_trace.fraction == 1.f && left_trace.fraction != 1.f)
									plane_angle.y += 90.f;

								break;
							}
						case 2:
							{
								if (left_trace.fraction == 1.f && right_trace.fraction != 1.f)
									plane_angle.y -= 90.f;
								else if (right_trace.fraction == 1.f && left_trace.fraction != 1.f)
									plane_angle.y += 90.f;

								if (_send_packet)
									plane_angle.y += 180.f;
							}
						default:
							break;
					}

					yaw = plane_angle.normalized().y;

					return true;
				}

				return false;
			};

	auto get_closest_target = []() -> C_BaseEntity*


			
			{
				auto max_distance = 9999.f, max_vis_distance = 9999.f;
				C_BaseEntity *max_distance_ent = nullptr, *max_vis_distance_ent = nullptr;
				auto my_position = G::me->get_eye_origin();

				for (auto i = 1; i < G::interfaces.globaldata->max_clients; i++)
				{
					auto entity = G::interfaces.entitylist->get_client_entity(i);

					if (!G::hooks.createmove.ragebot->can_aimbot_player(entity))
						continue;

					auto vec_distance = my_position.distance(entity->get_eye_origin());

					if (vec_distance < max_distance)
					{
						max_distance = vec_distance;
						max_distance_ent = entity;
					}

					if (vec_distance < max_vis_distance)
					{
						auto trace = G::interfaces.trace->trace(my_position, entity->get_eye_origin(), mask_shot, G::me);
						if (trace.fraction > 0.97f || trace.ent == entity)
						{
							max_vis_distance = vec_distance;
							max_vis_distance_ent = entity;
						}
					}
				}

				if (max_vis_distance_ent != nullptr)
					return max_vis_distance_ent;

				return max_distance_ent;
			};


	auto edge_yaw = 0.f;
	if (auto_edge(edge_yaw, send_packet))
		return edge_yaw;

	auto closest_target = static_cast<C_BaseEntity*>(get_closest_target());
	float at_targets_angle = (closest_target != nullptr && G::settings.rage_antiaim_followtargets ? G::math.calc_angle(G::me->get_eye_origin(), closest_target->get_eye_origin()).normalized().y : cmd->viewangles.normalized().y);

	static auto jitter_send = false, jitter_choke = false;
	auto tick_jitter = send_packet ? jitter_send : jitter_choke;

	send_packet ? jitter_send = !jitter_send : jitter_choke = !jitter_choke;

	switch (send_packet ? G::settings.rage_antiaim_yaw_send : G::settings.rage_antiaim_yaw_choke)
	{
		case 1:
			return at_targets_angle + 180.f;
		case 2:
			return at_targets_angle + 180.f + (send_packet ? 45.f : -45.f);
		case 3:
			return at_targets_angle + 180.f + (tick_jitter ? 35.f : -35.f);
		case 4:
			{
				auto jitter_value = send_packet ? G::settings.rage_antiaim_custom_yaw_send : G::settings.rage_antiaim_custom_yaw_choke;
				return at_targets_angle + G::math.random_float(-jitter_value, jitter_value);
			}
		case 5:
			{
				auto jitter_value = send_packet ? G::settings.rage_antiaim_custom_yaw_send : G::settings.rage_antiaim_custom_yaw_choke;
				return at_targets_angle + 90.f + G::math.random_float(-jitter_value, jitter_value);
			}
		case 6:
			{
				auto jitter_value = send_packet ? G::settings.rage_antiaim_custom_yaw_send : G::settings.rage_antiaim_custom_yaw_choke;
				return at_targets_angle + 180.f + G::math.random_float(-jitter_value, jitter_value);
			}
		case 7:
			return at_targets_angle + (send_packet ? 90.f : -90.f);
		case 8:
			return static_cast<int>(G::interfaces.globaldata->curtime * 360) % 360;
		case 9:
			return static_cast<int>(G::interfaces.globaldata->curtime * 720) % 360;
		case 10:
			return G::me->get_lower_body_yaw() + (send_packet ? G::settings.rage_antiaim_custom_yaw_send : G::settings.rage_antiaim_custom_yaw_choke);
		case 11:
			return at_targets_angle + (send_packet ? G::settings.rage_antiaim_custom_yaw_send : G::settings.rage_antiaim_custom_yaw_choke);
		default:
			return cmd->viewangles.y;
	}
}

/*
 * anti_aim
 * Makes the player hard to hit
 */
void C_Miscellaneous::anti_aim(C_UserCmd* cmd, bool& send_packet)
{
	if (G::me == nullptr || cmd == nullptr || !G::settings.rage_antiaim || G::round_flags == ROUND_STARTING || G::me->get_move_type() == MOVETYPE_LADDER || G::me->get_move_type() == MOVETYPE_NOCLIP || cmd->buttons & IN_USE)
		return;

	auto weapon_handle = G::me->get_weapon();

	// Grenade Can Throw
	if (weapon_handle->is_grenade())
	{
		if (G::settings.antiban_enabled && G::settings.antiban_max_snap != 180)
			return;

		if ((!weapon_handle->was_pin_pulled() || G::cmd->buttons & IN_ATTACK || G::cmd->buttons & IN_ATTACK2) && weapon_handle->get_grenade_throw_time() > 0 && weapon_handle->get_grenade_throw_time() < G::interfaces.globaldata->curtime)
		{
			if (G::settings.rage_silent_aim == 2)
				send_packet = false;

			return;
		}
	}

	cmd->viewangles.p = get_anti_aim_pitch(cmd, send_packet);
	cmd->viewangles.y = get_anti_aim_yaw(cmd, send_packet);
	cmd->viewangles.r = 0.f;
}

/*
 * fake_lag
 * Handles fakelag
 */
void C_Miscellaneous::fake_lag(C_UserCmd* cmd, bool& send_packet)
{
	if (G::me == nullptr || cmd == nullptr || G::settings.misc_fakelag_type == 0 || G::round_flags == ROUND_STARTING || G::me->get_move_type() == MOVETYPE_LADDER || G::me->get_move_type() == MOVETYPE_NOCLIP)
		return;

	static auto packets_choked = 0;

	switch (G::settings.misc_fakelag_type)
	{
		case 1: // Factorial
			{
				send_packet = packets_choked < 1;
				++packets_choked %= G::settings.misc_fakelag_choke + 1;

				break;
			}
		case 2: // Adaptive
			{
				G::breaking_lag_compensation = (G::me->get_origin() - G::last_sent_origin).length_sqr() > 4096.f;

				send_packet = send_packet >= 14 || G::breaking_lag_compensation;
				!send_packet ? ++packets_choked : packets_choked = 0;
				break;
			}
		default:
			break;
	}

	// Lag Jump
	if (G::settings.misc_fakelag_lagjump == 1 && !(G::prediction_data.non_predicted.flags & FL_ONGROUND) && G::me->get_entity_flags() & FL_ONGROUND
		|| G::settings.misc_fakelag_lagjump == 2 && G::prediction_data.non_predicted.flags & FL_ONGROUND && !G::me->get_entity_flags() & FL_ONGROUND)
		send_packet = false;

	if (G::interfaces.clientstate->client_state->choked_commands >= 14 && !send_packet || G::interfaces.clientstate->client_state->choked_commands >= 15)
		send_packet = true;
}

/*
 * accuracy_related
 * Does all accuracy related things
 */
void C_Miscellaneous::accuracy_related(C_UserCmd* cmd)
{
	if (G::me == nullptr || cmd == nullptr || !G::me->has_attackable_weapon())
		return;

	auto no_spread = [](C_UserCmd* _cmd)
			{
				if (G::settings.antiban_enabled)
					return;

				C_BaseWeapon* weapon;

				if ((weapon = G::me->get_weapon()) == nullptr || G::prediction_data.prediction_random_seed == nullptr)
					return;

				G::math.random_seed((*G::prediction_data.prediction_random_seed & 255) + 1);

				auto s1 = G::math.random_float(0.f, 1.f), s2 = G::math.random_float(0.f, 2.f * PI), s3 = G::math.random_float(0.f, 1.f), s4 = G::math.random_float(0.f, 2.f * PI);

				if (weapon->get_index() == WEAPON_REVOLVER && _cmd->buttons & IN_ATTACK2)
				{
					s1 = 1.f - s1 * s1;
					s3 = 1.f - s3 * s3;
				}
				else if (weapon->get_index() == WEAPON_NEGEV && weapon->get_recoil_index() < 3.f)
				{
					for (auto i = 3; i > weapon->get_recoil_index(); i--)
					{
						s1 *= s1;
						s3 *= s3;
					}

					s1 = 1.f - s1;
					s3 = 1.f - s3;
				}

				auto random_spread = s1 * weapon->get_spread();
				auto cone = s3 * weapon->get_cone();

				auto spread = Vector3(sin(s2) * random_spread + sin(s4) * cone, cos(s2) * random_spread + cos(s4) * cone, 0.f);

				_cmd->viewangles.p += G::math.rad_2_deg(atan(spread.length_2d()));
				_cmd->viewangles.r = -G::math.rad_2_deg(atan2(spread.y, spread.x));
			};

	auto no_recoil = [](C_UserCmd* _cmd)
			{
				_cmd->viewangles -= G::me->get_aim_punch() * G::interfaces.cvar->find_var("weapon_recoil_scale")->get_float();
			};

	if (G::settings.rage_nospread)
		no_spread(cmd);

	if (G::settings.rage_norecoil)
		no_recoil(cmd);

	cmd->viewangles.normalize();
}
