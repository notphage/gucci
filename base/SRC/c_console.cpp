// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "c_console.hpp"

/*
 * CreateConsole
 * Creates a console with a given window name
 */
void C_Console::create_console(char* chWindowName)
{
	AllocConsole();

	auto pMenu = GetSystemMenu(GetConsoleWindow(), 0);

	if (pMenu == nullptr)
		return;

	DeleteMenu(pMenu, 0xF060, 0x00000000L); // Delete Close button on taskbar for console

	_iobuf* pData;
	freopen_s(&pData, "CONIN$", "r", __acrt_iob_func(0));
	freopen_s(&pData, "CONOUT$", "w", __acrt_iob_func(1));

	SetConsoleTitleA(chWindowName);

	this->bConsoleVisible = true;
}

/*
 * SetTextColour
 * Set the colour of the text
 */
void C_Console::set_text_colour(eColour eColour)
{
	SetConsoleTextAttribute(GetStdHandle(static_cast<DWORD>(-11)), *reinterpret_cast<WORD*>(&eColour));
}

/*
 * SetVisible
 * Sets if the console should be visible
 */
void C_Console::set_visible(bool bVisible)
{
	this->bConsoleVisible = bVisible;
}

/*
* GetVisible
* Returns if the console is visible
*/
bool C_Console::get_visible() const
{
	return this->bConsoleVisible;
}

/*
 * Print
 * Prints text to console
 */
void C_Console::print(std::string chText, ...) const
{
	if (!get_visible())
		return;

	char chMergedBuffer[1024];
	va_list vlist;
	(void)(__vcrt_va_start_verify_argument_type<decltype(chText)>() , (void)(vlist = static_cast<va_list>(&const_cast<char&>(reinterpret_cast<const volatile char&>(chText))) + (sizeof chText + sizeof(int) - 1 & ~(sizeof(int) - 1))));
	vsprintf_s(chMergedBuffer, chText.c_str(), vlist);
	(void)(vlist = static_cast<va_list>(nullptr));

	// Now lets print the merged string
	set_text_colour(eColour::WHITE);
	printf("%s", chMergedBuffer);
	set_text_colour(eColour::WHITE);
}

/*
 * Print
 * Prints text to console with a colour format
 */
void C_Console::print(eColour eColour, std::string chText, ...) const
{
	if (!get_visible())
		return;

	char chMergedBuffer[1024];
	va_list vlist;
	(void)(__vcrt_va_start_verify_argument_type<decltype(chText)>() , (void)(vlist = static_cast<va_list>(&const_cast<char&>(reinterpret_cast<const volatile char&>(chText))) + (sizeof chText + sizeof(int) - 1 & ~(sizeof(int) - 1))));
	vsprintf_s(chMergedBuffer, chText.c_str(), vlist);
	(void)(vlist = static_cast<va_list>(nullptr));

	// Now lets print the merged string
	set_text_colour(eColour);
	printf("%s", chMergedBuffer);
	set_text_colour(eColour::WHITE);
}
