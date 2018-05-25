// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_BaseEntity;

/*
 * draw_model_state
 */
struct draw_model_state
{
	studio_hdr* studio_hdr;
	void* studio_data;
	void* renderable;
	const Matrix3x4* model_to_world;
	unsigned short decals;
	int draw_flags;
	int lod;
};

/*
 * draw_model_info
 */
struct draw_model_info
{
	studio_hdr* studio_hdr;
	void* hardware_data;
	PAD(0x4)
	int skin;
	int body;
	int hitbox_set;
	C_BaseEntity* entity;
	int lod;
	void* colour_mesh;
	bool static_lighting;
	PAD(0x8)
};

/*
 * model_render_info
 */
struct model_render_info
{
	Vector3 origin;
	Vector3 angles;
	void* renderable;
	const C_Model* model;
	const Matrix3x4* model_to_world;
	const Matrix3x4* lighting_offset;
	const Vector3* lighting_origin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	unsigned short instance;

	model_render_info(): renderable(nullptr), model(nullptr), model_to_world(nullptr), lighting_offset(nullptr), lighting_origin(nullptr), flags(0), entity_index(0), skin(0), body(0), hitboxset(0), instance(0)
	{
	}
};

/*
 * C_KeyValues
 */
class C_KeyValues
{
public:
	explicit C_KeyValues(const char* name)
	{
		C_SignatureScanner signature_scanner;
		static auto address = reinterpret_cast<void(__thiscall*)(C_KeyValues*, const char*)>(signature_scanner.find_signature("client.dll", "55 8B EC 51 33 C0 C7 45 ? ? ? ? ? 56 8B F1 81 26 ? ? ? ? C6 46 03 ? 89 46 10 89 46 18 89 46 14 89 46 1C 89 46 04 89 46 08 89 46 0C FF 15 ? ? ? ? 6A 01 FF 75 08 8D 4D FC 8B 10 51 8B C8 FF 52 24 8B 0E 33 4D FC 81 E1 ? ? ? ? 31 0E 88 46 03"));
		address(this, name);
	}

	bool load_from_buffer(const char* resource_name, const char* buffer)
	{
		C_SignatureScanner signature_scanner;
		static auto address = reinterpret_cast<bool(__thiscall*)(void*, const char*, const char*, void*, const char*, void*)>(signature_scanner.find_signature("client.dll", "55 8B EC 83 EC 48 53 56 57 8B F9 89 7D F4"));
		return address(this, resource_name, buffer, nullptr, nullptr, nullptr);
	}

	byte pad[64U];
};

/*
 * override_type
 */
enum override_type
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
};

/*
 * material_flags
 */
enum material_flags
{
	MATERIAL_VAR_DEBUG = 1 << 0,
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = 1 << 1,
	MATERIAL_VAR_NO_DRAW = 1 << 2,
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = 1 << 3,
	MATERIAL_VAR_VERTEXCOLOR = 1 << 4,
	MATERIAL_VAR_VERTEXALPHA = 1 << 5,
	MATERIAL_VAR_SELFILLUM = 1 << 6,
	MATERIAL_VAR_ADDITIVE = 1 << 7,
	MATERIAL_VAR_ALPHATEST = 1 << 8,
	MATERIAL_VAR_ZNEARER = 1 << 10,
	MATERIAL_VAR_MODEL = 1 << 11,
	MATERIAL_VAR_FLAT = 1 << 12,
	MATERIAL_VAR_NOCULL = 1 << 13,
	MATERIAL_VAR_NOFOG = 1 << 14,
	MATERIAL_VAR_IGNOREZ = 1 << 15,
	MATERIAL_VAR_DECAL = 1 << 16,
	MATERIAL_VAR_ENVMAPSPHERE = 1 << 17,
	MATERIAL_VAR_ENVMAPCAMERASPACE = 1 << 19,
	MATERIAL_VAR_BASEALPHAENVMAPMASK = 1 << 20,
	MATERIAL_VAR_TRANSLUCENT = 1 << 21,
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = 1 << 22,
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = 1 << 23,
	MATERIAL_VAR_OPAQUETEXTURE = 1 << 24,
	MATERIAL_VAR_ENVMAPMODE = 1 << 25,
	MATERIAL_VAR_SUPPRESS_DECALS = 1 << 26,
	MATERIAL_VAR_HALFLAMBERT = 1 << 27,
	MATERIAL_VAR_WIREFRAME = 1 << 28,
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = 1 << 29,
	MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = 1 << 30,
	MATERIAL_VAR_VERTEXFOG = 1 << 31,
};
