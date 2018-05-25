// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_Element_Window : public C_Element_Base
{
	C_Element_Base* pFocusedElement = nullptr;
	bool m_bDragging;
	int m_iDX, m_iDY;
public:

	C_Element_Window(std::string chTitle, int x, int y, int w, int h, bool cursor = false, C_Element_Base* eParent = nullptr);

	// Functions
	bool is_dragging() const;
	void set_dragging(bool dragging);
	C_Element_Base* get_focused_element() const;
	void set_focused_element(C_Element_Base* pElement);

	void paint(int paint_id) override;
	void click(bool was_in_panel) override;
	void think() override;
};
