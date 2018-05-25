// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once
class C_Element_Group_Box : public C_Element_Base
{
	std::string chText;
	C_Element_Label* label_element;
	int m_iDrawTabGroup = 0;
public:
	C_Element_Group_Box(int x, int y, int w, int h, std::string chString, C_Element_Base* parent = nullptr);

	// Functions
	C_Element_Label* get_label() const;
	void set_label(C_Element_Label* label);

	void paint(int paint_id) override;
	void click(bool was_in_panel) override;
	void think() override;
};
