// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * C_Element_Base
 * Constructor Function
 */
C_Element_Base::C_Element_Base(int x, int y, int w, int h, C_Element_Base* _pParent)
{
	height_offset = h;
	set_position(x, y);
	set_size(w, h);
	set_parent(_pParent);
}

/*
 * get_parent
 * Returns the parent
 */
C_Element_Base* C_Element_Base::get_parent() const
{
	return pParent;
}

/*
 * set_parent
 * Sets the elements parent
 */
void C_Element_Base::set_parent(C_Element_Base* parent)
{
	pParent = parent;
}

/*
 * get_root_parent
 * Returns the root parent
 */
C_Element_Base* C_Element_Base::get_root_parent() const
{
	auto parent = get_parent();

	while (true)
	{
		if (parent != nullptr && parent->get_parent() == nullptr)
			return parent;

		if (parent == nullptr)
			return nullptr;

		parent = parent->get_parent();
	}
}

/*
 * add_child
 * Adds a child to the children vector
 */
void C_Element_Base::add_child(C_Element_Base* element)
{
	if (element != nullptr)
		get_children()->push_back(element);
}

/*
 * get_children
 * Returns all children within the element
 */
std::vector<C_Element_Base*>* C_Element_Base::get_children()
{
	return &pChildren;
}

/*
 * get_position
 * Returns the elemtns position
 * if exact is true it will return the exact coordinates from the start of the screen (x: 0, y: 0)
 */
void C_Element_Base::get_position(int& x, int& y, bool exact) const
{
	x = m_x;
	y = m_y;

	if (exact && get_parent() != nullptr)
	{
		int __x, __y;
		get_parent()->get_position(__x, __y, true);

		x += __x;
		y += __y;
	}
}

/*
 * set_position
 * Sets the elements position
 */
void C_Element_Base::set_position(int x, int y)
{
	int _x, _y;
	G::interfaces.engine->get_screen_size(_x, _y);

	m_x = std::clamp(x, 0, _x);
	m_y = std::clamp(y, 0, _y);
}

/*
 * get_size
 * Returns the size of the element
 */
void C_Element_Base::get_size(int& w, int& h) const
{
	int _x, _y;
	G::interfaces.engine->get_screen_size(_x, _y);

	w = std::clamp(m_w, 0, _x);
	h = std::clamp(m_h, 0, _y);
}

/*
 * set_size
 * Sets the size of the element
 */
void C_Element_Base::set_size(int w, int h)
{
	m_w = w;
	m_h = h;
}

/*
 * get_draw_group
 * Returns the draw group
 */
int C_Element_Base::get_draw_group() const
{
	return m_iDrawGroup;
}

/*
 * set_draw_group
 * Sets the draw group
 */
void C_Element_Base::set_draw_group(int draw_group)
{
	m_iDrawGroup = draw_group;
}

/*
 * get_enabled
 * Returns if the element is enabled
 */
bool C_Element_Base::get_enabled() const
{
	return m_bPanelEnabled;
}

/*
 * set_enabled
 * Sets if the element is enabled
 */
void C_Element_Base::set_enabled(bool enabled)
{
	m_bPanelEnabled = enabled;
}

/*
 * get_mouse_pos
 * Returns the mouse position
 */
void C_Element_Base::get_mouse_pos(int& x, int& y) const
{
	tagPOINT point;
	GetCursorPos(&point);
	auto mousePos = &point;
	ScreenToClient(G::hooks.paint.menu.m_pProcess, mousePos);

	int w, h;
	G::interfaces.engine->get_screen_size(w, h);

	x = static_cast<int>(std::clamp(static_cast<float>(mousePos->x), 0.f, static_cast<float>(w)));
	y = static_cast<int>(std::clamp(static_cast<float>(mousePos->y), 0.f, static_cast<float>(h)));
}

/*
 * handle_mouse
 * Handle mouse
 */
void C_Element_Base::handle_mouse()
{
	m_bMouseDown1 = m_bMouseDown2;
	m_bMouseDown2 = is_mouse_down();
}

/*
 * is_mouse_down
 * Returns if the mouse is down
 */
bool C_Element_Base::is_mouse_down()
{
	return G::hooks.paint.menu.m_bIsInGame && GetAsyncKeyState(0x01);
}

/*
 * was_mouse_clicked
 * Returns if the mouse was clicked
 */
bool C_Element_Base::was_mouse_clicked() const
{
	auto pWindow = static_cast<C_Element_Window*>(get_root_parent());

	if (pWindow != nullptr && pWindow->get_focused_element() != nullptr && pWindow->get_focused_element() != this)
		return false;

	return G::hooks.paint.menu.m_bIsInGame && !m_bMouseDown1 && m_bMouseDown2;
}

/*
 * is_in_rect
 * Returns if mouse is in rectangular coordinates
 */
bool C_Element_Base::is_in_rect(int x, int y, int w, int h)
{
	int mx, my, __x, __y, __w, __h;
	get_mouse_pos(mx, my);
	get_size(__w, __h);
	get_position(__x, __y, true);

	if (x != -1)
		__x = x;

	if (y != -1)
		__y = y;

	if (w != -1)
		__w = w;

	if (h != -1)
		__h = h;

	auto pWindow = static_cast<C_Element_Window*>(get_root_parent());

	if (pWindow != nullptr && pWindow->get_focused_element() != nullptr && pWindow->get_focused_element() != this)
		return false;

	return G::hooks.paint.menu.m_bIsInGame && mx > __x && mx < __x + __w && my > __y && my < __y + __h;
}

/*
 * draw_cursor
 * Draws the cursor
 */
void C_Element_Base::draw_cursor() const
{
	int __x, __y;
	get_mouse_pos(__x, __y);

	G::interfaces.surface->set_draw_colour(Colour(255, 255, 255, 255));
	G::interfaces.surface->draw_filled_rect(__x, __y, 1, 1);
	G::interfaces.surface->draw_filled_rect(__x, __y + 1, 2, 1);
	G::interfaces.surface->draw_filled_rect(__x, __y + 2, 3, 1);
	G::interfaces.surface->draw_filled_rect(__x, __y + 3, 4, 1);
	G::interfaces.surface->draw_filled_rect(__x, __y + 4, 5, 1);
	G::interfaces.surface->draw_filled_rect(__x, __y + 5, 6, 1);
	G::interfaces.surface->draw_filled_rect(__x, __y + 6, 7, 1);
	G::interfaces.surface->draw_filled_rect(__x, __y + 7, 8, 1);
	G::interfaces.surface->draw_filled_rect(__x, __y + 8, 9, 1);
	G::interfaces.surface->draw_filled_rect(__x, __y + 9, 10, 1);
	G::interfaces.surface->draw_filled_rect(__x, __y + 10, 6, 1);
	G::interfaces.surface->draw_filled_rect(__x, __y + 11, 3, 1);
	G::interfaces.surface->draw_filled_rect(__x, __y + 12, 2, 1);
	G::interfaces.surface->draw_filled_rect(__x, __y + 13, 1, 1);
	G::interfaces.surface->draw_filled_rect(__x + 5, __y + 10, 2, 1);
	G::interfaces.surface->draw_filled_rect(__x + 5, __y + 11, 2, 1);
	G::interfaces.surface->draw_filled_rect(__x + 5, __y + 12, 2, 1);
	G::interfaces.surface->draw_filled_rect(__x + 6, __y + 13, 2, 1);
	G::interfaces.surface->draw_filled_rect(__x + 6, __y + 14, 2, 1);
}

/*
 * handle_paint
 * Paints all children within element
 */
void C_Element_Base::handle_paint(int paint_id)
{
	paint();

	for (auto pChild : pChildren)
		if (pChild != nullptr && pChild->get_enabled())
			pChild->handle_paint();

	if (m_bDrawCursor)
		draw_cursor();
}

/*
 * handle_think
 * Thinks all children within element
 */
void C_Element_Base::handle_think()
{
	handle_mouse();

	if (was_mouse_clicked())
		click(is_in_rect());

	think();

	for (auto pChild : pChildren)
		if (pChild != nullptr && pChild->get_enabled())
			pChild->handle_think();
}
