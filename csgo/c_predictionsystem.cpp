// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"
#include "c_md5.hpp"

/*
 * setup
 * Sets up prediction so that we can perfrom full game prediction
 */
void C_PredictionSystem::setup(player_prediction_data& data)
{
	if (data.prediction_stage != 0 || G::me == nullptr)
		return;

	static auto random_seed_sig = *reinterpret_cast<unsigned**>(G::signature.find_signature("client.dll", "8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04", 2));

	data.curtime = G::interfaces.globaldata->curtime;
	data.frametime = G::interfaces.globaldata->frametime;

	if (random_seed_sig != nullptr)
	{
		data.prediction_random_seed = random_seed_sig;
		data.random_seed = *random_seed_sig;
	}

	G::interfaces.globaldata->curtime = static_cast<float>(G::me->get_tick_base() * G::interfaces.globaldata->interval_per_tick);
	G::interfaces.globaldata->frametime = G::interfaces.globaldata->interval_per_tick;

	data.non_predicted.flags = G::me->get_entity_flags();
	data.non_predicted.curtime = G::interfaces.globaldata->curtime;

	data.prediction_stage = 1;
}

/*
 * predict_engine
 * Predicts the game 1 tick forwards
 */
void C_PredictionSystem::predict_engine(player_prediction_data& data, C_UserCmd* cmd)
{
	if (data.prediction_stage != 1 || G::me == nullptr)
		return;

	data.in_prediction = G::interfaces.prediction->in_prediction;
	data.tickbase = G::me->get_tick_base();

	if (data.prediction_random_seed != nullptr)
		*data.prediction_random_seed = C_MD5::MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;

	G::interfaces.prediction->in_prediction = true;

	if (G::interfaces.prediction->engine_paused)
		G::interfaces.globaldata->frametime = 0;

	C_MoveData move_data;
	memset(&move_data, 0, sizeof move_data);

	//static auto sv_footsteps = G::interfaces.cvar->find_var("sv_footsteps");
	//auto sv_footsteps_old = sv_footsteps->get_float();

	//sv_footsteps->change_callbacks = nullptr;
	//sv_footsteps->set_value(0.f);
	G::interfaces.movehelper->set_host(G::me);
	G::interfaces.prediction->setup_movement(G::me, cmd, G::interfaces.movehelper, &move_data);
	G::interfaces.movement->process_movement(G::me, &move_data);
	G::me->get_tick_base() = data.tickbase;
	G::interfaces.prediction->finish_movement(G::me, cmd, &move_data);
	//sv_footsteps->set_value(sv_footsteps_old);

	G::interfaces.prediction->in_prediction = data.in_prediction;

	data.prediction_stage = 2;
}

/*
 * finish
 * Finishes prediction and restores all values
 */
void C_PredictionSystem::finish(player_prediction_data& data)
{
	if (data.prediction_stage != 2 || G::me == nullptr)
		return;

	G::interfaces.movehelper->set_host(nullptr);

	if (data.prediction_random_seed != nullptr)
		*data.prediction_random_seed = data.random_seed;

	G::interfaces.globaldata->curtime = data.curtime;
	G::interfaces.globaldata->frametime = data.frametime;
}
