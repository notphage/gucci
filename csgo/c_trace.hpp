// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017D
// *********************************

#pragma once

enum contents
{
	contents_empty = 0x0,
	contents_solid = 0x1,
	contents_window = 0x2,
	contents_aux = 0x4,
	contents_grate = 0x8,
	contents_slime = 0x10,
	contents_water = 0x20,
	contents_blocklos = 0x40,
	contents_opaque = 0x80,
	contents_testfogvolume = 0x100,
	contents_unused = 0x200,
	contents_blocklight = 0x400,
	contents_team1 = 0x800,
	contents_team2 = 0x1000,
	contents_ignore_nodraw_opaque = 0x2000,
	contents_moveable = 0x4000,
	contents_areaportal = 0x8000,
	contents_playerclip = 0x10000,
	contents_monsterclip = 0x20000,
	contents_current0 = 0x40000,
	contents_current90 = 0x80000,
	contents_current180 = 0x100000,
	contents_current270 = 0x200000,
	contents_current_up = 0x400000,
	contents_current_down = 0x800000,
	contents_origin = 0x1000000,
	contents_monster = 0x2000000,
	contents_debris = 0x4000000,
	contents_detail = 0x8000000,
	contents_translucent = 0x10000000,
	contents_ladder = 0x20000000,
	contents_hitbox = 0x40000000,

	last_visible_contents = contents_opaque,
	all_visible_contents = last_visible_contents | last_visible_contents - 1
};

enum surf
{
	surf_light = 0x1,
	surf_sky2d = 0x2,
	surf_sky = 0x4,
	surf_warp = 0x8,
	surf_trans = 0x10,
	surf_noportal = 0x20,
	surf_trigger = 0x40,
	surf_nodraw = 0x80,
	surf_hint = 0x100,
	surf_skip = 0x200,
	surf_nolight = 0x400,
	surf_bumplight = 0x800,
	surf_noshadows = 0x1000,
	surf_nodecals = 0x2000,
	surf_nopaint = surf_nodecals,
	surf_nochop = 0x4000,
	surf_hitbox = 0x8000
};

enum mask
{
	mask_all = 0xFFFFFFFF,
	mask_solid = (contents_solid | contents_moveable | contents_window | contents_monster | contents_grate),
	mask_playersolid = (contents_solid | contents_moveable | contents_playerclip | contents_window | contents_monster | contents_grate),
	mask_npcsolid = (contents_solid | contents_moveable | contents_monsterclip | contents_window | contents_monster | contents_grate),
	mask_npcfluid = (contents_solid | contents_moveable | contents_monsterclip | contents_window | contents_monster),
	mask_water = (contents_water | contents_moveable | contents_slime),
	mask_opaque = (contents_water | contents_moveable | contents_opaque),
	mask_opaque_npc = (mask_opaque | contents_monster),
	mask_blocklos = (contents_solid | contents_moveable | contents_slime),
	mask_blocklos_npc = (mask_blocklos | contents_monster),
	mask_visible = (mask_opaque | contents_ignore_nodraw_opaque),
	mask_visible_npc = (mask_opaque_npc | contents_ignore_nodraw_opaque),
	mask_shot = (contents_solid | contents_moveable | contents_monster | contents_window | contents_debris | contents_hitbox),
	mask_shot_brushonly = (contents_solid | contents_moveable | contents_window | contents_debris),
	mask_shot_hull = (contents_solid | contents_moveable | contents_monster | contents_window | contents_debris | contents_grate),
	mask_shot_portal = (contents_solid | contents_moveable | contents_window | contents_monster),
	mask_solid_brushonly = (contents_solid | contents_moveable | contents_window | contents_grate),
	mask_playersolid_brushonly = (contents_solid | contents_moveable | contents_window | contents_playerclip | contents_grate),
	mask_npcsolid_brushonly = (contents_solid | contents_moveable | contents_window | contents_monsterclip | contents_grate),
	mask_npcworldstatic = (contents_solid | contents_window | contents_monsterclip | contents_grate),
	mask_npcworldstatic_fluid = (contents_solid | contents_window | contents_monsterclip),
	mask_splitareaportal = (contents_water | contents_slime),
	mask_current = (contents_current0 | contents_current90 | contents_current180 | contents_current270 | contents_current_up | contents_current_down),
	mask_deadsolid = (contents_solid | contents_playerclip | contents_window | contents_grate)
};

/*
 * trace_type
 */
enum trace_type
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

/*
 * ray
 */
struct ray
{
	Vector4 start;
	Vector4 delta;
	Vector4 start_offset;
	Vector4 extents;

	const Matrix3x4* world_axis;
	bool is_ray;
	bool is_swept;

	ray(): world_axis(nullptr), is_ray(false), is_swept(false)
	{
	}

	ray(Vector3 _start, Vector3 _end)
	{
		init(_start, _end);
	}

	ray(Vector3 _start, Vector3 _end, Vector3 _mins, Vector3 _maxs)
	{
		init(_start, _end, _mins, _maxs);
	}

	void init(Vector3 _start, Vector3 _end)
	{
		start = _start;
		delta = _end - _start;
		is_swept = fabs(delta.length_sqr()) != 0.f;
		extents.clear();
		world_axis = nullptr;
		is_ray = true;
		start_offset.clear();
	}

	void init(Vector3 _start, Vector3 _end, Vector3 _mins, Vector3 _maxs)
	{
		//m_Delta = VectorAligned(Vector(end - start));
		delta.x = _end.x - _start.x;
		delta.y = _end.y - _start.y;
		delta.z = _end.z - _start.z;

		world_axis = nullptr;
		is_swept = delta.length_sqr() != 0.f;

		//m_Extents = VectorAligned(Vector(maxs - mins));
		extents.x = _maxs.x - _mins.x;
		extents.y = _maxs.y - _mins.y;
		extents.z = _maxs.z - _mins.z;

		extents *= 0.5f;
		is_ray = extents.length_sqr() < 1e-6;

		//m_StartOffset = VectorAligned(Vector(mins + maxs));
		start_offset.x = _mins.x + _maxs.x;
		start_offset.y = _mins.y + _maxs.y;
		start_offset.z = _mins.z + _maxs.z;

		start_offset *= 0.5f;

		//m_Start = VectorAligned(Vector(start + m_StartOffset));
		start.x = _start.x + start_offset.x;
		start.y = _start.y + start_offset.y;
		start.z = _start.z + start_offset.z;

		start_offset *= -1.0f;
	}
};


/*
 * C_TraceFilter
 * Trace
 */
class C_TraceFilter
{
public:
	explicit C_TraceFilter(C_BaseEntity* entity, trace_type tracetype = TRACE_EVERYTHING)
	{
		skip_entity = entity;
		type = tracetype;
	}

	virtual bool should_hit(C_BaseEntity* entity, int mask)
	{
		return entity != skip_entity;
	}

	virtual trace_type get_trace_type()
	{
		return type;
	}

	C_BaseEntity* skip_entity;
	trace_type type;
};

/*
 * C_Trace
 * Trace Class
 */
class C_Trace
{
public:
	bool IsDispSurface() const { return (disp_flags & 1 << 0) != 0; }
	bool IsDispSurfaceWalkable() const { return (disp_flags & 1 << 1) != 0; }
	bool IsDispSurfaceBuildable() const { return (disp_flags & 1 << 2) != 0; }
	bool IsDispSurfaceProp1() const { return (disp_flags & 1 << 3) != 0; }
	bool IsDispSurfaceProp2() const { return (disp_flags & 1 << 4) != 0; }

	Vector3 startpos;
	Vector3 endpos;
	C_Plane plane;
	float fraction;
	int contents;
	unsigned short disp_flags;
	bool allsolid;
	bool startsolid;

	float fractionleftsolid;
	C_Surface surface;
	int hitgroup;
	short physicsbone;
	unsigned short world_surface_index;
	C_BaseEntity* ent;
	int hitbox;

	bool did_hit() const
	{
		return fraction < 1.f || allsolid || startsolid;
	}
};
