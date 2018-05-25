// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * safe_command
 * Safes the current command so that we can use it in valve servers
 */
void C_AntiBan::safe_command(antiban_state_data& data, bool& send_packet, C_UserCmd* cmd) const
{
	if (!G::settings.antiban_enabled)
	{
		data.snap_angle = G::me->get_eye_angles();
		data.snap_state = ANTIBAN_AT_DESTINATION;
		return;
	}

	auto destination_angle = cmd->viewangles.normalized();
	auto current_angle = data.snap_angle.normalized();
	auto angle_delta = (destination_angle - current_angle).normalized();
	auto snap_state = ANTIBAN_AT_DESTINATION;
	G::settings.antiban_max_snap = std::clamp(G::settings.antiban_max_snap, 1, G::settings.antiban_safesnaps ? 39 : 180);

	for (auto i = 0; i <= 1; i++)
	{
		if (abs(angle_delta[i]) > G::settings.antiban_max_snap)
			snap_state = ANTIBAN_STEPPING;

		if (angle_delta[i] > G::settings.antiban_max_snap)
			current_angle[i] += G::settings.antiban_max_snap;
		else if (angle_delta[i] < -G::settings.antiban_max_snap)
			current_angle[i] -= G::settings.antiban_max_snap;
		else
			current_angle[i] = destination_angle[i];

		current_angle[i] = std::clamp(current_angle[i], current_angle[i] - G::settings.antiban_max_snap, current_angle[i] + G::settings.antiban_max_snap);
	}

	data.snap_angle = current_angle.normalized();
	data.snap_angle.clamp();
	data.snap_state = snap_state;

	safe_clamp(data, send_packet, cmd);
}

/*
 * safe_clamp
 * Safes our to be movement data
 */
void C_AntiBan::safe_clamp(antiban_state_data& data, bool& send_packet, C_UserCmd* cmd) const
{
	if (!G::settings.antiban_enabled)
	{
		data.snap_angle = G::me->get_eye_angles();
		data.snap_state = ANTIBAN_AT_DESTINATION;
		return;
	}

	data.snap_angle.normalize();
	data.snap_angle.clamp();
	cmd->viewangles = data.snap_angle;

	cmd->move.x = std::clamp(cmd->move.x, -450.f, 450.f);
	cmd->move.y = std::clamp(cmd->move.y, -450.f, 450.f);
	cmd->move.z = std::clamp(cmd->move.z, -320.f, 320.f);

	if (data.snap_state == ANTIBAN_STEPPING)
	{
		cmd->buttons &= ~IN_ATTACK;
		cmd->buttons &= ~IN_USE;
	}
}
