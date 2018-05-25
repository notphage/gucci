// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * C_Element_Spectators
 * Constructor Function
 */
C_Element_Spectators::C_Element_Spectators(int x, int y, int w, int h, C_Element_Base* parent) : C_Element_Base(x, y, w, h, parent)
{
	if (parent != nullptr)
		parent->add_child(this);
}


/*
 * paint
 * Paints the window
 */
void C_Element_Spectators::paint(int paint_id)
{
	int _x, _y, _w, _h;

	get_position(_x, _y, true);
	get_parent()->get_size(_w, _h);

	auto height = 40;

	for (auto i = 1; i < G::interfaces.globaldata->max_clients; i++)
	{
		auto entity = G::interfaces.entitylist->get_client_entity(i);

		if (entity == nullptr || entity->is_alive())
			continue;

		height += 15;

		G::interfaces.surface->draw_string(_w / 2, height, G::hooks.paint.Verdana12, TEXT_ALIGN_CENTER, Colour(255, 255, 255), "%s", entity->get_info().name);

		get_parent()->set_size(_w, height);
	}
}

/*
 * click
 * Called when clicked
 */
void C_Element_Spectators::click(bool was_in_panel)
{
}

/*
 * think
 * Called when a think is taking place.
 */
void C_Element_Spectators::think()
{
}
