// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

/*
 * PaintMode_t
 * Paint Modes
 */
enum PaintMode_t
{
	PAINT_UIPANELS = 1 << 0,
	PAINT_INGAMEPANELS = 1 << 1,
	PAINT_CURSOR = 1 << 2
};

/*
 * StringAlign_t
 * Align Modes
 */
enum StringAlign_t
{
	TEXT_ALIGN_CENTER = 0,
	TEXT_ALIGN_LEFT,
	TEXT_ALIGN_RIGHT,
	TEXT_ALIGN_CENTER_CENTER,
	TEXT_ALIGN_CENTER_TOP,
	TEXT_ALIGN_CENTER_BOT,
	TEXT_ALIGN_LEFT_CENTER,
	TEXT_ALIGN_LEFT_TOP,
	TEXT_ALIGN_LEFT_BOT,
	TEXT_ALIGN_RIGHT_CENTER,
	TEXT_ALIGN_RIGHT_TOP,
	TEXT_ALIGN_RIGHT_BOT,
};

/*
 * FontFlags_t
 * Font Flags
 */
enum FontFlags_t
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x1,
	FONTFLAG_UNDERLINE = 0x2,
	FONTFLAG_STRIKEOUT = 0x4,
	FONTFLAG_SYMBOL = 0x8,
	FONTFLAG_ANTIALIAS = 0x10,
	FONTFLAG_GAUSSIANBLUR = 0x20,
	FONTFLAG_ROTARY = 0x40,
	FONTFLAG_DROPSHADOW = 0x80,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

/*
 * box_data
 */
struct box_data
{
	int x, y, w, h;
};
