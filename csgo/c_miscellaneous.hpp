// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_Miscellaneous
{
public:
	static void fast_reload();
	static void auto_hop(C_UserCmd* cmd);
	static void buy_weapons();
	static float get_anti_aim_pitch(C_UserCmd* cmd, bool& send_packet);
	static float get_anti_aim_yaw(C_UserCmd* cmd, bool& send_packet);
	static void anti_aim(C_UserCmd* cmd, bool& send_packet);
	static void fake_lag(C_UserCmd* cmd, bool& send_packet);
	static void accuracy_related(C_UserCmd* cmd);
};
