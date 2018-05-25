// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * C_Element_Window
 * Constructor Function
 */
C_Element_Label::C_Element_Label(int x, int y, std::string text, StringAlign_t align, C_Element_Base* parent) : C_Element_Base(x, y, 0, 0, parent)
{
	set_text(text);
	set_align(align);
	set_font(G::hooks.paint.Verdana12);

	if (parent != nullptr)
		parent->add_child(this);
}

/*
 * get_text
 * Returns the text for the label
 */
std::string C_Element_Label::get_text() const
{
	return label_text;
}

/*
 * set_text
 * Sets the text for the label
 */
void C_Element_Label::set_text(std::string text)
{
	label_text = text;
}

/*
 * get_align
 * Returns the alignment of the text
 */
StringAlign_t C_Element_Label::get_align() const
{
	return align;
}

/*
 * set_align
 * Sets the align
 */
void C_Element_Label::set_align(StringAlign_t alignment)
{
	align = alignment;
}

/*
 * get_font
 * Returns the font
 */
unsigned long C_Element_Label::get_font() const
{
	return label_font;
}

/*
 * set_font
 * Sets the font
 */
void C_Element_Label::set_font(unsigned long font)
{
	label_font = font;
}

/*
 * paint
 * Paints the window
 */
void C_Element_Label::paint(int paint_id)
{
	int _x, _y, _w, _h;

	get_position(_x, _y, true);
	get_size(_w, _h);
	auto a = get_align();

	G::interfaces.surface->draw_string(_x, _y, get_font(), a, Colour(200, 200, 200), get_text());
}

/*
 * click
 * Called when clicked
 */
void C_Element_Label::click(bool was_in_panel)
{
}

/*
 * think
 * Called when a think is taking place.
 */
void C_Element_Label::think()
{
}
