// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_WalkBot
{
public:
	static void run(C_UserCmd* cmd);
	static void set_track_points(std::vector<Vector3> vector_map);
	static bool is_point_visible(Vector3 vector);
	static int get_closest_moveable_point(int lowest_point);
	static Angle calculate_move_angle(Vector3 vector);
	static void draw_map_track();
};
