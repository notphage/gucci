// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * C_Element_Tab_Panel
 * Constructor
 */
C_Element_Tab_Panel::C_Element_Tab_Panel(int x, int y, int w, int h, std::vector<std::string> chTabs, int start_tab, C_Element_Tab_Container* tab_container, C_Element_Base* parent): C_Element_Base(x, y, w, h, parent)
{
	tabs = chTabs;

	set_tab_container(tab_container);
	set_current_tab(start_tab);
	build_tabs();

	if (parent != nullptr)
		parent->add_child(this);

	if (get_tab_container() != nullptr)
		add_child(get_tab_container());
}

void C_Element_Tab_Panel::build_tabs()
{
	int _x, _y, _w, _h;

	get_position(_x, _y, true);
	get_size(_w, _h);

	auto iTabCount = 0;
	for (auto chName : get_tabs())
	{
		auto iTabSize = _w / get_tabs().size();

		auto eLabel = new C_Element_Label(iTabSize * iTabCount + iTabSize / 2, _h / 2, chName, TEXT_ALIGN_CENTER_CENTER, this);
		eLabel->set_align(TEXT_ALIGN_CENTER_CENTER);

		iTabCount += 1;
	}
}

/*
 * get_tabs
 * Returns the tabs
 */
std::vector<std::string> C_Element_Tab_Panel::get_tabs() const
{
	return tabs;
}

/*
 * get_tab_container
 * Returns the tab container
 */
C_Element_Tab_Container* C_Element_Tab_Panel::get_tab_container() const
{
	return tab_container_ptr;
}

/*
 * set_tab_container
 * Sets the tab container
 */
void C_Element_Tab_Panel::set_tab_container(C_Element_Tab_Container* tab_container)
{
	tab_container_ptr = tab_container;
}

/*
 * get_current_tab
 * Returns the tab id
 */
int C_Element_Tab_Panel::get_current_tab() const
{
	return current_tab;
}

/*
 * set_current_tab
 * Sets the tab id
 */
void C_Element_Tab_Panel::set_current_tab(int tab)
{
	current_tab = tab;

	if (get_tab_container() != nullptr)
		get_tab_container()->set_draw_tab(get_current_tab());
}

/*
 * paint
 * Paints the window
 */
void C_Element_Tab_Panel::paint(int paint_id)
{
	int _x, _y, _w, _h;

	get_position(_x, _y, true);
	get_size(_w, _h);

	int tab_count = get_tabs().size();
	auto tab_width = _w / tab_count;

	for (auto i = 0; i < tab_count; i++)
	{
		auto cur_x = tab_width * i;
		auto is_in_box = is_in_rect(_x + cur_x + 10, _y, tab_width - 20, _h);

		if (get_current_tab() == i || is_in_box)
		{
			if (was_mouse_clicked())
				set_current_tab(i);

			/*
			 * Bar
			 */
			G::interfaces.surface->set_draw_colour(Colour(255, 222, 125, get_current_tab() == i ? 255 : 50));
			G::interfaces.surface->draw_filled_rect(_x + cur_x + 10, _y + _h - _h / 4, tab_width - 20, 1);
			G::interfaces.surface->set_draw_colour(Colour(222, 172, 22, get_current_tab() == i ? 255 : 50));
			G::interfaces.surface->draw_filled_rect(_x + cur_x + 10, _y + _h - _h / 4 + 1, tab_width - 20, 1);

			///*
			// * Glow
			// */
			//G::interfaces.surface->set_draw_colour(Colour(170, 145, 0, get_current_tab() == i ? 100 : 20));
			//G::interfaces.surface->draw_outlined_rect(_x + cur_x + 10 - 1, _y + _h - _h / 4 + 1 - 2, tab_width - 20 + 2, 1 + 3);
			//G::interfaces.surface->set_draw_colour(Colour(150, 125, 0, get_current_tab() == i ? 15 : 5));
			//G::interfaces.surface->draw_outlined_rect(_x + cur_x + 10 - 2, _y + _h - _h / 4 + 1 - 3, tab_width - 20 + 4, 1 + 5);
		}
		else
		{
			G::interfaces.surface->set_draw_colour(Colour(60, 60, 60, 255));
			G::interfaces.surface->draw_filled_rect(_x + cur_x + 10, _y + _h - _h / 4, tab_width - 20, 2);
		}
	}
}

/*
 * click
 * Called when clicked
 */
void C_Element_Tab_Panel::click(bool was_in_panel)
{
}

/*
 * think
 * Called when a think is taking place.
 */
void C_Element_Tab_Panel::think()
{
}
