// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

#include "c_paintvisuals.hpp"
#include "c_menu.hpp"

class C_PaintManager
{
public:

	// Fonts
	unsigned long Arial12;
	unsigned long Arial14;
	unsigned long CourierESP;
	unsigned long Tahoma12;
	unsigned long Tahoma14B;
	unsigned long Verdana12;
	unsigned long Verdana12N;
	unsigned long Verdana12ESP;

	// Classes
	C_PaintVisuals visuals;
	C_Menu menu;

	void start();
	static void setup();
};
