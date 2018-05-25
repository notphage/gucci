// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"
#include <valarray>

/*
 * render
 * Render function that calls all members within
 */
void C_PaintVisuals::render()
{
	render_player_visuals();
	render_watermark();
	render_networked_breaks();
}

/*
 * calculate_box
 * Generates a 3d box then calculates a perfect 2d box from the deltas.
 */
bool C_PaintVisuals::calculate_box(C_BaseEntity* pEntity, box_data& box)
{
	if (pEntity == nullptr || !pEntity->is_alive())
		return false;

	const auto& tran_frame = pEntity->get_rgflcoordinateframe();
	printf("%p\n", &tran_frame);

	auto min = pEntity->get_obbmins();
	auto max = pEntity->get_obbmaxs();

	Vector3 screen_boxes[8];

	Vector3 points[] =
	{
		Vector3(min.x, min.y, min.z),
		Vector3(min.x, max.y, min.z),
		Vector3(max.x, max.y, min.z),
		Vector3(max.x, min.y, min.z),
		Vector3(max.x, max.y, max.z),
		Vector3(min.x, max.y, max.z),
		Vector3(min.x, min.y, max.z),
		Vector3(max.x, min.y, max.z)
	};

	for (auto i = 0; i <= 7; ++i)
		if (!G::math.world_2_screen(G::math.vector_transform(points[i], tran_frame), screen_boxes[i]))
			return false;

	Vector3 box_array[] =
	{
		screen_boxes[3], // Front left
		screen_boxes[5], // Back right 
		screen_boxes[0], // Back left
		screen_boxes[4], // Front right
		screen_boxes[2], // Front right
		screen_boxes[1], // Back right
		screen_boxes[6], // Back left
		screen_boxes[7] // Front Left
	};

	auto left = screen_boxes[3].x, bottom = screen_boxes[3].y, right = screen_boxes[3].x, top = screen_boxes[3].y;

	for (auto i = 0; i <= 7; i++)
	{
		if (left > box_array[i].x)
			left = box_array[i].x;

		if (bottom < box_array[i].y)
			bottom = box_array[i].y;

		if (right < box_array[i].x)
			right = box_array[i].x;

		if (top > box_array[i].y)
			top = box_array[i].y;
	}

	box.x = static_cast<int>(left);
	box.y = static_cast<int>(top);
	box.w = static_cast<int>(right - left);
	box.h = static_cast<int>(bottom - top);

	return true;
}

/*
 * render_networked_breaks
 * Shows networked breaks
 */
void C_PaintVisuals::render_networked_breaks()
{
	if (!G::settings.visuals_networkinformation || !G::interfaces.engine->is_ingame() || G::me == nullptr || !G::me->is_alive())
		return;

	auto draw_module = [](int x, int y, int w, int h, std::string title, bool is_breaking)
			{
				auto colour = Colour();

				if (is_breaking)
					colour = Colour(std::clamp(255.f - sin(G::interfaces.globaldata->curtime * 5.f) * 50.f, 0.f, 255.f), 0.f, 0.f);
				else
					colour = Colour(0.f, std::clamp(255.f - sin(G::interfaces.globaldata->curtime * 5.f) * 50.f, 0.f, 255.f), 0.f);

				G::interfaces.surface->set_draw_colour(Colour(0.f, 0.f, 0.f));
				G::interfaces.surface->draw_outlined_rect(x, y, w, h);
				G::interfaces.surface->draw_outlined_rect(x + 1, y + 1, w, h);

				G::interfaces.surface->set_draw_colour(colour);
				G::interfaces.surface->draw_filled_rect(x + 1, y + 1, w - 2, h - 2);

				G::interfaces.surface->draw_string(x + w / 2, y + h / 2, G::hooks.paint.Tahoma12, TEXT_ALIGN_CENTER_CENTER, Colour(), title);
			};

	draw_module(10, 10, 200, 15, "Lag-Compensation", G::breaking_lag_compensation);
	draw_module(10, 30, 200, 15, "Lower-Body", abs(G::math.normalize_angle(G::original_cmd.viewangles.y - G::me->get_lower_body_yaw())) >= 30.f);
}

/*
 * optimise_graphics
 * Attempts to optimise the graphics
 */
void C_PaintVisuals::optimise_graphics()
{
	static auto mat_postprocess_enable = G::interfaces.cvar->spoof(G::interfaces.cvar->find_var("mat_postprocess_enable"), "gucci_mat_postprocess_enable");
	static auto mat_disable_bloom = G::interfaces.cvar->spoof(G::interfaces.cvar->find_var("mat_disable_bloom"), "gucci_mat_disable_bloom");
	static auto mat_colorcorrection = G::interfaces.cvar->spoof(G::interfaces.cvar->find_var("mat_colorcorrection"), "gucci_mat_colorcorrection");
	static auto r_drawdecals = G::interfaces.cvar->spoof(G::interfaces.cvar->find_var("r_drawdecals"), "gucci_r_drawdecals");
	static auto r_drawtranslucentrenderables = G::interfaces.cvar->spoof(G::interfaces.cvar->find_var("r_drawtranslucentrenderables"), "gucci_r_drawtranslucentrenderables");

	if (G::settings.visuals_optimisegraphics)
	{
		mat_postprocess_enable->set_value(0);
		mat_disable_bloom->set_value(1);
		mat_colorcorrection->set_value(0);
		r_drawdecals->set_value(0);
		r_drawtranslucentrenderables->set_value(0);
	}
	else
	{
		mat_postprocess_enable->set_value(1);
		mat_disable_bloom->set_value(0);
		mat_colorcorrection->set_value(1);
		r_drawdecals->set_value(1);
		r_drawtranslucentrenderables->set_value(1);
	}
}

/*
 * render_asus_walls
 * Renders asus walls
 */
void C_PaintVisuals::render_asus_walls()
{
	if (!G::interfaces.engine->is_ingame() || G::me == nullptr)
		return;

	static auto sv_skyname = G::interfaces.cvar->find_var("sv_skyname");
	sv_skyname->flags &= ~FCVAR_CHEAT;

	static auto asus_value_static = 100;
	auto asus_value = G::settings.visuals_daytime;

	if (asus_value_static != asus_value)
	{
		asus_value_static = asus_value;

		for (auto handle = G::interfaces.materialsystem->first_material(); handle != G::interfaces.materialsystem->invalid_material(); handle = G::interfaces.materialsystem->next_material(handle))
		{
			auto material = G::interfaces.materialsystem->get_material(handle);

			if (material == nullptr)
				continue;

			if (std::string(material->get_texture_group_name()).compare("World textures") == 0)
			{
				auto asus_float_value = asus_value / 100.f;

				material->colour_modulate(asus_float_value, asus_float_value, asus_float_value);

				//if (std::string(material->get_name()).compare("dev/dev_measuregeneric01b") != 0)
				//{
				//	material->set_material_var_flag(MATERIAL_VAR_TRANSLUCENT, asus_value < 100);

				//	material->alpha_modulate(static_cast<float>(asus_value * 0.01f));
				//}
			}
			else if (std::string(material->get_texture_group_name()).compare("SkyBox textures") == 0)
			{
				sv_skyname->set_value("sky_csgo_night02");

				//if (asus_value < 100)
				//	material->colour_modulate(0.f, 0.f, 0.f);
				//else
				//	material->colour_modulate(1.f, 1.f, 1.f);
			}
		}

		//if (asus_value_static == 100)
		//	G::interfaces.engine->client_cmd("mat_reloadallmaterials");
	}
}

/*
 * render_player_visuals
 * Renders the players visuals
 */
void C_PaintVisuals::render_player_visuals()
{
	if (!G::interfaces.engine->is_ingame())
		return;

	auto render_esp = [](C_BaseEntity* entity)
			{
				if (entity == nullptr || G::settings.visuals_render == 2 && entity->get_team() != G::me->get_team() || G::settings.visuals_render == 3 && entity->get_team() == G::me->get_team())
					return;

				box_data data;

				if (!calculate_box(entity, data))
					return;

				if (G::settings.visuals_box)
				{
					auto team = entity->get_team();
					auto box_colour = team == TEAM_T ? Colour(255, 51, 0) : team == TEAM_CT ? Colour(66, 134, 244) : Colour();
					G::interfaces.surface->set_draw_colour(box_colour);
					G::interfaces.surface->draw_outlined_rect(data.x, data.y, data.w, data.h);

					/*
					 * Outlines
					 */
					if (G::settings.visuals_outlines)
					{
						G::interfaces.surface->set_draw_colour(Colour(10, 10, 10, 179));
						G::interfaces.surface->draw_outlined_rect(data.x - 1, data.y - 1, data.w + 2, data.h + 2);
						G::interfaces.surface->draw_outlined_rect(data.x + 1, data.y + 1, data.w - 2, data.h - 2);
					}
				}

				/*
				 * HealthBar
				 */
				if (G::settings.visuals_healthbar)
				{
					auto health = entity->get_health();
					auto health_calc = std::clamp(health * data.h / 100, 0, data.h);
					auto health_colour = Colour().hsv_to_rgb(health + 25, 1, 1);

					G::interfaces.surface->set_draw_colour(Colour(10, 10, 10, 179));
					G::interfaces.surface->draw_filled_rect(data.x - 5, data.y - 1, 3, data.h + 2);

					G::interfaces.surface->set_draw_colour(health_colour);
					G::interfaces.surface->draw_filled_rect(data.x - 4, data.y + data.h - health_calc, 1, health_calc);
				}

				/*
				 * ArmorBar
				 */
				if (G::settings.visuals_armorbar)
				{
					auto armor = entity->get_armor();
					auto armor_calc = std::clamp(armor * data.w / 100, 0, data.w);

					G::interfaces.surface->set_draw_colour(Colour(10, 10, 10, 179));
					G::interfaces.surface->draw_filled_rect(data.x - 1, data.y + data.h + 2, data.w + 2, 3);

					G::interfaces.surface->set_draw_colour(Colour(116, 193, 252));
					G::interfaces.surface->draw_filled_rect(data.x, data.y + data.h + 3, armor_calc, 1);
				}

				if (G::settings.visuals_information)
				{
					G::interfaces.surface->draw_string(data.x + data.w / 2, data.y, G::hooks.paint.CourierESP, TEXT_ALIGN_CENTER_TOP, Colour(255, 255, 255), "%s", entity->get_info().name);

					auto weapon_handle = entity->get_weapon();
					if (weapon_handle != nullptr)
					{
						G::interfaces.surface->draw_string(data.x + data.w / 2, data.y + data.h + 1 + (G::settings.visuals_armorbar ? 3 : 0), G::hooks.paint.CourierESP, TEXT_ALIGN_CENTER, Colour(255, 255, 255), "%s", weapon_handle->get_weapon_name());
					}
				}
			};

	render_asus_walls();
	optimise_graphics();
	G::interfaces.lagcompensation->paint_debug();

	for (auto i = 1; i < G::interfaces.globaldata->max_clients; i++)
	{
		auto entity = G::interfaces.entitylist->get_client_entity(i);

		if (entity == nullptr || !entity->is_alive() || entity->is_dormant())
			continue;

		if (G::settings.visuals_render != 0)
			render_esp(entity);
	}
}

/*
 * render_watermark
 * Draw Watermark
 */
void C_PaintVisuals::render_watermark()
{
	if (!G::interfaces.engine->is_ingame())
	{
		G::interfaces.surface->draw_string(10, 10, G::hooks.paint.Arial14, Colour(), "Gucci");
		G::interfaces.surface->draw_string(10, 20, G::hooks.paint.Arial14, Colour(), "%s", __DATE__);
	}
}
