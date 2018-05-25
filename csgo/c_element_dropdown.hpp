// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_Element_DropDown : public C_Element_Base
{
	bool dropdown_suspsend_1 = true;
	bool dropdown_suspsend = true;
	bool dropdown_open = false;
	bool dropdown_open_last = false;
	int* int_ptr;
	std::string title;
	std::vector<std::string> options;
	std::vector<C_Element_Label*> labels;
	C_Element_Label* selected_label;
public:
	C_Element_DropDown(int x, int y, int w, int h, std::string string, std::vector<std::string> options_vec, int* intptr, C_Element_Base* parent = nullptr);

	// Functions
	void set_value(int value) const;
	int get_value() const;
	void make_label_buffer();

	void paint(int paint_id) override;
	void click(bool was_in_panel) override;
	void think() override;
};
