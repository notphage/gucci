// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * C_Element_CheckBox
 * Constructor
 */
C_Element_CheckBox::C_Element_CheckBox(int x, int y, int w, int h, std::string string, bool* boolptr, C_Element_Base* parent): C_Element_Base(x, y, w, h, parent)
{
	auto pLabel = new C_Element_Label(w + 3, h / 2, string, TEXT_ALIGN_LEFT_CENTER, this);
	pLabel->set_font(G::hooks.paint.Verdana12N);

	add_child(pLabel);

	bool_ptr = boolptr;
}

/*
 * get_bool
 * Returns the boolean pointer
 */
bool C_Element_CheckBox::get_bool() const
{
	return *bool_ptr;
}

/*
 * set_bool
 * Sets the boolean pointer
 */
void C_Element_CheckBox::set_bool(bool new_bool) const
{
	*bool_ptr = new_bool;
}

/*
 * paint
 * Paints the window
 */
void C_Element_CheckBox::paint(int /*paint_id*/)
{
	int _x, _y, _w, _h;
	get_position(_x, _y, true);
	get_size(_w, _h);

	auto draw_gradient_box = [](int x, int y, int w, int h, Colour colour)
			{
				for (auto i = 0; i < h; i++)
				{
					G::interfaces.surface->set_draw_colour(Colour(colour.r - static_cast<uint8_t>(5) * static_cast<uint8_t>(i), colour.g - static_cast<uint8_t>(5) * static_cast<uint8_t>(i), colour.b - static_cast<uint8_t>(5) * static_cast<uint8_t>(i), colour.a));
					G::interfaces.surface->draw_line(x, y + i, x + w - 1, y + i);
				}
			};

	if (is_in_rect() && was_mouse_clicked())
		set_bool(!get_bool());

	draw_gradient_box(_x, _y, _w - 1, _h - 1, get_bool() ? Colour(255, 222, 125) : Colour(80, 80, 80));

	G::interfaces.surface->set_draw_colour(Colour(10, 10, 10));
	G::interfaces.surface->draw_outlined_rect(_x, _y, _w - 1, _h - 1);
}

/*
 * click
 * Called when clicked
 */
void C_Element_CheckBox::click(bool /*was_in_panel*/)
{
}

/*
 * think
 * Called when a think is taking place.
 */
void C_Element_CheckBox::think()
{
}
