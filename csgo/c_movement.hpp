// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_Movement
{
public:

	float get_move_angle(float speed) const;
	bool get_closest_plane(Vector3* plane) const;
	bool will_hit_obstacle_in_future(float predict_time, float step) const;
	void circle_strafe(C_UserCmd* cmd, float* circle_yaw);
	void strafe(C_UserCmd* cmd);
	Vector3 fix_movement(C_UserCmd* cmd, C_UserCmd original_command) const;
};
