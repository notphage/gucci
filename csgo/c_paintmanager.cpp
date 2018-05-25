// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * start
 * Starts drawing
 */
void C_PaintManager::start()
{
	if (!G::interfaces.engine->is_ingame())
		G::me = nullptr;

	if (menu.m_bSetup)
		visuals.render();

	//G::interfaces.walkbot->draw_map_track();
	menu.handle();
}

/*
 * setup
 * Sets up painter before its started
 */
void C_PaintManager::setup()
{
	G::interfaces.surface->set_font_glyph_set(G::hooks.paint.Verdana12N = G::interfaces.surface->reserve_font_handle(), "Verdana", 12, FW_BOLD, 0, 0, FONTFLAG_OUTLINE);
	G::interfaces.surface->set_font_glyph_set(G::hooks.paint.Verdana12 = G::interfaces.surface->reserve_font_handle(), "Verdana", 12, FW_BOLD, 0, 0, FONTFLAG_ANTIALIAS);
	G::interfaces.surface->set_font_glyph_set(G::hooks.paint.Verdana12ESP = G::interfaces.surface->reserve_font_handle(), "Verdana", 12, FW_BOLD, 0, 0, FONTFLAG_DROPSHADOW);
	G::interfaces.surface->set_font_glyph_set(G::hooks.paint.Arial12 = G::interfaces.surface->reserve_font_handle(), "Arial", 12, FW_NORMAL, 0, 0, FONTFLAG_DROPSHADOW);
	G::interfaces.surface->set_font_glyph_set(G::hooks.paint.Arial14 = G::interfaces.surface->reserve_font_handle(), "Arial", 14, FW_NORMAL, 0, 0, FONTFLAG_DROPSHADOW);
	G::interfaces.surface->set_font_glyph_set(G::hooks.paint.CourierESP = G::interfaces.surface->reserve_font_handle(), "Courier New", 14, 200, 0, 0, FONTFLAG_OUTLINE);
	G::interfaces.surface->set_font_glyph_set(G::hooks.paint.Tahoma12 = G::interfaces.surface->reserve_font_handle(), "Tahoma", 12, FW_BOLD, 0, 0, FONTFLAG_DROPSHADOW);
	G::interfaces.surface->set_font_glyph_set(G::hooks.paint.Tahoma14B = G::interfaces.surface->reserve_font_handle(), "Tahoma", 14, FW_BOLD, 0, 0, FONTFLAG_DROPSHADOW);
}
