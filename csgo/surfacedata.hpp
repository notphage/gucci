// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017D
// *********************************

#pragma once

enum TEXTURE_CHARACTERS
{
	CHAR_TEX_ANTLION = 'A',
	CHAR_TEX_BLOODYFLESH = 'B',
	CHAR_TEX_CONCRETE = 'C',
	CHAR_TEX_DIRT = 'D',
	CHAR_TEX_EGGSHELL = 'E',
	CHAR_TEX_FLESH = 'F',
	CHAR_TEX_GRATE = 'G',
	CHAR_TEX_ALIENFLESH = 'H',
	CHAR_TEX_CLIP = 'I',
	CHAR_TEX_PLASTIC = 'L',
	CHAR_TEX_METAL = 'M',
	CHAR_TEX_SAND = 'N',
	CHAR_TEX_FOLIAGE = 'O',
	CHAR_TEX_COMPUTER = 'P',
	CHAR_TEX_SLOSH = 'S',
	CHAR_TEX_TILE = 'T',
	CHAR_TEX_CARDBOARD = 'U',
	CHAR_TEX_VENT = 'V',
	CHAR_TEX_WOOD = 'W',
	CHAR_TEX_GLASS = 'Y',
	CHAR_TEX_WARPSHIELD = 'Z',
};

/*
 * surface_physics_params
 */
struct surface_physics_params
{
	float friction;
	float elasticity;
	float density;
	float thickness;
	float dampening;
};

/*
 * surface_audio_params
 */
struct surface_audio_params
{
	float reflectivity;
	float hardnessfactor;
	float roughnessfactor;
	float roughthreshold;
	float hardthreshold;
	float hardvelocitythreshold;
};

/*
 * surface_sound_names
 */
struct surface_sound_names
{
	unsigned short walkstepleft;
	unsigned short walkstepright;
	unsigned short runstepleft;
	unsigned short runstepright;
	unsigned short impactsoft;
	unsigned short impacthard;
	unsigned short scrapesmooth;
	unsigned short scraperough;
	unsigned short bulletimpact;
	unsigned short rolling;
	unsigned short breaksound;
	unsigned short strainsound;
};

/*
 * surface_sound_handles
 */
struct surface_sound_handles
{
	short walkstepleft;
	short walkstepright;
	short runstepleft;
	short runstepright;
	short impactsoft;
	short impacthard;
	short scrapesmooth;
	short scraperough;
	short bulletimpact;
	short rolling;
	short breaksound;
	short strainsound;
};

/*
 * surface_game_props
 */
struct surface_game_props
{
	float maxspeedfactor;
	float jumpfactor;
	PAD(0x4)
	float penetrationmodifier;
	float damagemodifier;
	unsigned short material;
	PAD(0x3)
};

/*
 * surface_data
 */
struct surface_data
{
	surface_physics_params physics;
	surface_audio_params audio;
	surface_sound_names sounds;
	surface_game_props game;
	surface_sound_handles soundhandles;
};


/*
 * wrect_s
 */
typedef struct wrect_s
{
	int left;
	int right;
	int top;
	int bottom;
} wrect_t;

/*
 * C_HudTexture
 */
class C_HudTexture
{
public:
	char m_short_name[64];
	char m_texture_file[64];
	bool m_render_using_font;
	bool m_precached;
	char m_character_in_font;
private:
	PAD(0x1)
public:
	unsigned long m_font;
	int m_texture_id;
	float m_tex_coords[4];
	wrect_t m_rc;
};
