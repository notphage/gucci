// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * C_Element_SlideBar
 * Constructor
 */
C_Element_SlideBar::C_Element_SlideBar(int x, int y, int w, int h, std::string string, std::string prefix, int* intptr, int min, int max, C_Element_Base* parent) : C_Element_Base(x, y, w, h, parent)
{
	auto pLabel = new C_Element_Label(1, 8, string, TEXT_ALIGN_LEFT_TOP, this);

	add_child(pLabel);

	int_ptr = intptr;

	set_min_value(min);
	set_max_value(max);
	set_prefix(prefix);
	set_slider_by_value(get_value());
}

/*
 * set_prefix
 * Sets the sliders prefix
 */
void C_Element_SlideBar::set_prefix(std::string prefix)
{
	slider_prefix = prefix;
}

/*
 * get_prefix
 * Returns the sliders prefix
 */
std::string C_Element_SlideBar::get_prefix() const
{
	return slider_prefix;
}

/*
 * set_value
 * Returns the value
 */
void C_Element_SlideBar::set_value(int iValue) const
{
	*int_ptr = std::clamp(iValue, get_min_value(), get_max_value());
}

/*
 * get_value
 * Gets the value
 */
int C_Element_SlideBar::get_value() const
{
	return *int_ptr;
}

/*
 * set_slider_value
 * Sets the slider value
 */
void C_Element_SlideBar::set_slider_value(int _value)
{
	value = _value;
}

/*
 * get_slider_value
 * Returns the slider value
 */
int C_Element_SlideBar::get_slider_value() const
{
	return value;
}

/*
 * set_min
 * Sets the minimum value
 */
void C_Element_SlideBar::set_min_value(int _min)
{
	min = _min;
}

/*
 * get_min
 * Gets the minimum value
 */
int C_Element_SlideBar::get_min_value() const
{
	return min;
}

/*
 * set_max
 * Sets the max
 */
void C_Element_SlideBar::set_max_value(int _max)
{
	max = _max;
}

/*
 * get_max
 * Gets the maximum value
 */
int C_Element_SlideBar::get_max_value() const
{
	return max;
}

/*
 * set_slider_by_pos
 * Sets the slider by position
 */
void C_Element_SlideBar::set_slider_by_pos()
{
	int _x, _y, _w, _h, mx, my;
	get_position(_x, _y, true);
	get_size(_w, _h);
	get_mouse_pos(mx, my);

	_y += 6;
	_h -= 6;

	if (is_in_rect(-1, _y, -1, _h) && is_mouse_down())
	{
		auto slider_ammount = static_cast<float>(mx - _x);

		set_slider_value(static_cast<int>(slider_ammount));
		set_value(static_cast<int>(floor(get_max_value() * std::clamp(slider_ammount / (_w - 1), 0.f, 1.f))));
	}
}

/*
* set_slider_by_value
* Sets the slider by value
*/
void C_Element_SlideBar::set_slider_by_value(int iValue)
{
	int _x, _y, _w, _h, mx, my;
	get_position(_x, _y, true);
	get_size(_w, _h);
	get_mouse_pos(mx, my);

	auto slider_ammount = std::clamp(static_cast<float>(iValue) / static_cast<float>(get_max_value()), 0.f, 1.f);

	set_slider_value(static_cast<int>(_w * slider_ammount));
	set_value(static_cast<int>(floor(get_max_value() * slider_ammount)));
}

/*
 * paint
 * Paints the window
 */
void C_Element_SlideBar::paint(int paint_id)
{
	static auto old_value = 0;
	int _x, _y, _w, _h, t_w, t_h;
	get_position(_x, _y, true);
	get_size(_w, _h);

	_y += 6;
	_h -= 6;

	auto draw_gradient_box = [](int x, int y, int w, int h, Colour colour)
			{
				for (auto i = 0; i < h; i++)
				{
					G::interfaces.surface->set_draw_colour(Colour(colour.r - static_cast<uint8_t>(5) * static_cast<uint8_t>(i), colour.g - static_cast<uint8_t>(5) * static_cast<uint8_t>(i), colour.b - static_cast<uint8_t>(5) * static_cast<uint8_t>(i), colour.a));
					G::interfaces.surface->draw_line(x, y + i, x + w - 1, y + i);
				}
			};

	if (is_in_rect() && is_mouse_down())
		set_slider_by_pos();
	else if (old_value != get_value())
	{
		set_slider_by_value(get_value());
		old_value = get_value();
	}

	draw_gradient_box(_x, _y, _w, _h, Colour(80, 80, 80));
	draw_gradient_box(_x, _y, std::clamp(get_slider_value(), 0, _w), _h, Colour(255, 222, 125));

	G::interfaces.surface->set_draw_colour(Colour(10, 10, 10));
	G::interfaces.surface->draw_outlined_rect(_x, _y, _w, _h);

	G::interfaces.surface->get_text_size(G::hooks.paint.Verdana12N, t_w, t_h, "%i%s", get_value(), get_prefix().c_str());
	G::interfaces.surface->draw_string(std::clamp(_x + get_slider_value() - t_w - 3, _x + 3, _x + _w), _y + _h / 2 + 2, G::hooks.paint.Verdana12N, TEXT_ALIGN_LEFT_CENTER, Colour(200, 200, 200), "%i%s", get_value(), get_prefix().c_str());
}

/*
 * click
 * Called when clicked
 */
void C_Element_SlideBar::click(bool was_in_panel)
{
}

/*
 * think
 * Called when a think is taking place.
 */
void C_Element_SlideBar::think()
{
}
