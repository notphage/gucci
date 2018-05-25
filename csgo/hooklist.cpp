// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * paint_hook
 * Root painting hook that will draw on the root panel
 */
void __fastcall paint_hook(void* ecx, void*, PaintMode_t mode)
{
	G::hooks.oPaint(ecx, mode);

	static auto setup_fonts = false;
	static auto setup_paint = reinterpret_cast<void(__thiscall*)(C_VGUISurface*)>(G::signature.find_signature("vguimatsurface.dll", "55 8B EC 83 E4 ? 83 EC ? 80 3D ? ? ? ? 00 56 57 8B F9"));
	static auto finish_paint = reinterpret_cast<void(__thiscall*)(C_VGUISurface*)>(G::signature.find_signature("vguimatsurface.dll", "8B 0D ? ? ? ? 56 C6 05 ? ? ? ? 00 8B 01 FF 90"));

	if (setup_paint == nullptr || finish_paint == nullptr || G::interfaces.surface == nullptr)
	{
		G::console.print("paint_hook nullptr exception!\n");
		return;
	}

	if (mode & PAINT_UIPANELS)
	{
		setup_paint(G::interfaces.surface);

		if (!setup_fonts)
		{
			G::hooks.paint.setup();
			setup_fonts = true;
		}
		else
			G::hooks.paint.start();

		finish_paint(G::interfaces.surface);
	}
}

/*
 * createmove_hook
 * Responsible for all movement related commands
 */
bool __fastcall createmove_hook(void* ecx, void* edx, float sequence, C_UserCmd* cmd)
{
	// Fix frame stuttering
	if (G::hooks.oCreateMove(ecx, edx, sequence, cmd))
		G::interfaces.engine->set_viewangles(cmd->viewangles);

	G::me = G::interfaces.entitylist->get_client_entity(G::interfaces.engine->get_localplayer());

	if (cmd->command_number == 0 || G::me == nullptr || !G::me->is_alive() || G::me->get_weapon() == nullptr || G::round_flags == ROUND_STARTING)
		return false;

	auto& send_packet = *reinterpret_cast<bool*>(*reinterpret_cast<uintptr_t*>(static_cast<char*>(_AddressOfReturnAddress()) - 0x4) - 0x1C);
	G::original_cmd = *cmd;
	G::cmd = cmd;

	G::hooks.createmove.createmove(sequence, cmd, send_packet);

	if (G::interfaces.clientstate->client_state->choked_commands >= 14 && !send_packet || G::interfaces.clientstate->client_state->choked_commands >= 15)
		send_packet = true;

	if (send_packet)
		G::last_sent_origin = G::me->get_origin();

	return false;
}

/*
 * framestagenotify_hook
 * FrameStageNotify
 */
void __fastcall framestagenotify_hook(void* ecx, void* edx, frame_stage stage)
{
	auto valid = G::me != nullptr && G::me->get_weapon() != nullptr && G::me->is_alive();

	if (stage == FRAME_RENDER_START && valid)
	{
		if (G::me->is_thirdperson())
		{
			G::interfaces.prediction->set_local_view_angles(G::me->get_eye_angles());
			G::me->set_abs_angles(Angle(0.f, G::me->get_animation_state()->goal_feet_yaw, 0.f));

			G::me->update_clientside_animations();
		}

		Angle old_aim_punch, old_view_punch;

		if (G::settings.visuals_novisrecoil)
		{
			old_aim_punch = G::me->get_aim_punch();
			old_view_punch = G::me->get_view_punch();

			G::me->get_aim_punch() = Angle();
			G::me->get_view_punch() = Angle();
		}

		G::hooks.oFrameStageNotify(ecx, stage);

		if (G::settings.visuals_novisrecoil)
		{
			G::me->get_aim_punch() = old_aim_punch;
			G::me->get_view_punch() = old_view_punch;
		}
	}
	else
		G::hooks.oFrameStageNotify(ecx, stage);

	if (stage == FRAME_NET_UPDATE_END && valid)
		G::interfaces.lagcompensation->frame_net_update_end();

	//// Perform a full update when these values are changed
	//static int old_posadjust, old_resolver;
	//static auto cl_fullupdate = G::interfaces.cvar->find_var("cl_fullupdate");

	//if (G::settings.rage_positionadjustment != old_posadjust || G::settings.rage_resolver != old_resolver)
	//{
	//	old_posadjust = G::settings.rage_positionadjustment;
	//	old_resolver = G::settings.rage_resolver;

	//	cl_fullupdate->change_callbacks_v1();
	//}

	if (stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START && valid && G::settings.rage_resolver != 0)
	{
		for (auto i = 1; i < G::interfaces.globaldata->max_clients; i++)
		{
			auto entity = G::interfaces.entitylist->get_client_entity(i);

			if (entity == nullptr)
				continue;

			auto index = entity->get_index() - 1;

			G::resolve_ticks[index]++;

			auto eye_angles = &entity->get_eye_angles();
			auto resolve_p = G::interfaces.resolver->resolve(entity, PITCH);
			auto resolve_y = G::interfaces.resolver->resolve(entity, YAW);

			if (resolve_p != -1.f)
				eye_angles->p = resolve_p;

			if (resolve_y != -1.f)
				eye_angles->y = resolve_y;
		}
	}
}

/*
 * overrideview_hook
 * Overrideview hook
 */
void __stdcall overrideview_hook(C_ViewSetup* view_setup)
{
	if (view_setup != nullptr && G::interfaces.engine->is_ingame() && G::me != nullptr)
	{
		Angle camera_angles;
		auto camera_distance = static_cast<float>(G::settings.visuals_thirdperson_distance);

		G::interfaces.engine->get_viewangles(camera_angles);
		camera_angles.r = 0;

		if (G::settings.visuals_thirdperson && G::me->is_alive())
		{
			C_Trace trace;
			C_TraceFilter trace_filter(G::me, TRACE_WORLD_ONLY);
			Vector3 eye_position = G::me->get_eye_origin(), forward_calculation;

			G::math.angle_vectors(camera_angles, &forward_calculation);
			G::interfaces.trace->trace_ray(ray(eye_position, eye_position - forward_calculation * camera_distance, Vector3(-16.f, -16.f, -16.f), Vector3(16.f, 16.f, 16.f)), mask_shot_hull, &trace_filter, &trace);

			camera_distance *= std::clamp(trace.fraction, 0.f, 1.f);

			G::interfaces.cmdinput->m_fCameraInThirdPerson = true;
			G::interfaces.cmdinput->m_vecCameraOffset = Vector3(camera_angles.p, camera_angles.y, camera_distance);
		}
		else
		{
			G::interfaces.cmdinput->m_fCameraInThirdPerson = false;
			G::interfaces.cmdinput->m_vecCameraOffset = Vector3(camera_angles.p, camera_angles.y, 0.f);
		}
	}

	G::hooks.oOverrideView(view_setup);
}

/*
 * in_prediction
 * Called when in prediction, this hook is used to fix setupbones
 */
bool __fastcall inprediction_hook(void* ecx, void*)
{
	static bool data_open[64];
	static auto last_bone_setup_time = /*m_flLastBoneSetupTime*/G::netvars.m_NetVars["DT_BaseAnimating"_crc]["m_hLightingOrigin"_crc] - 0x20;

	if (G::me != nullptr && *reinterpret_cast<uint32_t*>(_ReturnAddress()) == 0x875c084)
	{
		for (auto i = 1; i < G::interfaces.globaldata->max_clients; i++)
		{
			auto entity = G::interfaces.entitylist->get_client_entity(i);

			if (!G::hooks.createmove.ragebot->can_aimbot_player(entity))
				continue;

			auto index = entity->get_index();

			// Force setupbones to not be called
			if (G::settings.rage_positionadjustment != 0 && G::settings.rage_positionadjustment_optimize && G::me->get_weapon() != nullptr && G::hooks.createmove.ragebot->can_aimbot())
			{
				data_open[index] = true;
				entity->write<float>(last_bone_setup_time, sqrt(-1.f));
			}
			else if (data_open[index] == true)
			{
				data_open[index] = false;
				entity->write<float>(last_bone_setup_time, G::interfaces.globaldata->curtime);
			}
		}
	}

	return G::hooks.oInPrediction(ecx);
}

/*
 * runcommand_hook
 * Runcommand
 */
void __stdcall runcommand_hook(C_BaseEntity* entity, C_UserCmd* cmd, void* move_helper)
{
	G::hooks.oRunCommand(entity, cmd, move_helper);

	if (move_helper != nullptr)
		G::interfaces.movehelper = static_cast<C_MoveHelper*>(move_helper);
}

/*
 * firegameevent_hook
 * Fire Game Event
 */
bool __fastcall firegameevent_hook(void* ecx, void* edx, C_GameEvent* game_event)
{
	if (game_event != nullptr && G::me != nullptr)
	{
		if (Crypto::CRC::crc(game_event->GetName()) == "round_freeze_end"_crc)
			G::round_flags = ROUND_IN_PROGRESS;
		else if (Crypto::CRC::crc(game_event->GetName()) == "round_start"_crc)
		{
			G::hooks.createmove.misc->buy_weapons();
			G::round_flags = ROUND_STARTING;
		}
		else if (Crypto::CRC::crc(game_event->GetName()) == "round_end"_crc)
			G::round_flags = ROUND_ENDING;
		else if (Crypto::CRC::crc(game_event->GetName()) == "weapon_reload"_crc)
		{
			if (G::settings.visuals_fastreload && G::interfaces.engine->get_playerforuserid(game_event->GetInt("userid")) == G::me->get_index() && G::me->is_alive())
			{
				G::reloading_data[0] = 1;
				G::reloading_data[1] = G::me->get_weapon()->get_index();
			}
		}
		else if (Crypto::CRC::crc(game_event->GetName()) == "client_disconnect"_crc)
		{
			G::me = nullptr;
			G::round_flags = ROUND_STARTING;
			G::interfaces.lagcompensation->reset();
		}
		else if (Crypto::CRC::crc(game_event->GetName()) == "player_death"_crc)
		{
			if (G::interfaces.engine->get_playerforuserid(game_event->GetInt("userid")) == G::me->get_index())
				G::interfaces.lagcompensation->reset();
		}

		G::interfaces.resolver->fire_game_event(game_event);
	}

	return G::hooks.oFireGameEvent(ecx, edx, game_event);
}

/*
 * get_match_session_hook
 * Get Match Session
 */
void* __stdcall get_match_session_hook()
{
	if (*reinterpret_cast<uint32_t*>(_ReturnAddress()) == 0xcf83d88b)
	{
		auto ebp = *reinterpret_cast<uint32_t*>((uint32_t)_AddressOfReturnAddress() - sizeof(void*));
		auto ptr = *reinterpret_cast<uint32_t*>(ebp - 0xA0);

		if (ptr && *(uint32_t*)(ptr + 0x24))
		{
			auto map_name = *reinterpret_cast<char**>(ptr + 0x24);
			G::console.print(eColour::WHITE, "[COMPETITIVE] Session Map:");
			G::console.print(eColour::GREEN, " %s\n", map_name);
		}
	}

	return G::hooks.oGetMatchSession();
}

void __fastcall draw_model_hook(void* ecx, void*, void* results, const draw_model_info& info, Matrix3x4* bone_to_world, float* flex_weights, float* flex_delayed_weights, const Vector3& model_origin, int flags)
{
	static C_Material* game_cube = nullptr;

	if (info.studio_hdr != nullptr && G::me != nullptr)
	{
		if (game_cube == nullptr)
		{
			for (auto handle = G::interfaces.materialsystem->first_material(); handle != G::interfaces.materialsystem->invalid_material(); handle = G::interfaces.materialsystem->next_material(handle))
			{
				auto material = G::interfaces.materialsystem->get_material(handle);

				if (material != nullptr && std::string(material->get_name()).compare("debug/debugambientcube") == 0)
				{
					game_cube = material;
					break;
				}
			}
		}
		else
		{
			if (G::settings.visuals_chams_enabled)
			{
				std::string model_name = info.studio_hdr->m_name;
				auto entity = info.entity == G::me->get_renderable() ? G::me : info.entity;

				if (entity != nullptr && entity->is_alive())
				{
					auto dont_render_player = G::settings.rage_positionadjustment != 0 && G::settings.rage_positionadjustment_optimize && !(G::settings.rage_target == 0 || G::settings.rage_target == 1 && entity->get_team() == G::me->get_team() || G::settings.rage_target == 2 && entity->get_team() != G::me->get_team()) && entity != G::me;

					if (model_name.find("player/") != std::string::npos)
					{
						auto visible_colour = entity->get_team() == TEAM_T ? Colour(232, 209, 32) : entity->get_team() == TEAM_CT ? Colour(153, 255, 51) : Colour();
						auto invisible_colour = entity->get_team() == TEAM_T ? Colour(255, 51, 0) : entity->get_team() == TEAM_CT ? Colour(66, 134, 244) : Colour();

						// Non Visible Segment
						game_cube->colour_modulate(invisible_colour.r / 255.f, invisible_colour.g / 255.f, invisible_colour.b / 255.f);
						game_cube->alpha_modulate(dont_render_player ? 0.f : 1.f);

						game_cube->set_material_var_flag(MATERIAL_VAR_IGNOREZ, true);
						G::interfaces.studiorender->force_material_override(game_cube);

						G::hooks.oDrawModel(ecx, results, info, bone_to_world, flex_weights, flex_delayed_weights, model_origin, flags);

						// Visible Segment
						game_cube->colour_modulate(visible_colour.r / 255.f, visible_colour.g / 255.f, visible_colour.b / 255.f);
						game_cube->alpha_modulate(dont_render_player ? 0.f : 1.f);

						game_cube->set_material_var_flag(MATERIAL_VAR_IGNOREZ, false);
						G::interfaces.studiorender->force_material_override(game_cube);
					}
				}

				//if (model_name.find("weapons\\w_") != std::string::npos)
				//{
				//	auto visible_colour = Colour(255, 20, 147);

				//	// Non Visible Segment
				//	game_cube->colour_modulate(visible_colour.r / 255.f, visible_colour.g / 255.f, visible_colour.b / 255.f);
				//	game_cube->set_material_var_flag(MATERIAL_VAR_IGNOREZ, true);
				//	G::interfaces.studiorender->force_material_override(game_cube);

				//	G::hooks.oDrawModel(ecx, results, info, bone_to_world, flex_weights, flex_delayed_weights, model_origin, flags);

				//	// Visible Segment
				//	game_cube->colour_modulate(visible_colour.r / 255.f, visible_colour.g / 255.f, visible_colour.b / 255.f);
				//	game_cube->set_material_var_flag(MATERIAL_VAR_IGNOREZ, false);

				//	G::interfaces.studiorender->force_material_override(game_cube);
				//}
			}
		}
	}

	G::hooks.oDrawModel(ecx, results, info, bone_to_world, flex_weights, flex_delayed_weights, model_origin, flags);

	G::interfaces.modelrender->force_material_override(nullptr);
}
