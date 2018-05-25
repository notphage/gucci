// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * frame_net_update_end
 * Function where position adjustment takes place
 */
void C_LagCompensation::frame_net_update_end() const
{
	if (G::me == nullptr || !G::me->is_alive() || G::me->get_weapon() == nullptr || G::round_flags == ROUND_STARTING)
	{
		reset();
		return;
	}

	for (auto index = 1; index < G::interfaces.globaldata->max_clients; index++)
	{
		auto entity = G::interfaces.entitylist->get_client_entity(index);

		if (!should_lag_compensate(entity))
		{
			G::player_lag_records[index - 1].records->clear();
			continue;
		}

		fix_animation_data(entity);
		set_interpolation_flags(entity, DISABLE_INTERPOLATION);
		update_player_record_data(entity);

		entity->client_side_animation() = true;
	}
}

/*
 * paint_debug
 */
void C_LagCompensation::paint_debug() const
{
	for (auto index = 1; index < G::interfaces.globaldata->max_clients; index++)
	{
		auto entity = G::interfaces.entitylist->get_client_entity(index);

		if (!should_lag_compensate(entity))
			continue;

		auto player_index = entity->get_index() - 1;
		auto player_record = &G::player_lag_records[player_index];

		for (size_t i = 0; i < player_record->records->size(); i++)
		{
			if (i + 1 > player_record->records->size() - 1)
				break;

			auto record1 = player_record->records->at(i);

			if (is_time_delta_too_large(record1))
				break;

			auto record2 = player_record->records->at(i + 1);

			Vector3 screen1, screen2;

			auto map_conversion1 = G::math.world_2_screen(record1.origin, screen1), map_conversion2 = G::math.world_2_screen(record2.origin, screen2);

			if (!map_conversion1 && !map_conversion2)
				continue;

			srand(i);
			G::interfaces.surface->set_draw_colour(Colour(rand() % 255, rand() % 255, rand() % 255));
			G::interfaces.surface->draw_line(screen1.x, screen1.y, screen2.x, screen2.y);
		}
	}
}

/*
 * should_lag_compensate
 * Returns if the player should be lag compensated
 */
bool C_LagCompensation::should_lag_compensate(C_BaseEntity* entity)
{
	if (G::me == nullptr || G::settings.rage_positionadjustment == 0)
		return false;

	if (!G::hooks.createmove.ragebot->can_aimbot_player(entity))
		return false;

	return true;
}

/*
 * set_interpolation_flags
 * Sets the interpolation flags of the player
 */
void C_LagCompensation::set_interpolation_flags(C_BaseEntity* entity, int flag)
{
	auto var_map = reinterpret_cast<uintptr_t>(entity) + 36; // tf2 = 20
	auto var_map_list_count = *reinterpret_cast<int*>(var_map + 20);

	for (auto index = 0; index < var_map_list_count; index++)
		*reinterpret_cast<uintptr_t*>(*reinterpret_cast<uintptr_t*>(var_map) + index * 12) = flag;
}

/*
 * get_interpolation
 * Returns the interpolation per tick
 */
float C_LagCompensation::get_interpolation()
{
	static auto cl_interp = G::interfaces.cvar->find_var("cl_interp");
	static auto cl_interp_ratio = G::interfaces.cvar->find_var("cl_interp_ratio");
	static auto sv_client_min_interp_ratio = G::interfaces.cvar->find_var("sv_client_min_interp_ratio");
	static auto sv_client_max_interp_ratio = G::interfaces.cvar->find_var("sv_client_max_interp_ratio");
	static auto cl_updaterate = G::interfaces.cvar->find_var("cl_updaterate");
	static auto sv_minupdaterate = G::interfaces.cvar->find_var("sv_minupdaterate");
	static auto sv_maxupdaterate = G::interfaces.cvar->find_var("sv_maxupdaterate");

	auto updaterate = std::clamp(cl_updaterate->get_float(), sv_minupdaterate->get_float(), sv_maxupdaterate->get_float());
	auto lerp_ratio = std::clamp(cl_interp_ratio->get_float(), sv_client_min_interp_ratio->get_float(), sv_client_max_interp_ratio->get_float());
	return std::clamp(lerp_ratio / updaterate, cl_interp->get_float(), 1.0f);
}

/*
 * is_time_delta_too_large
 * Returns if the time delta between now and wish tick is too out
 */
bool C_LagCompensation::is_time_delta_too_large(C_Tick_Record wish_record) const
{
	auto predicted_arrival_tick = TIME_TO_TICKS(G::interfaces.engine->get_avg_latency(0) + G::interfaces.engine->get_avg_latency(1)) + (G::original_cmd.tick_count + G::interfaces.clientstate->client_state->choked_commands + 1);

	auto lerp_time = get_interpolation();
	auto correct = std::clamp(G::interfaces.engine->get_latency(0) + lerp_time, 0.f, 1.f);
	auto lag_delta = correct - TICKS_TO_TIME(predicted_arrival_tick + TIME_TO_TICKS(lerp_time - wish_record.simulation_time + lerp_time));

	return abs(lag_delta) > static_cast<float>(G::settings.rage_positionadjustment_max_history) / 1000.f;
}

/*
 * update_player_record_data
 * Updates a players record data
 */
void C_LagCompensation::update_player_record_data(C_BaseEntity* entity) const
{
	if (entity == nullptr)
		return;

	auto player_index = entity->get_index() - 1;
	auto player_record = &G::player_lag_records[player_index];

	if (entity->get_simulation_time() > 0.f && (player_record->records->empty() || player_record->records->size() > 0 && player_record->records->at(0).simulation_time != entity->get_simulation_time()))
	{
		C_Tick_Record new_record;
		store_record_data(entity, &new_record);

		// Resolver shit
		if (abs(player_record->lower_body_yaw - entity->get_lower_body_yaw()) != 0.f)
		{
			player_record->lower_body_yaw = entity->get_lower_body_yaw();
			player_record->last_lower_body_yaw_last_update = entity->get_simulation_time();
		}

		if (new_record.data_filled)
		{
			player_record->records->push_front(new_record);

			while (player_record->records->size() > LAG_COMPENSATION_TICKS)
				player_record->records->pop_back();
		}
	}
}

/*
 * fix_animation_data
 * Fixes animation data for the entity before they are stored
 */
void C_LagCompensation::fix_animation_data(C_BaseEntity* entity)
{
	if (!should_lag_compensate(entity) || !entity->is_self_animating())
		return;

	auto player_index = entity->get_index() - 1;
	auto player_record = &G::player_lag_records[player_index];

	if (player_record->records->size() < 2)
		return;

	entity->client_side_animation() = true;

	auto old_curtime = G::interfaces.globaldata->curtime;
	auto old_frametime = G::interfaces.globaldata->frametime;
	auto old_ragpos = entity->get_ragdoll_pos();

	G::interfaces.globaldata->curtime = entity->get_simulation_time();
	G::interfaces.globaldata->frametime = G::interfaces.globaldata->interval_per_tick;

	auto player_animation_state = reinterpret_cast<DWORD*>(entity + 0x3894);
	auto player_model_time = reinterpret_cast<int*>(player_animation_state + 112);
	if (player_animation_state != nullptr && player_model_time != nullptr)
		if (*player_model_time == G::interfaces.globaldata->framecount)
			*player_model_time = G::interfaces.globaldata->framecount - 1;

	entity->get_ragdoll_pos() = old_ragpos;
	entity->update_clientside_animations();

	G::interfaces.globaldata->curtime = old_curtime;
	G::interfaces.globaldata->frametime = old_frametime;

	entity->client_side_animation() = false;
}

/*
 * store_record_data
 * Stores a players data into a tick record
 */
void C_LagCompensation::store_record_data(C_BaseEntity* entity, C_Tick_Record* record_data)
{
	if (entity == nullptr)
		return;

	record_data->origin = entity->get_origin();
	record_data->abs_origin = entity->get_abs_origin();
	record_data->velocity = entity->get_velocity();
	record_data->object_mins = entity->get_obbmins();
	record_data->object_maxs = entity->get_obbmaxs();
	record_data->eye_angles = entity->get_eye_angles();
	record_data->abs_eye_angles = entity->get_abs_eye_angles();
	record_data->sequence = entity->get_sequence();
	record_data->entity_flags = entity->get_entity_flags();
	record_data->simulation_time = entity->get_simulation_time();
	record_data->lower_body_yaw = entity->get_lower_body_yaw();
	record_data->cycle = entity->get_cycle();
	record_data->pose_paramaters = entity->get_pose_paramaters();
	record_data->rag_positions = entity->get_ragdoll_pos();

	record_data->data_filled = true;
}

/*
 * apply_record_data
 * Apply the record data to the entity
 */
void C_LagCompensation::apply_record_data(C_BaseEntity* entity, C_Tick_Record* record_data)
{
	if (entity == nullptr || !record_data->data_filled)
		return;

	entity->get_origin() = record_data->origin;
	entity->get_velocity() = record_data->velocity;
	entity->get_obbmins() = record_data->object_mins;
	entity->get_obbmaxs() = record_data->object_maxs;
	entity->get_eye_angles() = record_data->eye_angles;
	entity->get_abs_eye_angles() = record_data->abs_eye_angles;
	entity->get_sequence() = record_data->sequence;
	entity->get_entity_flags() = record_data->entity_flags;
	entity->get_simulation_time() = record_data->simulation_time;
	entity->get_lower_body_yaw() = record_data->lower_body_yaw;
	entity->get_cycle() = record_data->cycle;
	entity->get_pose_paramaters() = record_data->pose_paramaters;
	entity->get_ragdoll_pos() = record_data->rag_positions;
	entity->set_abs_angles(record_data->abs_eye_angles);
	entity->set_abs_origin(record_data->abs_origin);
}

/*
 * simulate_movement
 * Extrapolates the player forwards a tick
 */
void C_LagCompensation::simulate_movement(C_Simulation_Data* data)
{
	C_Trace trace;
	C_TraceFilter filter(G::me, TRACE_EVERYTHING);

	auto sv_gravity = G::interfaces.cvar->find_var("sv_gravity")->get_int();
	auto sv_jump_impulse = G::interfaces.cvar->find_var("sv_jump_impulse")->get_float(); // math.sqrt(91200) = 301.1
	auto gravity_per_tick = sv_gravity * G::interfaces.globaldata->interval_per_tick;
	auto predicted_origin = data->origin;

	if (data->on_ground)
		data->velocity.z -= gravity_per_tick;

	predicted_origin += data->velocity * G::interfaces.globaldata->interval_per_tick;

	G::interfaces.trace->trace_ray(ray(data->origin, predicted_origin, data->entity->get_obbmins(), data->entity->get_obbmaxs()), contents_solid, &filter, &trace);

	if (trace.fraction == 1.f)
		data->origin = predicted_origin;

	G::interfaces.trace->trace_ray(ray(data->origin, data->origin - Vector3(0.f, 0.f, 2.f), data->entity->get_obbmins(), data->entity->get_obbmaxs()), contents_solid, &filter, &trace);

	data->on_ground = trace.fraction == 0.f;
}

/*
 * predict_player
 * Attempts to predict the player when they have broken lag compensation
 */
void C_LagCompensation::predict_player(C_BaseEntity* entity, C_Tick_Record* current_record, C_Tick_Record* next_record) const
{
	if (!should_lag_compensate(entity))
		return;

	// Create Simulation Data
	C_Simulation_Data simulation_data;

	simulation_data.entity = entity;
	simulation_data.origin = current_record->origin;
	simulation_data.velocity = current_record->velocity;
	simulation_data.on_ground = current_record->entity_flags & FL_ONGROUND;
	simulation_data.data_filled = true;

	// Calculate Delta's
	auto simulation_time_delta = current_record->simulation_time - next_record->simulation_time;
	auto simulation_tick_delta = std::clamp(TIME_TO_TICKS(simulation_time_delta), 1, 15);
	auto delta_ticks = (std::clamp(TIME_TO_TICKS(G::interfaces.engine->get_avg_latency(1) + G::interfaces.engine->get_avg_latency(0)) + G::interfaces.globaldata->tickcount - TIME_TO_TICKS(current_record->simulation_time + get_interpolation()), 0, 100)) - simulation_tick_delta;

	// Calculate movement delta
	auto current_velocity_angle = G::math.rad_2_deg(atan2(current_record->velocity.y, current_record->velocity.x));
	auto next_velocity_angle = G::math.rad_2_deg(atan2(next_record->velocity.y, next_record->velocity.x));
	auto velocity_angle_delta = G::math.normalize_angle(current_velocity_angle - next_velocity_angle);
	auto velocity_movement_delta = velocity_angle_delta / simulation_time_delta;

	if (delta_ticks > 0 && simulation_data.data_filled)
	{
		for (; delta_ticks >= 0; delta_ticks -= simulation_tick_delta)
		{
			auto ticks_left = simulation_tick_delta;

			do
			{
				simulate_movement(&simulation_data);
				current_record->simulation_time += G::interfaces.globaldata->interval_per_tick;

				--ticks_left;
			}
			while (ticks_left);
		}

		current_record->origin = simulation_data.origin;
		current_record->abs_origin = simulation_data.origin;
	}
}

/*
 * get_lowerbodyyaw_update_tick
 * Returns the tick of any lowerbodyyaw
 */
bool C_LagCompensation::get_lowerbodyyaw_update_tick(C_BaseEntity* entity, C_Tick_Record* tick_record, int* record_index) const
{
	if (!should_lag_compensate(entity))
		return false;

	auto player_index = entity->get_index() - 1;
	auto player_record = &G::player_lag_records[player_index];

	for (auto index = 0; index < 8; index++)
	{
		if (index + 1 > player_record->records->size() - 1)
			return false;

		auto current_record = player_record->records->at(index);

		if (current_record.data_filled && !is_time_delta_too_large(current_record) && player_record->last_lower_body_yaw_last_update == current_record.simulation_time)
		{
			*tick_record = current_record;
			*record_index = index;
			return true;
		}
	}

	return false;
}

/*
 * start_lag_compensation
 * Attempts to roll the player back
 */
int C_LagCompensation::start_lag_compensation(C_BaseEntity* entity, int wish_tick, C_Tick_Record* output_record) const
{
	if (!should_lag_compensate(entity))
		return -1;

	auto player_index = entity->get_index() - 1;
	auto player_record = G::player_lag_records[player_index];

	if (player_record.records->empty() || wish_tick + 1 > player_record.records->size() - 1)
		return -1;

	auto current_record = player_record.records->at(wish_tick);
	auto next_record = player_record.records->at(wish_tick + 1);

	if (!current_record.data_filled || !next_record.data_filled || wish_tick > 0 && is_time_delta_too_large(current_record))
		return -1;

	if (wish_tick == 0 && (current_record.origin - next_record.origin).length_sqr() > 4096.f)
		predict_player(entity, &current_record, &next_record);

	if (output_record != nullptr && current_record.data_filled)
		*output_record = current_record;

	return TIME_TO_TICKS(current_record.simulation_time + get_interpolation());
}

/*
 * start_position_adjustment
 * Function where position adjustment is called on everyone
 */
void C_LagCompensation::start_position_adjustment() const
{
	if (G::settings.rage_positionadjustment == 0)
		return;

	for (auto index = 1; index < G::interfaces.globaldata->max_clients; index++)
	{
		auto entity = G::interfaces.entitylist->get_client_entity(index);

		if (!should_lag_compensate(entity))
			continue;

		auto player_record = &G::player_lag_records[entity->get_index() - 1];

		if (player_record->records->size() <= 2)
			return;

		player_record->being_lag_compensated = true;
		start_position_adjustment(entity);
		player_record->being_lag_compensated = false;
	}
}

/*
 * start_position_adjustment
 * Starts position adjustment on the entity given
 */
void C_LagCompensation::start_position_adjustment(C_BaseEntity* entity) const
{
	if (!should_lag_compensate(entity))
		return;

	/*
	* test_and_apply_record
	*/
	auto test_and_apply_record = [](C_BaseEntity* _entity, C_Player_Record* player_record, C_Tick_Record* restore_record, C_Tick_Record* corrected_record, int tick_count, bool lby_resolved) -> bool
			{
				apply_record_data(_entity, corrected_record);
				corrected_record->hitbox_positon = G::hooks.createmove.ragebot->get_entity_hitbox(_entity);
				apply_record_data(_entity, restore_record);

				if (corrected_record->hitbox_positon.empty())
					return false;

				player_record->tick_count = tick_count;
				player_record->eye_angles = corrected_record->eye_angles;
				player_record->hitbox_position = corrected_record->hitbox_positon;
				player_record->lower_body_yaw_resolved = lby_resolved;
				player_record->lower_body_yaw_resolved_yaw = corrected_record->lower_body_yaw;

				return true;
			};

	auto player_index = entity->get_index() - 1;
	auto player_record = &G::player_lag_records[player_index];

	if (player_record->records->empty() || !entity->is_self_animating())
		return;

	player_record->tick_count = -1;
	player_record->hitbox_position.clear();
	player_record->eye_angles.clear();
	player_record->lower_body_yaw_resolved = false;
	player_record->lower_body_yaw_resolved_yaw = 0.f;

	store_record_data(entity, &player_record->restore_record);

	C_Tick_Record lby_record;
	int lby_index;

	// Test if lowerbodyyaw was leaked and is visible
	//if (!(entity->get_entity_flags() & FL_ONGROUND) && get_lowerbodyyaw_update_tick(entity, &lby_record, &lby_index))
	//{
	//	if (lby_record.data_filled)
	//	{
	//		C_Tick_Record corrected_record;

	//		auto tick_count = start_lag_compensation(entity, lby_index, &corrected_record);

	//		if (tick_count != -1 && test_and_a pply_record(entity, player_record, &player_record->restore_record, &corrected_record, tick_count, true))
	//			return;
	//	}
	//}

	// Just normally loop as we would
	for (auto index = 0; index < player_record->records->size(); index++)
	{
		if (index + 1 > player_record->records->size() - 1 || G::settings.rage_positionadjustment == 1 && index > 0)
			break;

		C_Tick_Record corrected_record;
		auto current_record = &player_record->records->at(index);

		auto tick_count = start_lag_compensation(entity, index, &corrected_record);

		if (tick_count == -1 || !corrected_record.data_filled)
			break;

		if (test_and_apply_record(entity, player_record, &player_record->restore_record, &corrected_record, tick_count, false))
			return;
	}
}

/*
 * finish_position_adjustment
 * Function where position adjustment is called on everyone
 */
void C_LagCompensation::finish_position_adjustment() const
{
	if (G::settings.rage_positionadjustment == 0)
		return;

	for (auto index = 1; index < G::interfaces.globaldata->max_clients; index++)
	{
		auto entity = G::interfaces.entitylist->get_client_entity(index);

		if (!should_lag_compensate(entity))
			continue;

		finish_position_adjustment(entity);
	}
}

/*
 * finish_position_adjustment
 * Finishes and cleans up position adjustment
 */
void C_LagCompensation::finish_position_adjustment(C_BaseEntity* entity)
{
	if (!should_lag_compensate(entity))
		return;

	auto player_index = entity->get_index() - 1;
	auto player_record = &G::player_lag_records[player_index];

	if (!player_record->restore_record.data_filled)
		return;

	apply_record_data(entity, &player_record->restore_record);

	player_record->restore_record.data_filled = false; // Set to false so that we dont apply this record again if its not set next time
}

/*
 * reset
 */
void C_LagCompensation::reset()
{
	for (auto i = 0; i < 64; i++)
		G::player_lag_records[i].reset();
}
