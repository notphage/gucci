// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * C_Element_Group_Box
 * Constructor
 */
C_Element_Group_Box::C_Element_Group_Box(int x, int y, int w, int h, std::string chString, C_Element_Base* parent) : C_Element_Base(x, y, w, h, parent)
{
	chText = chString;
	auto pLabel = new C_Element_Label(22, 0, chText, TEXT_ALIGN_LEFT_CENTER, this);
	pLabel->set_align(TEXT_ALIGN_LEFT_CENTER);

	set_label(pLabel);
	add_child(pLabel);
}

/*
 * get_label
 * Returns the label
 */
C_Element_Label* C_Element_Group_Box::get_label() const
{
	return label_element;
}

/*
 * set_label
 * Sets the label
 */
void C_Element_Group_Box::set_label(C_Element_Label* label)
{
	label_element = label;
}

/*
 * paint
 * Paints the window
 */
void C_Element_Group_Box::paint(int paint_id)
{
	int _x, _y, _w, _h, t_w, t_h;
	get_position(_x, _y, true);
	get_size(_w, _h);
	G::interfaces.surface->get_text_size(get_label()->get_font(), t_w, t_h, chText);

	G::interfaces.surface->set_draw_colour(Colour(5, 5, 5));
	G::interfaces.surface->draw_outlined_rect(_x, _y, _w, _h);

	G::interfaces.surface->set_draw_colour(Colour(30, 30, 30));
	G::interfaces.surface->draw_outlined_rect(_x + 1, _y + 1, _w - 2, _h - 2);

	G::interfaces.surface->set_draw_colour(Colour(15, 15, 15));
	G::interfaces.surface->draw_line(_x + 20, _y, _x + 20 + t_w + 2, _y);
	G::interfaces.surface->draw_line(_x + 20, _y + 1, _x + 20 + t_w + 2, _y + 1);
}

/*
 * click
 * Called when clicked
 */
void C_Element_Group_Box::click(bool was_in_panel)
{
}

/*
 * think
 * Called when a think is taking place.
 */
void C_Element_Group_Box::think()
{
}
