// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * get_move_angle
 * Returns the movement angle from the current speed
 */
float C_Movement::get_move_angle(float speed) const
{
	auto move_angle = G::math.rad_2_deg(asin(15.f / speed));

	if (!isfinite(move_angle) || move_angle > 90.f)
		move_angle = 90.f;
	else if (move_angle < 0.f)
		move_angle = 0.f;

	return move_angle;
}

/*
 * get_closest_plane
 * Returns the closest plane
 */
bool C_Movement::get_closest_plane(Vector3* plane) const
{
	C_Trace trace;
	C_TraceFilter filter(G::me, TRACE_WORLD_ONLY);

	auto start = G::me->get_origin(), mins = G::me->get_obbmins(), maxs = G::me->get_obbmaxs();

	Vector3 planes;
	auto count = 0;

	for (auto step = 0.f; step <= PI * 2.f; step += PI / 10.f)
	{
		auto end = start;

		end.x += cos(step) * 64.f;
		end.y += sin(step) * 64.f;

		G::interfaces.trace->trace_ray(ray(start, end, mins, maxs), mask_playersolid, &filter, &trace);

		if (trace.fraction < 1.f)
		{
			planes += trace.plane.normal;
			count++;
		}
	}

	planes /= count;

	if (planes.z < 0.1f)
	{
		*plane = planes;
		return true;
	}

	return false;
}

/*
 * will_hit_obstacle_in_future
 * Calculates if we will hit anything in the future
 */
bool C_Movement::will_hit_obstacle_in_future(float predict_time, float step) const
{
	static auto sv_gravity = G::interfaces.cvar->find_var("sv_gravity");
	static auto sv_jump_impulse = G::interfaces.cvar->find_var("sv_jump_impulse");

	bool ground = G::me->get_entity_flags() & FL_ONGROUND;
	auto gravity_per_tick = sv_gravity->get_float() * G::interfaces.globaldata->interval_per_tick;

	auto start = G::me->get_origin(), end = start;
	auto velocity = G::me->get_velocity();

	C_Trace trace;
	C_TraceFilter filter(G::me, TRACE_WORLD_ONLY);

	auto predicted_ticks_needed = TIME_TO_TICKS(predict_time);
	auto velocity_rotation_angle = G::math.rad_2_deg(atan2(velocity.y, velocity.x));
	auto ticks_done = 0;

	if (predicted_ticks_needed <= 0)
		return false;

	while (true)
	{
		auto rotation_angle = velocity_rotation_angle + step;

		velocity.x = cos(G::math.deg_2_rad(rotation_angle)) * G::me->get_velocity().length_2d();
		velocity.y = sin(G::math.deg_2_rad(rotation_angle)) * G::me->get_velocity().length_2d();
		velocity.z = ground ? sv_jump_impulse->get_float() : velocity.z - gravity_per_tick;

		end += velocity * G::interfaces.globaldata->interval_per_tick;

		G::interfaces.trace->trace_ray(ray(start, end, G::me->get_obbmins(), G::me->get_obbmaxs()), mask_playersolid, &filter, &trace);

		if (trace.fraction != 1.f && trace.plane.normal.z <= 0.9f || trace.startsolid || trace.allsolid)
			break;

		end = trace.endpos;
		end.z -= 2.f;

		G::interfaces.trace->trace_ray(ray(trace.endpos, end, G::me->get_obbmins(), G::me->get_obbmaxs()), mask_playersolid, &filter, &trace);
		ground = (trace.fraction < 1.f || trace.allsolid || trace.startsolid) && trace.plane.normal.z >= 0.7f;

		if (++ticks_done >= predicted_ticks_needed)
			return false;

		velocity_rotation_angle = rotation_angle;
	}

	return true;
}

/*
 * circle_strafe
 * Attempts to automatically strafe around and through objects.
 */
void C_Movement::circle_strafe(C_UserCmd* cmd, float* circle_yaw)
{
	const auto min_step = 2.25f;
	const auto max_step = 5.f;
	auto velocity_2d = G::me->get_velocity().length_2d();

	auto ideal_strafe = std::clamp(get_move_angle(velocity_2d) * 2.f, min_step, max_step);
	auto predict_time = std::clamp(320.f / velocity_2d, 0.35f, 1.f);

	auto step = ideal_strafe;

	while (true)
	{
		if (!will_hit_obstacle_in_future(predict_time, step) || step > max_step)
			break;

		step += 0.2f;
	}

	if (step > max_step)
	{
		step = ideal_strafe;

		while (true)
		{
			if (!will_hit_obstacle_in_future(predict_time, step) || step < -min_step)
				break;

			step -= 0.2f;
		}

		if (step < -min_step)
		{
			Vector3 plane;
			if (get_closest_plane(&plane))
				step = -G::math.normalize_angle(*circle_yaw - G::math.rad_2_deg(atan2(plane.y, plane.x))) * 0.1f;
		}
		else
			step -= 0.2f;
	}
	else
		step += 0.2f;

	G::original_cmd.viewangles.y = *circle_yaw = G::math.normalize_angle(*circle_yaw + step);
	G::original_cmd.move.y = copysign(450.f, -step);
}

/*
 * strafe
 */
void C_Movement::strafe(C_UserCmd* cmd)
{
	if (!G::settings.misc_autostrafer)
		return;

	static auto switch_key = 1.f;
	static auto circle_yaw = 0.f;
	static auto old_yaw = 0.f;

	auto velocity = G::me->get_velocity();
	velocity.z = 0.f;

	auto speed = velocity.length_2d();
	auto ideal_strafe = get_move_angle(speed);

	switch_key *= -1.f;

	if (G::me->get_move_type() == MOVETYPE_WALK && !(G::me->get_entity_flags() & FL_ONGROUND && !(G::original_cmd.buttons & IN_JUMP)))
	{
		if (G::settings.misc_circlestrafer && GetAsyncKeyState('V'))
		{
			circle_strafe(cmd, &circle_yaw);
			return;
		}

		if (G::original_cmd.move.x > 0.f)
			G::original_cmd.move.x = 0.f;

		auto yaw_delta = G::math.normalize_angle(G::original_cmd.viewangles.y - old_yaw);
		auto absolute_yaw_delta = abs(yaw_delta);

		circle_yaw = old_yaw = G::original_cmd.viewangles.y;

		if (yaw_delta > 0.f)
			G::original_cmd.move.y = -450.f;
		else if (yaw_delta < 0.f)
			G::original_cmd.move.y = 450.f;

		if (absolute_yaw_delta <= ideal_strafe || absolute_yaw_delta >= 30.f)
		{
			Angle velocity_angles;
			G::math.vector_angles(velocity, velocity_angles);

			auto velocity_delta = G::math.normalize_angle(G::original_cmd.viewangles.y - velocity_angles.y);
			auto retrack = 2.f * (ideal_strafe * 2.f);

			if (velocity_delta <= retrack || speed <= 15.f)
			{
				if (-retrack <= velocity_delta || speed <= 15.f)
				{
					G::original_cmd.viewangles.y += ideal_strafe * switch_key;
					G::original_cmd.move.y = switch_key * 450.f;
				}
				else
				{
					G::original_cmd.viewangles.y = velocity_angles.y - retrack;
					G::original_cmd.move.y = 450.f;
				}
			}
			else
			{
				G::original_cmd.viewangles.y = velocity_angles.y + retrack;
				G::original_cmd.move.y = -450.f;
			}
		}
	}
}

/*
 * fix_movement
 * Fixes the players movement and returns the correct walk data
 */
Vector3 C_Movement::fix_movement(C_UserCmd* cmd, C_UserCmd original_command) const
{
	Vector3 wish_forward, wish_right, wish_up, cmd_forward, cmd_right, cmd_up;

	auto viewangles = cmd->viewangles;
	auto movedata = original_command.move;
	viewangles.normalize();

	if (!(G::me->get_entity_flags() & FL_ONGROUND) && viewangles.r != 0.f)
		movedata.y = 0.f;

	G::math.angle_vectors(original_command.viewangles, &wish_forward, &wish_right, &wish_up);
	G::math.angle_vectors(viewangles, &cmd_forward, &cmd_right, &cmd_up);

	auto v8 = sqrt(wish_forward.x * wish_forward.x + wish_forward.y * wish_forward.y), v10 = sqrt(wish_right.x * wish_right.x + wish_right.y * wish_right.y), v12 = sqrt(wish_up.z * wish_up.z);

	Vector3 wish_forward_norm(1.0f / v8 * wish_forward.x, 1.0f / v8 * wish_forward.y, 0.f),
			wish_right_norm(1.0f / v10 * wish_right.x, 1.0f / v10 * wish_right.y, 0.f),
			wish_up_norm(0.f, 0.f, 1.0f / v12 * wish_up.z);

	auto v14 = sqrt(cmd_forward.x * cmd_forward.x + cmd_forward.y * cmd_forward.y), v16 = sqrt(cmd_right.x * cmd_right.x + cmd_right.y * cmd_right.y), v18 = sqrt(cmd_up.z * cmd_up.z);

	Vector3 cmd_forward_norm(1.0f / v14 * cmd_forward.x, 1.0f / v14 * cmd_forward.y, 1.0f / v14 * 0.0f),
			cmd_right_norm(1.0f / v16 * cmd_right.x, 1.0f / v16 * cmd_right.y, 1.0f / v16 * 0.0f),
			cmd_up_norm(0.f, 0.f, 1.0f / v18 * cmd_up.z);

	auto v22 = wish_forward_norm.x * movedata.x, v26 = wish_forward_norm.y * movedata.x, v28 = wish_forward_norm.z * movedata.x, v24 = wish_right_norm.x * movedata.y, v23 = wish_right_norm.y * movedata.y, v25 = wish_right_norm.z * movedata.y, v30 = wish_up_norm.x * movedata.z, v27 = wish_up_norm.z * movedata.z, v29 = wish_up_norm.y * movedata.z;

	Vector3 correct_movement;
	correct_movement.x = cmd_forward_norm.x * v24 + cmd_forward_norm.y * v23 + cmd_forward_norm.z * v25
			+ (cmd_forward_norm.x * v22 + cmd_forward_norm.y * v26 + cmd_forward_norm.z * v28)
			+ (cmd_forward_norm.y * v30 + cmd_forward_norm.x * v29 + cmd_forward_norm.z * v27);
	correct_movement.y = cmd_right_norm.x * v24 + cmd_right_norm.y * v23 + cmd_right_norm.z * v25
			+ (cmd_right_norm.x * v22 + cmd_right_norm.y * v26 + cmd_right_norm.z * v28)
			+ (cmd_right_norm.x * v29 + cmd_right_norm.y * v30 + cmd_right_norm.z * v27);
	correct_movement.z = cmd_up_norm.x * v23 + cmd_up_norm.y * v24 + cmd_up_norm.z * v25
			+ (cmd_up_norm.x * v26 + cmd_up_norm.y * v22 + cmd_up_norm.z * v28)
			+ (cmd_up_norm.x * v30 + cmd_up_norm.y * v29 + cmd_up_norm.z * v27);

	correct_movement.x = std::clamp(correct_movement.x, -450.f, 450.f);
	correct_movement.y = std::clamp(correct_movement.y, -450.f, 450.f);
	correct_movement.z = std::clamp(correct_movement.z, -320.f, 320.f);

	return correct_movement;
}
