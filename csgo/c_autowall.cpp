// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

float C_AutoWall::hitgroup_damage(int hitgroup)
{
	switch (hitgroup)
	{
		case hitgroup_head:
			return 4.f;
		case hitgroup_stomach:
			return 1.25f;
		case hitgroup_leftleg:
		case hitgroup_rightleg:
			return 0.75f;
		default:
			return 1.f;
	}
}

void C_AutoWall::scale_damage(int hitgroup, C_BaseEntity* ent, float weapon_armor_ratio, float& current_damage)
{
	auto armor = static_cast<float>(ent->get_armor());

	current_damage *= hitgroup_damage(hitgroup);

	if (armor > 0.f && hitgroup < hitgroup_leftleg)
	{
		if (hitgroup == hitgroup_head && !ent->has_helmet())
			return;

		auto scaled = weapon_armor_ratio * .5f * current_damage;

		if ((current_damage - scaled) * .5f > armor)
			scaled = current_damage - armor * 2.f;

		current_damage = scaled;
	}
}

bool C_AutoWall::trace_to_exit(Vector3& end, Vector3 start, Vector3 dir, C_Trace* enter_trace, C_Trace* exit_trace)
{
	auto distance = 0.f;

	while (distance <= 90.f)
	{
		distance += 4.f;
		end = start + dir * distance;
		auto a1 = end - dir * 4.f;

		auto point_contents = G::interfaces.trace->get_point_contents(end, mask_shot_hull | contents_hitbox, nullptr);
		if (point_contents & mask_shot_hull && !(point_contents & contents_hitbox))
			continue;

		G::interfaces.trace->trace_ray(ray(end, a1), mask_shot_hull | contents_hitbox, nullptr, exit_trace);

		if (exit_trace->startsolid && exit_trace->surface.flags & surf_hitbox)
		{
			C_TraceFilter filter(exit_trace->ent);
			G::interfaces.trace->trace_ray(ray(end, start), mask_shot_hull, &filter, exit_trace);

			if ((exit_trace->fraction < 1.f || exit_trace->allsolid) && !exit_trace->startsolid)
			{
				end = exit_trace->endpos;
				return true;
			}

			continue;
		}

		if (!exit_trace->did_hit() || exit_trace->startsolid)
		{
			if (enter_trace->ent)
			{
				if (enter_trace->ent != nullptr && enter_trace->ent != G::interfaces.entitylist->get_client_entity(0))
				{
					*exit_trace = *enter_trace;
					exit_trace->endpos = start + dir;
					return true;
				}
			}

			continue;
		}

		if (exit_trace->surface.flags >> 7 & surf_light)
		{
			if (!(enter_trace->surface.flags >> 7 & surf_light))
				continue;
		}

		if (exit_trace->plane.normal.dot(dir) <= 1.f)
		{
			end = end - (dir * (exit_trace->fraction * 4.f));
			return true;
		}
	}

	return false;
}

bool C_AutoWall::handle_bullet_penetration(surface_data* enter_surface, C_Trace* enter_trace, Vector3 direction, Vector3* origin, float range, float penetration, int& penetration_count, float& current_damage)
{
	bool a5 = enter_trace->contents >> 3 & contents_solid;
	bool v19 = enter_trace->surface.flags >> 7 & surf_light;

	auto enter_material = enter_surface->game.material;

	Vector3 end;
	C_Trace exit_trace;

	if (!penetration_count && !a5 && !v19 && enter_material != CHAR_TEX_GLASS)
	{
		if (enter_material != CHAR_TEX_GRATE)
			return false;
	}

	if (penetration_count <= 0)
		return false;

	if (!trace_to_exit(end, enter_trace->endpos, direction, enter_trace, &exit_trace))
	{
		if (!(G::interfaces.trace->get_point_contents(end, mask_shot_hull, nullptr) & mask_shot_hull))
			return false;
	}

	auto exit_surfce_data = G::interfaces.physicssurface->get_surface_data(exit_trace.surface.surface_props);
	auto damage_modifier = 0.16f;
	auto average_penetration_modifier = (enter_surface->game.penetrationmodifier + exit_surfce_data->game.penetrationmodifier) / 2;

	if (enter_material == CHAR_TEX_GRATE || enter_material == CHAR_TEX_GLASS)
	{
		damage_modifier = 0.05f;
		average_penetration_modifier = 3.f;
	}

	else if (a5 || v19)
	{
		damage_modifier = 0.16f;
		average_penetration_modifier = 1.f;
	}

	if (enter_material == exit_surfce_data->game.material)
	{
		if (exit_surfce_data->game.material == CHAR_TEX_WOOD || exit_surfce_data->game.material == CHAR_TEX_CARDBOARD)
			average_penetration_modifier = 3.f;

		if (exit_surfce_data->game.material == CHAR_TEX_PLASTIC)
			average_penetration_modifier = 2.f;
	}

	auto modifier = fmaxf(0.f, 1.f / average_penetration_modifier);
	auto penetration_length = (exit_trace.endpos - enter_trace->endpos).length();
	auto taken_damage = modifier * 3.f * fmaxf(0.f, 3.f / penetration * 1.25f) + current_damage * damage_modifier + penetration_length * penetration_length * modifier / 24.f;

	current_damage -= fmaxf(0.f, taken_damage);

	if (current_damage < 1.f)
		return false;

	*origin = exit_trace.endpos;

	--penetration_count;

	return true;
}

void C_AutoWall::util_clip_trace_to_players_rebuilt(Vector3 end, Vector3 start, C_Trace* oldtrace, C_BaseEntity* ent)
{
	auto mins = ent->get_obbmins(), maxs = ent->get_obbmaxs();

	auto dir(end - start);
	dir.normalize();

	auto center = (maxs + mins) / 2;
	auto pos(center + ent->get_origin());

	auto to = pos - start;
	auto range_along = dir.dot(to);

	float range;
	if (range_along < 0.f)
		range = -to.length();

	else if (range_along > dir.length())
		range = -(pos - end).length();

	else
	{
		auto ray(pos - (dir * range_along + start));
		range = ray.length();
	}

	if (range <= 60.f)
	{
		C_Trace trace;
		G::interfaces.trace->clip_ray_to_entity(ray(start, end), mask_shot_hull | contents_hitbox, ent, &trace);

		if (oldtrace->fraction > trace.fraction)
			*oldtrace = trace;
	}
}

bool C_AutoWall::invoke(Vector3 position, C_BaseEntity* entity, bool head, int mindmg, bool& penetrated) const
{
	// compiler thinks its funny to do 'sub esp, 0xC' instead of 'add esp, 0xC'
	static auto util_clip_trace_to_players = [](const Vector3& start, const Vector3& end, uint32_t mask, C_TraceFilter* filter, C_Trace* tr)
			{
				static auto calladdr = G::signature.find_signature("client.dll", "53 8B DC 83 EC 08 83 E4 F0 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 81 EC ? ? ? ? 8B 43 10");
				__asm
				{
					push tr
					push filter
					push mask
					lea edx, end
					lea ecx, start
					call calladdr
					add esp, 0xC
				}
			};

	auto weapon = G::me->get_weapon();
	if (weapon == nullptr)
		return false;

	auto weapon_info = weapon->get_weapon_data();
	if (weapon_info == nullptr)
		return false;

	G::autowall_damage = static_cast<float>(weapon_info->m_damage);

	auto start = G::me->get_eye_origin();
	auto direction(position - start);
	direction.normalize();

	auto hits_left = 4;
	auto trace_length = 0.f;

	C_Trace trace;
	C_TraceFilter filter(G::me);

	while (G::autowall_damage > 0.f)
	{
		auto trace_length_remaining = weapon_info->m_range - trace_length;
		auto end = start + direction * trace_length_remaining;

		G::interfaces.trace->trace_ray(ray(start, end), mask_shot_hull | contents_hitbox, &filter, &trace);

		if (head)
			util_clip_trace_to_players_rebuilt(end + direction * 40.f, start, &trace, entity);
		else
			util_clip_trace_to_players(start, end + direction * 40.f, mask_shot_hull | contents_hitbox, &filter, &trace);

		if (trace.fraction == 1.f)
			break;

		trace_length += trace.fraction * trace_length_remaining;
		G::autowall_damage *= pow(weapon_info->m_range_modifier, trace_length / 500);

		if (trace.hitgroup > hitgroup_generic && trace.hitgroup <= hitgroup_rightleg && trace.ent != nullptr && entity == trace.ent)
		{
			scale_damage(trace.hitgroup, entity, weapon_info->m_armor_ratio, G::autowall_damage);
			penetrated = hits_left != 4;

			return G::autowall_damage >= mindmg;
		}

		auto enter_surface_data = G::interfaces.physicssurface->get_surface_data(trace.surface.surface_props);

		if (trace_length > 3000.f || enter_surface_data->game.penetrationmodifier < 0.1f)
			hits_left = 0;

		if (!handle_bullet_penetration(enter_surface_data, &trace, direction, &start, weapon_info->m_range, weapon_info->m_penetration, hits_left, G::autowall_damage))
			break;
	}

	return false;
}
