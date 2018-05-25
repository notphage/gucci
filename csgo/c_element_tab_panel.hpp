// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_Element_Tab_Panel : public C_Element_Base
{
	std::vector<std::string> tabs;
	C_Element_Tab_Container* tab_container_ptr;
	int current_tab = 0;
public:
	C_Element_Tab_Panel(int x, int y, int w, int h, std::vector<std::string> chTabs, int start_tab, C_Element_Tab_Container* tab_container, C_Element_Base* parent = nullptr);
	void build_tabs();

	std::vector<std::string> get_tabs() const;
	C_Element_Tab_Container* get_tab_container() const;
	void set_tab_container(C_Element_Tab_Container* tab_container);
	int get_current_tab() const;
	void set_current_tab(int tab);

	void paint(int paint_id) override;
	void click(bool was_in_panel) override;
	void think() override;
};
