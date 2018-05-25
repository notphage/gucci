// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

enum SlideBar_Type
{
	SLIDEBAR_FLOAT,
	SLIDEBAR_INT,
	SLIDEBAR_DEGREE,
	SLIDEBAR_PERCENT,
	SLIDEBAR_MS,
};

class C_Element_SlideBar : public C_Element_Base
{
	int value = 0;
	int min = 0;
	int max = 0;
	int* int_ptr;
	std::string slider_prefix;
public:
	C_Element_SlideBar(int x, int y, int w, int h, std::string string, std::string prefix, int* intptr, int min, int max, C_Element_Base* parent = nullptr);

	// Functions
	void set_prefix(std::string prefix);
	std::string get_prefix() const;
	void set_value(int value) const;
	int get_value() const;
	void set_slider_value(int value);
	int get_slider_value() const;
	void set_min_value(int min);
	int get_min_value() const;
	void set_max_value(int max);
	int get_max_value() const;
	void set_slider_by_pos();
	void set_slider_by_value(int value);

	void paint(int paint_id) override;
	void click(bool was_in_panel) override;
	void think() override;
};
