// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

/*
 * antiban_states
 */
enum antiban_states
{
	ANTIBAN_WAITING,
	ANTIBAN_STEPPING,
	ANTIBAN_AT_DESTINATION,
	ANTIBAN_MALFORMED,
};

/*
 * antiban_data
 */
struct antiban_state_data
{
	antiban_states snap_state = ANTIBAN_STEPPING;
	Angle snap_angle;
};

class C_AntiBan
{
public:
	void safe_command(antiban_state_data& data, bool& send_packet, C_UserCmd* cmd) const;
	void safe_clamp(antiban_state_data& data, bool& send_packet, C_UserCmd* cmd) const;
};
