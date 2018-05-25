// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * SPOT-SPANKER
 *
 * WRITTEN BY SENATOR
 */

/*
 * resolve_pitch
 * Attempts to resolve the players pitch
 */
bool C_Resolver::resolve_pitch(C_BaseEntity* entity) const
{
	if (entity == nullptr || G::settings.rage_resolver != 2 || !G::interfaces.lagcompensation->should_lag_compensate(entity))
		return false;

	auto index = entity->get_index() - 1;
	auto player_lag_record = &G::player_lag_records[index];
	auto player_resolve_record = &G::player_resolve_records[index];
	auto entity_angles = G::player_resolve_records[index].original_angle;

	auto record1 = player_lag_record->records->at(0), record2 = player_lag_record->records->at(1);

	if (G::player_shots[index] != 0 && player_resolve_record->last_shot_ticks != 0 &&
		abs(G::player_shots[index] - player_resolve_record->last_shot_ticks) <= 1)
		player_resolve_record->resolved_angle.p = player_resolve_record->hit_angle.p;
	else
	{
		player_resolve_record->resolved_angle.p = std::clamp(G::math.normalize_angle(player_resolve_record->resolved_angle.p), -89.f, 89.f);

		if (!(entity->get_entity_flags() & FL_ONGROUND) && record2.entity_flags & FL_ONGROUND && entity_angles.p >= 178.36304f)
			player_resolve_record->resolved_angle.p = -89.f;
		else
		{
			if (abs(entity_angles.p) > 89.f)
				player_resolve_record->resolved_angle.p = G::player_shots[index] % 4 != 3 ? 89.f : -89.f;
			else
				player_resolve_record->resolved_angle.p = G::player_shots[index] % 4 != 3 ? 89.f : player_resolve_record->resolved_angle.p;
		}
	}

	player_resolve_record->last_hit_ticks++;

	return true;
}

/*
 * resolve_yaw
 * Attempts to resolve the players yaw
 */
bool C_Resolver::resolve_yaw(C_BaseEntity* entity) const
{
	if (entity == nullptr || G::settings.rage_resolver == 0 || !G::interfaces.lagcompensation->should_lag_compensate(entity))
		return false;

	auto index = entity->get_index() - 1;
	auto player_lag_record = &G::player_lag_records[index];
	auto player_resolve_record = &G::player_resolve_records[index];

	auto record1 = player_lag_record->records->at(0), record2 = player_lag_record->records->at(1);

	if (abs(TIME_TO_TICKS(record1.simulation_time - record2.simulation_time)) <= 2)
		return false;

	auto entity_angles = player_resolve_record->original_angle;
	auto entity_direction = G::math.calc_angle(entity->get_eye_origin(), G::me->get_eye_origin()).normalized();
	auto lowerbody_update_delta = abs(record1.simulation_time - player_lag_record->last_lower_body_yaw_last_update);

	auto shot_hit_lby_last_tick = G::player_resolve_records[index].yaw_hit_lby && G::player_shots[index] != 0 && player_resolve_record->last_shot_ticks != 0 && abs(G::player_shots[index] - player_resolve_record->last_shot_ticks) <= 1;

	if (shot_hit_lby_last_tick || entity->get_entity_flags() & FL_ONGROUND && (lowerbody_update_delta == 0.f || lowerbody_update_delta < 1.1f && G::player_shots[index] % 2 == 0 || lowerbody_update_delta > 1.1f))
	{
		player_resolve_record->resolved_angle.y = record1.lower_body_yaw + (lowerbody_update_delta < 1.1f ? G::math.random_float(-35.f, 35.f) : 0.f);

		player_resolve_record->yaw_lby_ran = true;

		return true;
	}

	player_resolve_record->yaw_lby_ran = false;

	auto backwards = entity_direction.y + 180.f;

	switch ((G::player_shots[index] != 0 && player_resolve_record->last_shot_ticks != 0 && abs(G::player_shots[index] - player_resolve_record->last_shot_ticks) <= 1 ? player_resolve_record->yaw_hit_resolver : G::resolve_ticks[index]) % 6)
	{
		case 0:
		case 1:
			{
				player_resolve_record->resolved_angle.y = backwards;
				break;
			}

		case 2:
		case 3:
			{
				player_resolve_record->resolved_angle.y = backwards + 90.f;
				break;
			}

		case 4:
		case 5:
			{
				player_resolve_record->resolved_angle.y = backwards - 90.f;
				break;
			}
		default:
			break;
	}

	player_resolve_record->resolved_angle.y += G::math.random_float(-35.f, 35.f);

	return true;
}

/*
 * resolve
 */
float C_Resolver::resolve(C_BaseEntity* entity, int resolve_part) const
{
	if (entity == nullptr || G::settings.rage_resolver == 0 || !G::interfaces.lagcompensation->should_lag_compensate(entity))
		return -1.f;

	auto index = entity->get_index() - 1;
	auto player_record = &G::player_lag_records[index];

	if (player_record->records->empty() || player_record->records->size() < 5)
		return -1.f;

	G::player_resolve_records[index].original_angle[resolve_part] = player_record->tick_count != -1 ? player_record->eye_angles[resolve_part] : entity->get_eye_angles()[resolve_part];
	G::player_resolve_records[index].resolved_angle[resolve_part] = G::player_resolve_records[index].original_angle[resolve_part];

	resolve_part == 0 ? resolve_pitch(entity) : resolve_yaw(entity);

	return G::player_resolve_records[index].resolved_angle[resolve_part];
}

/*
 * fire_game_event
 * Handles all firegame event related information
 */
void C_Resolver::fire_game_event(C_GameEvent* game_event) const
{
	if (Crypto::CRC::crc(game_event->GetName()) == "player_hurt"_crc)
	{
		auto attacker_id = G::interfaces.engine->get_playerforuserid(game_event->GetInt("attacker"));
		auto attacked_id = G::interfaces.engine->get_playerforuserid(game_event->GetInt("userid"));
		auto hitgroup_id = game_event->GetInt("hitgroup");

		if (attacker_id == G::interfaces.engine->get_localplayer() && hitgroup_id == 1)
		{
			auto entity = G::interfaces.entitylist->get_client_entity(attacked_id);

			if (entity != nullptr)
			{
				auto index = entity->get_index() - 1;
				G::player_resolve_records[index].hit_angle = G::player_resolve_records[index].resolved_angle;
				G::player_resolve_records[index].hit_angle.p = G::player_resolve_records[index].shot_angle.p;
				G::player_resolve_records[index].yaw_hit_resolver = G::player_resolve_records[index].yaw_resolver;
				G::player_resolve_records[index].yaw_hit_lby = G::player_resolve_records[index].yaw_lby;
				G::player_resolve_records[index].last_hit_ticks = 0;
				G::player_resolve_records[index].last_shot_ticks = G::player_shots[index];
				G::player_resolve_records[index].shot_ticks_lby = G::player_resolve_records[index].ticks_lby;
			}
		}
	}
}
