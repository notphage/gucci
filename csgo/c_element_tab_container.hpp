// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once
class C_Element_Tab_Container : public C_Element_Base
{
	int item_offset = 0;
	int item_start_offset = 0;
	int m_iDrawTabGroup = 0;
public:
	C_Element_Tab_Container(int x, int y, int w, int h, C_Element_Base* parent = nullptr);

	// Functions
	int get_draw_tab() const;
	void set_draw_tab(int draw_tab);
	int get_item_offset() const;
	void add_offset(int offset);
	void reset_item_offsets(int offset = 0);
	void add(int draw_group, C_Element_Base* element, bool dont_position = false);

	void paint(int paint_id) override;
	void click(bool was_in_panel) override;
	void think() override;
};
