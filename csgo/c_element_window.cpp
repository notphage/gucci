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
C_Element_Window::C_Element_Window(std::string chTitle, int x, int y, int w, int h, bool cursor, C_Element_Base* parent): C_Element_Base(x, y, w, h, parent)
{
	m_bDrawCursor = cursor;
	add_child(new C_Element_Label(w / 2, 10, chTitle, TEXT_ALIGN_CENTER, this));
}

/*
 * is_dragging
 * Returns if the window is being dragged
 */
bool C_Element_Window::is_dragging() const
{
	return m_bDragging;
}

/*
 * set_dragging
 * Sets if the window is being dragged
 */
void C_Element_Window::set_dragging(bool dragging)
{
	m_bDragging = dragging;
}

/*
 * get_focused_element
 * Returns the focused element
 */
C_Element_Base* C_Element_Window::get_focused_element() const
{
	return pFocusedElement;
}

/*
 * set_focused_element
 * Sets the focused element
 */
void C_Element_Window::set_focused_element(C_Element_Base* pElement)
{
	pFocusedElement = pElement;
}

/*
 * paint
 * Paints the window
 */
void C_Element_Window::paint(int paint_id)
{
	int _x, _y, _w, _h;

	get_position(_x, _y);
	get_size(_w, _h);

	/*
	 * draw_slant
	 * Draws a Slant
	 */
	auto draw_slant = [](int __x, int __y, int __w, int __h, Colour colour, bool bReversed)
			{
				for (auto i = 0; i < __h; i++)
				{
					G::interfaces.surface->set_draw_colour(colour);

					bReversed ? G::interfaces.surface->draw_line(__x + __w - i, __y - i, __x, __y - i) : G::interfaces.surface->draw_line(__x + i, __y - i, __x + __w, __y - i);
				}
			};

	/*
	 * Menu background
	 */
	G::interfaces.surface->set_draw_colour(Colour(15, 15, 15, 254));
	G::interfaces.surface->draw_filled_rect(_x, _y, _w, _h);

	/*
	 * Menu Outline
	 */
	G::interfaces.surface->set_draw_colour(Colour(5, 5, 5));
	G::interfaces.surface->draw_outlined_rect(_x, _y, _w, _h);

	G::interfaces.surface->set_draw_colour(Colour(60, 60, 60));
	G::interfaces.surface->draw_outlined_rect(_x + 1, _y + 1, _w - 2, _h - 2);

	G::interfaces.surface->set_draw_colour(Colour(40, 40, 40));
	G::interfaces.surface->draw_outlined_rect(_x + 2, _y + 2, _w - 4, _h - 4);

	G::interfaces.surface->set_draw_colour(Colour(60, 60, 60));
	G::interfaces.surface->draw_outlined_rect(_x + 3, _y + 3, _w - 6, _h - 6);

	///*
	// * Top bar box
	// */
	//draw_slant(_x + (_w / 2 - 50 / 2) - 50, _y + 4, 50, 25, Colour(15, 15, 15), false);
	//draw_slant(_x + (_w / 2 - 50 / 2) + 50, _y + 4, 50, 25, Colour(15, 15, 15), true);

	//G::interfaces.surface->set_draw_colour(Colour(15, 15, 15));
	//G::interfaces.surface->draw_filled_rect(_x + (_w / 2 - 50 / 2), _y - 20, 51, 25);

	///*
	// * Top bar outline
	// */
	//G::interfaces.surface->set_draw_colour(Colour(60, 60, 60));
	//G::interfaces.surface->draw_line(_x + (_w / 2 - 50 / 2) - 50, _y + 1, _x + (_w / 2 - 50 / 2) - 44, _y + 1);
	//G::interfaces.surface->draw_line(_x + (_w / 2 - 50 / 2) - 44, _y + 1, _x + (_w / 2 - 50 / 2) - 44 + 20, _y + 2 - 21);
	//G::interfaces.surface->draw_line(_x + (_w / 2 - 50 / 2) - 44 + 20, _y + 2 - 21, _x + (_w / 2 - 50 / 2) - 44 + 20 + 99, _y + 2 - 21);
	//G::interfaces.surface->draw_line(_x + (_w / 2 - 50 / 2) - 44 + 20 + 99, _y + 2 - 21, _x + (_w / 2 - 50 / 2) - 44 + 20 + 99 + 19, _y + 2 - 21 + 20);
	//G::interfaces.surface->draw_line(_x + (_w / 2 - 50 / 2) - 44 + 20 + 99 + 19, _y + 2 - 21 + 20, _x + (_w / 2 - 50 / 2) - 44 + 20 + 99 + 18 + 7, _y + 2 - 21 + 20);

	//G::interfaces.surface->set_draw_colour(Colour(40, 40, 40));
	//G::interfaces.surface->draw_line(_x + (_w / 2 - 50 / 2) - 50, _y + 2, _x + (_w / 2 - 50 / 2) - 44 + 1, _y + 2);
	//G::interfaces.surface->draw_line(_x + (_w / 2 - 50 / 2) - 44 + 1, _y + 2, _x + (_w / 2 - 50 / 2) - 44 + 21, _y + 3 - 21);
	//   G::interfaces.surface->draw_line(_x + (_w / 2 - 50 / 2) - 44 + 21, _y + 3 - 21, _x + (_w / 2 - 50 / 2) - 44 + 20 + 98, _y + 3 - 21);
	//G::interfaces.surface->draw_line(_x + (_w / 2 - 50 / 2) - 44 + 20 + 98, _y + 3 - 21, _x + (_w / 2 - 50 / 2) - 44 + 20 + 99 + 18, _y + 3 - 21 + 20);
	//G::interfaces.surface->draw_line(_x + (_w / 2 - 50 / 2) - 44 + 20 + 98 + 19, _y + 2 - 21 + 21, _x + (_w / 2 - 50 / 2) - 44 + 20 + 99 + 18 + 7, _y + 3 - 21 + 20);

	//G::interfaces.surface->set_draw_colour(Colour(60, 60, 60));
	//G::interfaces.surface->draw_line(_x + (_w / 2 - 50 / 2) - 50, _y + 3, _x + (_w / 2 - 50 / 2) - 44 + 2, _y + 3);
	//G::interfaces.surface->draw_line(_x + (_w / 2 - 50 / 2) - 44 + 2, _y + 3, _x + (_w / 2 - 50 / 2) - 44 + 22, _y + 4 - 21);
	//G::interfaces.surface->draw_line(_x + (_w / 2 - 50 / 2) - 44 + 22, _y + 4 - 21, _x + (_w / 2 - 50 / 2) - 44 + 20 + 97, _y + 4 - 21);
	//G::interfaces.surface->draw_line(_x + (_w / 2 - 50 / 2) - 44 + 20 + 97, _y + 4 - 21, _x + (_w / 2 - 50 / 2) - 44 + 20 + 99 + 17, _y + 4 - 21 + 20);
	//G::interfaces.surface->draw_line(_x + (_w / 2 - 50 / 2) - 44 + 20 + 97 + 19, _y + 2 - 21 + 22, _x + (_w / 2 - 50 / 2) - 44 + 20 + 99 + 18 + 7, _y + 4 - 21 + 20);
}

/*
 * click
 * Called when clicked
 */
void C_Element_Window::click(bool was_in_panel)
{
	int _x, _y, mx, my;
	get_position(_x, _y);
	get_mouse_pos(mx, my);

	auto in_drag_panel = is_in_rect(-1, _y - 10, -1, 25);

	if (in_drag_panel && is_mouse_down())
	{
		m_iDX = mx - _x;
		m_iDY = my - _y;

		set_dragging(true);
	}
}

/*
 * think
 * Called when a think is taking place.
 */
void C_Element_Window::think()
{
	if (is_dragging())
	{
		if (!is_mouse_down())
		{
			set_dragging(false);
			return;
		}

		int mx, my, _w, _h, s_w, s_h;
		G::interfaces.engine->get_screen_size(s_w, s_h);
		get_size(_w, _h);
		get_mouse_pos(mx, my);

		set_position(std::clamp(mx - m_iDX, 0, s_w - _w), std::clamp(my - m_iDY, 0, s_h - _h));
	}
}
