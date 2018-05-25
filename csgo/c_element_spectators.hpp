// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_Element_Spectators : public C_Element_Base
{
public:
	C_Element_Spectators(int x, int y, int w, int h, C_Element_Base* parent = nullptr);

	void paint(int paint_id) override;
	void click(bool was_in_panel) override;
	void think() override;
};
