// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once
#include "framework.hpp"

/*
 * eColour
 * Enum table for all console colours
 */
enum class eColour
{
	BLACK,
	DARKBLUE,
	DARKGREEN,
	DARKCYAN,
	DARKRED,
	DARKPINK,
	DARKYELLOW,
	LIGHTGREY,
	DARKGREY,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PINK,
	YELLOW,
	WHITE
};

/*
 * C_Console
 * A Console class mainly used for debugging and such
 */
class C_Console
{
	bool bConsoleVisible = false;
public:

	void create_console(char* chWindowName);
	static void set_text_colour(eColour eColour);
	void set_visible(bool bVisible);
	bool get_visible() const;
	void print(std::string chText, ...) const;
	void print(eColour eColour, std::string chText, ...) const;
};
