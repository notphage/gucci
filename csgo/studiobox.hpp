#pragma once

class C_Model;

class studio_bbox
{
public:
	studio_bbox() = default;
	int m_bone;
	int m_group;
	Vector3 m_mins;
	Vector3 m_maxs;
	int m_hitbox_name_index;
private:
	PAD(0xC)
public:
	float m_radius;
private:
	PAD(0x10)
};

class studio_hitbox_set
{
public:
	studio_hitbox_set() = default;

	const char* get_name() const
	{
		return (char*)this + m_name_index;
	}

	studio_bbox* get_hitbox(int i) const
	{
		return reinterpret_cast<studio_bbox*>((byte*)this + m_hitbox_index) + i;
	}

	int m_name_index;
	int m_num_hitboxes;
	int m_hitbox_index;
};

class studio_hdr
{
public:
	studio_hdr() = default;

	const char* get_name() const
	{
		return m_name;
	}

	auto get_hitboxset(int i) const
	{
		return reinterpret_cast<studio_hitbox_set*>((byte*)this + m_hitboxset_index) + i;
	}

	int m_id;
	int m_version;
	int m_checksum;
	char m_name[64];
	int m_length;
	Vector3 m_eye_position;
	Vector3 m_illum_position;
	Vector3 m_hull_min;
	Vector3 m_hull_max;
	Vector3 m_view_bbmin;
	Vector3 m_view_bbmax;
	int m_flags;
	int m_num_bones;
	int m_bone_index;
	int m_num_bone_controllers;
	int m_bone_controller_index;
	int m_num_hitboxsets;
	int m_hitboxset_index;
private:
	PAD(0xE4)
};
