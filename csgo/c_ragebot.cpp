// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * can_hit_hitbox
 * Returns if you can hit the hitbox
 */
bool C_RageBot::can_hit_hitbox(C_BaseEntity* entity, Vector3 hitbox_position, int hitbox)
{
	if (entity == nullptr)
		return false;

	auto can_trace_to_hitbox = [](C_BaseEntity* _entity, Vector3 _hitbox_position, int _hitbox)
			{
				C_Trace trace;
				C_TraceFilter trace_filter(G::me, TRACE_EVERYTHING);

				G::interfaces.trace->trace_ray(ray(G::me->get_eye_origin(), _hitbox_position), mask_shot_hull | contents_hitbox, &trace_filter, &trace);

				return (trace.fraction > 0.97f || trace.ent == _entity) && trace.hitbox == _hitbox;
			};

	auto can_trace_to = [](C_BaseEntity* _entity, Vector3 _hitbox_position)
			{
				C_Trace trace;
				C_TraceFilter trace_filter(G::me, TRACE_EVERYTHING);

				G::interfaces.trace->trace_ray(ray(G::me->get_eye_origin(), _hitbox_position), mask_shot_hull, &trace_filter, &trace);

				return trace.fraction > 0.97f || trace.ent == _entity;
			};

	auto penetrated_wall = false;
	auto can_hit = false;

	if (hitbox == hitbox_head)
		can_hit = can_trace_to_hitbox(entity, hitbox_position, hitbox);
	else
		can_hit = can_trace_to(entity, hitbox_position);

	if (G::settings.rage_autowall == 1)
		G::settings.rage_minpenetration = G::me->get_weapon()->get_weapon_data()->m_damage / 2;

	if (!can_hit)
		can_hit = G::settings.rage_autowall != 0 && G::hooks.createmove.ragebot->autowall.invoke(hitbox_position, entity, hitbox == hitbox_head, G::settings.rage_minpenetration, penetrated_wall);

	return can_hit;
}

/*
 * get_best_target
 * Returns the best target to aimbot
 */
ragebot_record C_RageBot::get_best_target(C_UserCmd* cmd) const
{
	ragebot_record record;
	std::vector<C_BaseEntity*> ent_list;

	for (auto i = 1; i < G::interfaces.globaldata->max_clients; i++)
	{
		auto entity = G::interfaces.entitylist->get_client_entity(i);

		if (!can_aimbot_player(entity))
			continue;

		ent_list.push_back(entity);
	}

	auto get_closest_entity = [&]() -> ragebot_record
			{
				auto final_distance = G::me->get_weapon()->get_weapon_data()->m_range;
				auto my_origin = G::me->get_eye_origin();
				ragebot_record _record;

				for (auto entity : ent_list)
				{
					float there_distance;
					if ((there_distance = my_origin.distance(entity->get_eye_origin())) < final_distance)
					{
						auto there_hitbox_position = get_entity_hitbox(entity);

						if (!there_hitbox_position.empty())
						{
							final_distance = there_distance;
							_record.success = true;
							_record.entity = entity;
							_record.aim_position = there_hitbox_position;
						}
					}
				}

				return _record;
			};

	auto get_random_entity = [&]() -> ragebot_record
			{
				auto final_distance = G::me->get_weapon()->get_weapon_data()->m_range;
				auto my_origin = G::me->get_eye_origin();

				std::vector<ragebot_record> rand_ents;

				for (auto entity : ent_list)
				{
					ragebot_record _record;
					if (my_origin.distance(entity->get_eye_origin()) < final_distance)
					{
						auto there_hitbox_position = get_entity_hitbox(entity);

						if (!there_hitbox_position.empty())
						{
							_record.success = true;
							_record.entity = entity;
							_record.aim_position = there_hitbox_position;
						}
					}

					rand_ents.push_back(_record);
				}

				ragebot_record _record;

				std::random_device rd;
				std::mt19937 g(rd());
				shuffle(rand_ents.begin(), rand_ents.end(), g);

				return !rand_ents.empty() ? rand_ents.at(0) : _record;
			};

	switch (G::settings.rage_method)
	{
		case 0:
			record = get_closest_entity();
			break;
		case 1:
			record = get_random_entity();
			break;
		default:
			record = get_closest_entity();
			break;
	}

	return record;
}

/*
 * get_entity_hitbox
 * Returns the entities hitbox
 */
Vector3 C_RageBot::get_entity_hitbox(C_BaseEntity* entity, int* hitbox)
{
	if (!can_aimbot_player(entity) || G::me->get_weapon() == nullptr)
		return Vector3();

	if (G::settings.rage_positionadjustment != 0 && !G::player_lag_records[entity->get_index() - 1].being_lag_compensated)
		return G::player_lag_records[entity->get_index() - 1].hitbox_position;

	std::vector<int> test_hitboxes;

	if (G::settings.rage_smart_aim && G::me->get_weapon()->get_weapon_data()->m_damage >= entity->get_health())
		test_hitboxes.push_back(hitbox_pelvis);

	test_hitboxes.push_back(G::settings.rage_hitbox);

	if (G::settings.rage_hitscan != 0 && !test_hitboxes.empty())
	{
		auto head_hitbox = test_hitboxes.at(0);

		if (G::settings.rage_hitscan > 0)
		{
			if (head_hitbox != hitbox_head)
				test_hitboxes.push_back(hitbox_head);

			if (head_hitbox != hitbox_pelvis)
				test_hitboxes.push_back(hitbox_pelvis);

			if (head_hitbox != hitbox_l_forearm)
				test_hitboxes.push_back(hitbox_l_forearm);

			if (head_hitbox != hitbox_r_forearm)
				test_hitboxes.push_back(hitbox_r_forearm);
		}

		if (G::settings.rage_hitscan > 1)
		{
			if (head_hitbox != hitbox_l_calf)
				test_hitboxes.push_back(hitbox_l_calf);

			if (head_hitbox != hitbox_r_calf)
				test_hitboxes.push_back(hitbox_r_calf);

			if (head_hitbox != hitbox_l_foot)
				test_hitboxes.push_back(hitbox_l_foot);

			if (head_hitbox != hitbox_r_foot)
				test_hitboxes.push_back(hitbox_r_foot);
		}
	}

	Matrix3x4 matrix[128];
	auto hitbox_handle = entity->get_hitbox_handle(matrix);

	if (hitbox_handle == nullptr)
		return Vector3();

	for (auto current_hitbox : test_hitboxes)
	{
		auto bbox = hitbox_handle->get_hitbox(current_hitbox);
		auto hitbox_position = G::math.calc_hitbox(matrix, bbox);

		if (current_hitbox == hitbox_head)
			hitbox_position = resolve_entity(entity, hitbox_position);

		if (can_hit_hitbox(entity, hitbox_position, current_hitbox))
		{
			if (hitbox != nullptr)
				*hitbox = current_hitbox;

			return hitbox_position;
		}

		if (G::settings.rage_multipoint == 1 && current_hitbox == hitbox_head || G::settings.rage_multipoint == 2)
		{
			auto pointscale = static_cast<float>(G::settings.rage_pointscale) / 100.f;

			std::vector<Vector3> scan_points;

			if (bbox->m_radius == -1.f) // box based
			{
				scan_points.push_back(Vector3(bbox->m_mins.x, bbox->m_mins.y, bbox->m_mins.z) * pointscale);
				scan_points.push_back(Vector3(bbox->m_mins.x, bbox->m_maxs.y, bbox->m_mins.z) * pointscale);
				scan_points.push_back(Vector3(bbox->m_maxs.x, bbox->m_maxs.y, bbox->m_mins.z) * pointscale);
				scan_points.push_back(Vector3(bbox->m_maxs.x, bbox->m_mins.y, bbox->m_mins.z) * pointscale);
				scan_points.push_back(Vector3(bbox->m_mins.x, bbox->m_mins.y, bbox->m_maxs.z) * pointscale);
				scan_points.push_back(Vector3(bbox->m_mins.x, bbox->m_maxs.y, bbox->m_maxs.z) * pointscale);
				scan_points.push_back(Vector3(bbox->m_maxs.x, bbox->m_maxs.y, bbox->m_maxs.z) * pointscale);
				scan_points.push_back(Vector3(bbox->m_maxs.x, bbox->m_mins.y, bbox->m_maxs.z) * pointscale);
			}
			else if (bbox->m_radius > 0.f) // pill based
			{
				auto length = (bbox->m_mins - bbox->m_maxs).length() + bbox->m_radius * 2.f;

				scan_points.push_back(hitbox_position + Vector3(length / 2, 0.f, 0.f)); // top
				scan_points.push_back(hitbox_position - Vector3(length / 2, 0.f, 0.f)); // bottom

				scan_points.push_back(hitbox_position + Vector3(0.f, bbox->m_radius * pointscale, 0.f)); // front center ( nose )
				scan_points.push_back(hitbox_position - Vector3(0.f, bbox->m_radius * pointscale, 0.f)); // back center ( occiput )

				scan_points.push_back(hitbox_position + Vector3(0.f, 0.f, bbox->m_radius * pointscale)); // right center ( right ear )
				scan_points.push_back(hitbox_position - Vector3(0.f, 0.f, bbox->m_radius * pointscale)); // left center ( left ear )
			}

			for (auto current_point : scan_points)
			{
				if (can_hit_hitbox(entity, current_point, current_hitbox))
				{
					if (hitbox != nullptr)
						*hitbox = current_hitbox;

					return current_point;
				}
			}
		}
	}

	return Vector3();
}

/*
 * get_entity_hitchance
 * Returns the players hitchance
 */
float C_RageBot::get_entity_hitchance(Angle angle, C_BaseEntity* entity) const
{
	if (entity == nullptr || !G::settings.antiban_enabled && G::settings.rage_nospread || G::settings.rage_hitchance == 0)
		return 100;

	C_BaseWeapon* weapon;
	weapon_info* weapon_data;

	if ((weapon = G::me->get_weapon()) == nullptr || (weapon_data = weapon->get_weapon_data()) == nullptr)
		return 0;

	weapon->update_accuracy_penalty();

	Vector3 angle_forward, angle_right, angle_up, eye_position = G::me->get_eye_origin();
	auto weapon_spread = weapon->get_spread(), weapon_cone = weapon->get_cone();
	auto spread_points_hit = 0;

	angle.normalized();
	G::math.angle_vectors(angle /*+ (G::me->get_aim_punch().normalized() * G::interfaces.cvar->find_var("weapon_recoil_scale")->get_float())*/, &angle_forward, &angle_right, &angle_up);

	for (auto i = 1; i <= 256; i++)
	{
		G::math.random_seed(i);

		Angle spread_angle;
		Vector3 bullet_end;
		auto s1 = G::math.random_float(0.f, 1.f), s2 = G::math.random_float(0.f, 2.f * PI), s3 = G::math.random_float(0.f, 1.f), s4 = G::math.random_float(0.f, 2.f * PI), generated_spread = s1 * weapon_spread, generated_cone = s3 * weapon_cone;
		auto spread = Vector3(cos(s2) * generated_spread + cos(s4) * generated_cone, sin(s2) * generated_spread + sin(s4) * generated_cone, 0.f), spread_direction = (angle_forward + angle_right * -spread.x + angle_up * -spread.y).normalized();

		G::math.vector_angles(spread_direction, spread_angle);
		G::math.angle_vectors(angle - (spread_angle - angle), &bullet_end);

		C_Trace trace;

		G::interfaces.trace->clip_ray_to_entity(ray(eye_position, eye_position + bullet_end * weapon_data->m_range), mask_shot, entity, &trace);

		if (trace.ent == entity)
			spread_points_hit += 1;
	}

	return spread_points_hit / 256.f * 100.f;
}

/*
 * resolve_entity
 * Attempts to resolve the entity
 */
Vector3 C_RageBot::resolve_entity(C_BaseEntity* entity, Vector3 location)
{
	if (entity == nullptr || G::settings.rage_resolver == 0)
		return location;

	auto rotate_angle = [](C_BaseEntity* _entity, Vector3 _location, float yaw)
			{
				Vector3 base, rotated;
				G::math.vector_rotate(_location - _entity->get_origin(), Angle(0.f, 360.f - _entity->get_eye_angles().y, 0.f), base);
				G::math.vector_rotate(base, Angle(0.f, yaw, 0.f), rotated);

				return rotated + _entity->get_origin();
			};

	auto player_lag_record = &G::player_lag_records[entity->get_index() - 1];

	if (!player_lag_record->lower_body_yaw_resolved)
		return location;

	return rotate_angle(entity, location, player_lag_record->lower_body_yaw);
}

/*
 * can_aimbot
 * Returns if the player can aimbot
 */
bool C_RageBot::can_aimbot()
{
	return G::me->has_attackable_weapon() && G::settings.rage_aimbot;
}

/*
 * can_aimbot_player
 * Returns if the player can be aimbotted
 */
bool C_RageBot::can_aimbot_player(C_BaseEntity* entity)
{
	if (G::me == nullptr || G::me->get_weapon() == nullptr)
		return false;

	if (entity == nullptr || entity == G::me || !entity->is_alive() || entity->is_dormant() || entity->is_spawn_protected())
		return false;

	if (G::settings.rage_target == 0 || G::settings.rage_target == 1 && entity->get_team() == G::me->get_team() || G::settings.rage_target == 2 && entity->get_team() != G::me->get_team())
		return true;

	return false;
}

/*
 * run
 * Runs the ragebot code
 */
bool C_RageBot::run(C_UserCmd* cmd, bool& send_packet) const
{
	if (!can_aimbot() || G::settings.rage_silent_aim == 2 && G::interfaces.clientstate->client_state->choked_commands >= 14)
		return false;

	G::interfaces.lagcompensation->start_position_adjustment();
	auto best_record = get_best_target(cmd);
	G::interfaces.lagcompensation->finish_position_adjustment();

	if (!best_record.success)
		return false;

	auto entity_index = best_record.entity->get_index() - 1;
	auto aim_direction = G::math.calc_angle(G::me->get_eye_origin(), best_record.aim_position);
	auto can_fire = G::me->can_fire() && get_entity_hitchance(aim_direction, best_record.entity) >= G::settings.rage_hitchance;
	auto attack_button = G::me->get_weapon()->get_index() == WEAPON_REVOLVER ? IN_ATTACK2 : IN_ATTACK;

	auto tick_record = -1;
	if ((G::settings.rage_positionadjustment == 0 || (tick_record = G::player_lag_records[entity_index].tick_count) != -1) && G::settings.rage_autofire && can_fire && G::antiban_data.snap_state == ANTIBAN_AT_DESTINATION)
		cmd->buttons |= attack_button;

	if (cmd->buttons & attack_button || G::antiban_data.snap_state == ANTIBAN_STEPPING)
	{
		cmd->viewangles = aim_direction.normalized();

		if (G::settings.rage_silent_aim == 0)
			G::interfaces.engine->set_viewangles(G::antiban_data.snap_state == ANTIBAN_STEPPING ? G::antiban_data.snap_angle : aim_direction);
		else if (G::antiban_data.snap_state == ANTIBAN_AT_DESTINATION && G::settings.rage_silent_aim == 2)
			send_packet = false;

		if (G::antiban_data.snap_state == ANTIBAN_AT_DESTINATION)
		{
			G::player_shots[entity_index] += 1;

			auto player_record = &G::player_resolve_records[entity_index];

			player_record->shot_angle.p = player_record->resolved_angle.p;
			player_record->yaw_resolver = G::resolve_ticks[entity_index];
			player_record->yaw_lby = player_record->yaw_lby_ran;
			player_record->ticks_lby = G::player_shots[entity_index];
		}

		if (tick_record != -1)
			cmd->tick_count = tick_record;

		return true;
	}

	return false;
}
