// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_BaseEntity;

class C_PaintVisuals
{
public:
	static void render();
	static bool calculate_box(C_BaseEntity* pEntity, box_data& box);
	static void render_networked_breaks();
	static void optimise_graphics();
	static void render_asus_walls();
	static void render_player_visuals();
	static void render_watermark();
};
