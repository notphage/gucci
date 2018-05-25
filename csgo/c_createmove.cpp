// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * createmove
 * Creates Movement for the player
 */
void C_CreateMove::createmove(float /*sequence*/, C_UserCmd* cmd, bool& send_packet) const
{
	G::breaking_lag_compensation = false;

	G::prediction_data.reset();
	prediction->setup(G::prediction_data);
	misc->auto_hop(cmd);
	prediction->predict_engine(G::prediction_data, cmd);

	misc->fast_reload();
	movement->strafe(cmd);

	auto aimbot_ran = ragebot->run(cmd, send_packet);
	if (aimbot_ran || (cmd->buttons & IN_ATTACK || G::me->get_weapon()->get_index() == WEAPON_REVOLVER && cmd->buttons & IN_ATTACK2) && G::me->can_fire())
	{
		if (G::settings.rage_silent_aim == 2)
			send_packet = false;

		misc->accuracy_related(cmd);
	}
	else
	{
		misc->fake_lag(cmd, send_packet);
		misc->anti_aim(cmd, send_packet);
	}

	prediction->finish(G::prediction_data);

	antiban->safe_command(G::antiban_data, send_packet, cmd);
	cmd->move = movement->fix_movement(cmd, G::original_cmd);
	antiban->safe_clamp(G::antiban_data, send_packet, cmd);

	//if (!G::settings.antiban_enabled && GetAsyncKeyState(VK_HOME))
	//{
	//	cmd->viewangles.p = sqrt(-1.f);
	//	cmd->viewangles.y = sqrt(-1.f);
	//	cmd->viewangles.r = sqrt(-1.f);
	//	cmd->move.x = sqrt(-1.f);
	//	cmd->move.y = sqrt(-1.f);
	//	cmd->move.z = sqrt(-1.f);
	//}
}
