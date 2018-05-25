// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_Element_Label : public C_Element_Base
{
	StringAlign_t align;
	std::string label_text;
	unsigned long label_font;

public:
	C_Element_Label(int x, int y, std::string text, StringAlign_t align = TEXT_ALIGN_LEFT, C_Element_Base* parent = nullptr);

	// Functions
	std::string get_text() const;
	void set_text(std::string text);
	StringAlign_t get_align() const;
	void set_align(StringAlign_t alignment);
	unsigned long get_font() const;
	void set_font(unsigned long font);

	void paint(int paint_id) override;
	void click(bool was_in_panel) override;
	void think() override;
};
