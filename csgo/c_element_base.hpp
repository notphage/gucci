// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_Element_Base
{
public:
	int m_x, m_y, m_w, m_h;
	int m_iDrawGroup = -1;
	bool m_bPanelEnabled = true;
	bool m_bMouseDown1, m_bMouseDown2, m_bDrawCursor;

	C_Element_Base* pParent = nullptr;
	std::vector<C_Element_Base*> pChildren;

	int height_offset = 0;
	virtual ~C_Element_Base() = default;

	C_Element_Base(int _x, int _y, int _w, int _h, C_Element_Base* _pParent = nullptr);

	// Control Functions
	C_Element_Base* get_parent() const;
	void set_parent(C_Element_Base* parent);
	C_Element_Base* get_root_parent() const;
	void add_child(C_Element_Base* element);
	std::vector<C_Element_Base*>* get_children();
	void get_position(int& _x, int& _y, bool exact = false) const;
	void set_position(int _x, int _y);
	void get_size(int& _w, int& _h) const;
	void set_size(int _w, int _h);
	int get_draw_group() const;
	void set_draw_group(int draw_group);
	bool get_enabled() const;
	void set_enabled(bool enabled);
	void get_mouse_pos(int& _x, int& _y) const;
	void handle_mouse();
	static bool is_mouse_down();
	bool was_mouse_clicked() const;
	bool is_in_rect(int _x = -1, int _y = -1, int _w = -1, int _h = -1);
	void draw_cursor() const;

	void handle_paint(int paint_id = -1);
	void handle_think();

	// Virtual Functions
	virtual void paint(int paint_id = -1) = 0;
	virtual void think() = 0;
	virtual void click(bool was_in_panel) = 0;
};
