// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * C_Element_DropDown
 * Constructor
 */
C_Element_DropDown::C_Element_DropDown(int x, int y, int w, int h, std::string string, std::vector<std::string> options_vec, int* intptr, C_Element_Base* parent): C_Element_Base(x, y, w, h, parent)
{
	//auto pLabel = new C_Element_Label(1, 0, string, TEXT_ALIGN_LEFT_TOP, this);
	//add_child(pLabel);

	title = string;
	options = options_vec;
	int_ptr = intptr;

	make_label_buffer();
}

/*
 * set_value
 * Returns the value
 */
void C_Element_DropDown::set_value(int value) const
{
	*int_ptr = value;
}

/*
 * get_value
 * Gets the value
 */
int C_Element_DropDown::get_value() const
{
	return *int_ptr;
}

/*
 * make_label_buffers
 * Makes label buffers
 */
void C_Element_DropDown::make_label_buffer()
{
	int _x, _y, _w, _h;
	get_position(_x, _y, true);
	get_size(_w, _h);

	add_child(selected_label = new C_Element_Label(3 + 5, _h / 2, "DROPDOWN_TEXT", TEXT_ALIGN_LEFT_CENTER, this));

	auto i = 0;
	for (auto pOptionName : options)
	{
		auto pLabel = new C_Element_Label(3 + 5, _h + _h / 2 + _h * i - 3, pOptionName.c_str(), TEXT_ALIGN_LEFT_CENTER, this);
		add_child(pLabel);

		labels.push_back(pLabel);

		i++;
	}
}

/*
 * paint
 * Paints the window
 */
void C_Element_DropDown::paint(int /*paint_id*/)
{
	int _x, _y, _w, _h;
	get_position(_x, _y, true);
	get_size(_w, _h);

	auto window_element = static_cast<C_Element_Window*>(get_root_parent());

	if (dropdown_open_last != dropdown_open && !is_mouse_down() && !was_mouse_clicked() && !dropdown_suspsend)
	{
		window_element->set_focused_element(dropdown_open ? this : nullptr);
		dropdown_open_last = dropdown_open;
	}

	if (is_in_rect() && was_mouse_clicked() && !dropdown_suspsend)
	{
		dropdown_open = !dropdown_open;

		if (dropdown_open && get_parent() != nullptr)
		{
			auto _pChildren = get_parent()->get_children();

			if (_pChildren != nullptr)
			{
				auto i = 0;
				for (auto pChild : *_pChildren)
				{
					if (pChild == this)
					{
						_pChildren->erase(_pChildren->begin() + i);
						_pChildren->push_back(this);
						dropdown_suspsend = true;
						dropdown_suspsend_1 = true;

						//window_element->set_focused_element(this);
					}

					i++;
				}
			}
		}
	}

	auto draw_arrow = [](int x, int y, int w, Colour colour, bool dropdown_open)
			{
				G::interfaces.surface->set_draw_colour(colour);

				if (!dropdown_open)
				{
					G::interfaces.surface->draw_filled_rect(x, y, w, 2);
					G::interfaces.surface->draw_filled_rect(x + 1, y + 2, w - 2, 1);
					G::interfaces.surface->draw_filled_rect(x + 2, y + 3, w - 4, 1);
				}
				else
				{
					G::interfaces.surface->draw_filled_rect(x, y + 2, w, 2);
					G::interfaces.surface->draw_filled_rect(x + 1, y + 1, w - 2, 1);
					G::interfaces.surface->draw_filled_rect(x + 2, y, w - 4, 1);
				}
			};

	auto new_height = _h + _h * (dropdown_open ? options.size() : 0);
	auto selected_dropdown = options.at(get_value()).c_str();

	G::interfaces.surface->set_draw_colour(Colour(40, 40, 40, 255));
	G::interfaces.surface->draw_filled_rect(_x, _y, _w, new_height);

	G::interfaces.surface->set_draw_colour(Colour(15, 15, 15, 255));
	G::interfaces.surface->draw_outlined_rect(_x, _y, _w, new_height);

	draw_arrow(static_cast<int>(_x + _w * 0.95f), _y + (_h / 2 - 2), 6, Colour(200, 200, 200), dropdown_open);

	selected_label->set_text(title + ": " + selected_dropdown);

	auto i = 0;
	while (i <= static_cast<int>(options.size()) - 1)
	{
		auto pLabel = labels.at(i);
		pLabel->set_enabled(dropdown_open);

		if (dropdown_open)
		{
			window_element->set_focused_element(this);

			if (is_in_rect(_x + 2, _y + _h + _h * i, _w - 2, _h))
			{
				G::interfaces.surface->set_draw_colour(Colour(15, 15, 15));
				G::interfaces.surface->draw_filled_rect(_x + 4, _y + _h + _h * i, _w - 8, _h - 4);

				if (was_mouse_clicked())
				{
					dropdown_open = false;
					set_value(i);
				}
			}
			else if (!is_in_rect(-1, -1, _w, new_height) && was_mouse_clicked())
				dropdown_open = false;
		}

		i++;
	}

	if (!dropdown_suspsend_1)
		dropdown_suspsend = false;

	dropdown_suspsend_1 = false;
}

/*
 * click
 * Called when clicked
 */
void C_Element_DropDown::click(bool /*was_in_panel*/)
{
}

/*
 * think
 * Called when a think is taking place.
 */
void C_Element_DropDown::think()
{
}
