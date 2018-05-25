// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * C_Element_Tab_Container
 * Constructor
 */
C_Element_Tab_Container::C_Element_Tab_Container(int x, int y, int w, int h, C_Element_Base* parent) : C_Element_Base(x, y, w, h, parent)
{
}

/*
 * get_draw_tab
 * Returns the current draw tab
 */
int C_Element_Tab_Container::get_draw_tab() const
{
	return m_iDrawTabGroup;
}

/*
 * set_draw_tab
 * Sets the current draw tab
 */
void C_Element_Tab_Container::set_draw_tab(int draw_tab)
{
	m_iDrawTabGroup = draw_tab;
}

/*
 * Gets the item offset
 */
int C_Element_Tab_Container::get_item_offset() const
{
	return item_offset;
}

/*
 * add_offset
 * Adds a offset
 */
void C_Element_Tab_Container::add_offset(int offset)
{
	item_offset += offset;
}

/*
 * reset_item_offsets
 * Resets item offset
 */
void C_Element_Tab_Container::reset_item_offsets(int offset)
{
	item_offset = offset;
	item_start_offset = offset;
}

/*
 * add
 * Adds a element to container
 */
void C_Element_Tab_Container::add(int draw_group, C_Element_Base* element, bool dont_position)
{
	if (element != nullptr)
	{
		element->set_draw_group(draw_group);
		element->set_parent(this);

		add_child(element);

		if (!dont_position)
		{
			int _x, _y, _offset;
			element->get_position(_x, _y);
			_offset = element->height_offset + 5;

			element->set_position(_x, get_item_offset());

			add_offset(_offset);
		}
	}
}

/*
 * paint
 * Paints the window
 */
void C_Element_Tab_Container::paint(int paint_id)
{
	int _x, _y, _w, _h;
	get_position(_x, _y, true);
	get_size(_w, _h);

	//G::interfaces.surface->set_draw_colour(Colour(0, 255, 0));
	//G::interfaces.surface->draw_filled_rect(_x, _y, _w, _h);
}

/*
 * click
 * Called when clicked
 */
void C_Element_Tab_Container::click(bool was_in_panel)
{
}

/*
 * think
 * Called when a think is taking place.
 */
void C_Element_Tab_Container::think()
{
	for (auto pChild : *get_children())
		if (pChild != nullptr && pChild->get_draw_group() != -1)
			pChild->set_enabled(pChild->get_draw_group() == get_draw_tab());
}
