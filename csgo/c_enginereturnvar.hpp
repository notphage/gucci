// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_EngineCvar;

typedef void (*change_callbackv1)();
typedef void (*change_callback)(void* var, const char* old_value, float fl_old_value);

struct C_ConvarValue
{
	char* m_pszString;
	int m_StringLength;
	float m_fValue;
	int m_nValue;
};

class C_EngineReturnVar
{
public:

	enum Index
	{
		GETVALUE_STRING = 11,
		GETVALUE_FLOAT = 12,
		GETVALUE_INT = 13,
		SETVALUE_STRING = 14,
		SETVALUE_FLOAT = 15,
		SETVALUE_INT = 16,
	};

	/*
	 * get_string
	 * Returns a string
	 */
	const char* get_string()
	{
		return vtable<const char*(__thiscall*)(void*)>(this, GETVALUE_STRING)(this);
	}

	/*
	* get_float
	 * Returns a float
	 */
	float get_float()
	{
		return vtable<float(__thiscall*)(void*)>(this, GETVALUE_FLOAT)(this);
	}

	/*
	 * get_int
	 * Returns a int
	 */
	int get_int()
	{
		return vtable<int(__thiscall*)(void*)>(this, GETVALUE_INT)(this);
	}

	/*
	 * set_value
	 * Sets a value
	 */
	void set_value(const char* _value)
	{
		vtable<void(__thiscall*)(void*, const char*)>(this, SETVALUE_STRING)(this, _value);
	}

	/*
	 * set_value
	 * Sets a value
	 */
	void set_value(float _value)
	{
		vtable<void(__thiscall*)(void*, float)>(this, SETVALUE_FLOAT)(this, _value);
	}

	/*
	 * set_value
	 * Sets a value
	 */
	void set_value(int _value)
	{
		vtable<void(__thiscall*)(void*, int)>(this, SETVALUE_INT)(this, _value);
	}

	PAD(0x4)
	C_EngineReturnVar* next;
	int registered;
	char* name;
	char* help_string;
	int flags;
	change_callbackv1 change_callbacks_v1;
	C_EngineReturnVar* parent;
	char* default_value;
	C_ConvarValue value;
	int has_min;
	float min_val;
	int has_max;
	float max_val;
	void* change_callbacks;
};
