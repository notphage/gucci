// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_Element_CheckBox : public C_Element_Base
{
	bool* bool_ptr;
public:
	C_Element_CheckBox(int x, int y, int w, int h, std::string string, bool* boolptr, C_Element_Base* parent = nullptr);

	// Functions
	bool get_bool() const;
	void set_bool(bool new_bool) const;

	void paint(int paint_id) override;
	void click(bool was_in_panel) override;
	void think() override;
};
