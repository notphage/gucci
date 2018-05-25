// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * run
 * Runs the walkbot
 */
void C_WalkBot::run(C_UserCmd* cmd)
{
	static auto key_b_down = false;
	static auto key_b_down2 = false;
	static auto walkbot_enabled = false;
	static auto walkbot_firstmove = true;
	static auto walkbot_reverse = false;
	static size_t walkbot_move_point = 0;
	static auto walkbot_viewangles = 0.f;

	key_b_down = GetAsyncKeyState('X');

	if (key_b_down && !key_b_down2)
		walkbot_enabled = !walkbot_enabled;

	key_b_down2 = key_b_down;

	if (!walkbot_enabled || G::round_flags == ROUND_STARTING)
	{
		walkbot_reverse = false;
		walkbot_firstmove = true;
		walkbot_move_point = 0;
		walkbot_viewangles = G::original_cmd.viewangles.y;
		return;
	}

	std::vector<Vector3> vector_points =
	{
		Vector3(-1264.799438f, 129.866714f, 32.f),
		Vector3(-1257.073364f, 678.287415f, 32.f),
		Vector3(-462.865295f, 790.771912f, 32.f),
		Vector3(-428.725128f, 1221.569946f, 32.f),
		Vector3(-656.718567f, 1456.220581f, 32.f),
		Vector3(-744.038086f, 1517.613525f, 32.f),
		Vector3(-807.416199f, 1743.274292f, 32.f),
		Vector3(-388.207611f, 1808.168457f, 32.f),
		Vector3(327.855133f, 1921.192383f, 32.f),
		Vector3(414.404236f, 1731.821289f, 32.f),
		Vector3(401.393707f, 872.456787f, 32.f),
		Vector3(-532.208435f, 721.651855f, 32.f),
		Vector3(-793.866028f, 120.098541f, 32.f),
	};

	set_track_points(vector_points);

	auto closest_move_point = walkbot_firstmove || !is_point_visible(vector_points.at(walkbot_move_point)) ? get_closest_moveable_point(walkbot_move_point) - 1 : walkbot_move_point;

	if (closest_move_point < 0 || closest_move_point > vector_points.size())
		return;

	if (walkbot_firstmove)
	{
		walkbot_move_point = closest_move_point;
		walkbot_firstmove = false;
	}

	auto vector_closest_move_point = vector_points.at(closest_move_point);
	auto vector_me = G::me->get_abs_origin();
	vector_me.z = 0.f;
	vector_closest_move_point.z = 0.f;

	if (!vector_closest_move_point.empty())
	{
		auto destination = calculate_move_angle(vector_closest_move_point).y;
		auto destination_delta = destination - walkbot_viewangles;
		auto destination_lerp = 15.f;

		if (abs(destination_delta) > destination_lerp)
		{
			if (destination_delta > destination_lerp)
				walkbot_viewangles += destination_lerp;
			else if (destination_delta < -destination_lerp)
				walkbot_viewangles -= destination_lerp;
			else
				walkbot_viewangles = destination;
		}
		else
			walkbot_viewangles = destination;

		// walkbot_viewangles
		G::original_cmd.viewangles.y = walkbot_viewangles;

		if (vector_me.distance(vector_closest_move_point) <= 10)
		{
			if (walkbot_move_point + 1 > vector_points.size() - 1)
				walkbot_reverse = true;
			else if (walkbot_move_point <= 0)
				walkbot_reverse = false;

			if (walkbot_reverse)
				walkbot_move_point--;
			else
				walkbot_move_point++;
		}
	}
}

/*
 * set_track_points
 * Sets the track points for the map data
 */
void C_WalkBot::set_track_points(std::vector<Vector3> vector_map)
{
	G::walkbot_points = vector_map;
}

/*
 * is_point_visible
 * Returns if the point is visible
 */
bool C_WalkBot::is_point_visible(Vector3 vector)
{
	auto trace = G::interfaces.trace->trace(G::me->get_eye_origin(), vector, mask_solid, G::me);
	return trace.fraction > 0.97f;
}

/*
 * get_closest_moveable_point
 * Returns the closest move
 */
int C_WalkBot::get_closest_moveable_point(int lowest_point)
{
	auto my_position = G::me->get_eye_origin();
	auto closest_distance = 9999.f;
	auto closest_point = -1;

	auto idx = 0;
	for (auto vector_point : G::walkbot_points)
	{
		if (++idx <= lowest_point)
			continue;

		auto distance = my_position.distance(vector_point);

		if (distance < closest_distance)
		{
			if (is_point_visible(vector_point))
			{
				closest_point = idx;
				closest_distance = distance;
			}
		}
	}

	return closest_point;
}

/*
 * calculate_move_angle
 * Calculates movement angle to vector
 */
Angle C_WalkBot::calculate_move_angle(Vector3 vector)
{
	return G::math.calc_angle(G::me->get_eye_origin(), vector);
}

/*
 * draw_map_track
 * Draws the map track
 */
void C_WalkBot::draw_map_track()
{
	if (!G::interfaces.engine->is_ingame() || G::me == nullptr || !G::me->is_alive() || G::walkbot_points.empty())
		return;

	auto last_track = Vector3();

	for (auto vector_point : G::walkbot_points)
	{
		if (!last_track.empty() && !vector_point.empty())
		{
			Vector3 track_2d, lasttrack_2d;

			auto conversion1 = G::math.world_2_screen(vector_point, track_2d);
			auto conversion2 = G::math.world_2_screen(last_track, lasttrack_2d);

			if (!conversion1 && !conversion2)
				continue;

			G::interfaces.surface->set_draw_colour(Colour(0, 255, 0));
			G::interfaces.surface->draw_line(static_cast<int>(lasttrack_2d.x), static_cast<int>(lasttrack_2d.y), static_cast<int>(track_2d.x), static_cast<int>(track_2d.y));
		}

		last_track = vector_point;
	}
}
