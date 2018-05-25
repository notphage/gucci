// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

/*
 * C_EngineClient
 * Engine Client Interface
 */
class C_EngineClient
{
public:

	VFUNCTION(5, void, get_screen_size, int& w, int& h)
	VFUNCTION(12, int, get_localplayer)
	VFUNCTION(18, void, get_viewangles, Angle& viewangle)
	VFUNCTION(19, void, set_viewangles, Angle& viewangle)
	VFUNCTION(108, void, client_cmd, const char* command)
	VFUNCTION(8, bool, get_playerinfo, int entity_id, player_info* pInfo)
	VFUNCTION(9, int, get_playerforuserid, int entity_id)
	VFUNCTION(26, bool, is_ingame)
	VFUNCTION(37, Matrix4x4&, world_to_screen_matrix)
	VFUNCTION(78, void*, get_net_channel_info)

	/*
	 * get_latency
	 * Returns latency
	 */
	float get_latency(int flow)
	{
		auto pNetChannel = get_net_channel_info();

		return vtable<float(__thiscall*)(void*, int)>(pNetChannel, 9)(pNetChannel, flow);
	}

	/*
	 * get_avg_latency
	 * Returns average latency
	 */
	float get_avg_latency(int flow)
	{
		auto pNetChannel = get_net_channel_info();

		return vtable<float(__thiscall*)(void*, int)>(pNetChannel, 10)(pNetChannel, flow);
	}
};

/*
 * C_Client
 * Client Interface
 */
class C_Client
{
public:

	VFUNCTION(8, C_ClientPropData*, get_all_classes)
};

/*
 * C_ClientEntityList
 * ClientEntityList Interface
 */
class C_ClientEntityList
{
public:

	VFUNCTION(3, C_BaseEntity*, get_client_entity, int index)
	VFUNCTION(4, C_BaseEntity*, get_client_entity_handle, void* handle)
};

/*
 * C_EngineCVar
 * EngineCVar Interface
 */
class C_EngineCvar
{
public:
	VFUNCTION(10, void, register_con_command, C_EngineReturnVar* command);
	VFUNCTION(11, void, un_register_con_command, C_EngineReturnVar* command);
	VFUNCTION(15, C_EngineReturnVar*, find_var, const char* var)

	C_EngineReturnVar* spoof(C_EngineReturnVar* cvar, char* new_name)
	{
		un_register_con_command(cvar);
		cvar->name = new_name;
		register_con_command(cvar);

		return cvar;
	}

	//C_EngineReturnVar* setup_spoofable(C_EngineReturnVar* command)
	//{
	//	auto original_name = command->name;
	//	auto original_value = command->value;
	//	char new_name[128];

	//	sprintf(new_name, "forced_%s", original_name);

	//	un_register_con_command(command);
	//	command->name = new_name;
	//	register_con_command(command);

	//	return command;
	//}
};

/*
 * C_ClientState
 * ClientState Interface
 */
class C_ClientState
{
public:
	PAD(0x4CAC)
	int choked_commands;
};

/*
 * C_EnginePointerToClientState
 * EnginePointerToClientState Interface
 */
class C_EnginePointerToClientState
{
public:
	C_ClientState* client_state;
	PAD(0x3C)
};

/*
 * C_ClientPrediction
 * ClientPrediction Interface
 */
class C_ClientPrediction
{
public:
	VFUNCTION(13, void, set_local_view_angles, Angle& angle)
	VFUNCTION(20, void, setup_movement, C_BaseEntity* entity, C_UserCmd* cmd, void* move, void* move_data)
	VFUNCTION(21, void, finish_movement, C_BaseEntity* entity, C_UserCmd* cmd, void* move_data)

	PAD(8)
	bool in_prediction;
	PAD(1)
	bool engine_paused;
};

/*
 * C_GameMovement
 * GameMovement Interface
 */
class C_GameMovement
{
public:

	VFUNCTION(1, void, process_movement, C_BaseEntity* entity, void* move_data)
};

/*
 * C_MoveHelper
 * Move Helper Class
 */
class C_MoveHelper
{
public:

	VFUNCTION(1, void, set_host, C_BaseEntity* entity)
};

/*
 * C_Panel
 * Panel Interface
 */
class C_Panel
{
public:

	VFUNCTION(36, const char*, get_name, unsigned int panel)
};

/*
 * C_EngineVGUI
 * EngineVGUI Interface.
 */
class C_EngineVGUI
{
public:
};

/*
 * C_VGUISurface
 * VGUISurface Interface.
 */
class C_VGUISurface
{
public:

	/*
	 * set_draw_colour
	 * Sets draw colour
	 */
	void set_draw_colour(Colour colour)
	{
		vtable<void(__thiscall*)(void*, int, int, int, int)>(this, 15)(this, colour.r, colour.g, colour.b, colour.a);
	}

	/*
	 * set_text_colour
	 * Sets text colour
	 */
	void set_text_colour(Colour colour)
	{
		vtable<void(__thiscall*)(void*, int, int, int, int)>(this, 25)(this, colour.r, colour.g, colour.b, colour.a);
	}

	VFUNCTION(23, void, set_text_font, unsigned long font)
	VFUNCTION(26, void, set_text_pos, int x, int y)
	VFUNCTION(71, unsigned long, reserve_font_handle)
	VFUNCTION(43, int, create_texture, bool proc)
	VFUNCTION(72, void, set_font_glyph_set, unsigned long font, const char* name, int tall, int weight, int blur, int scanlines, FontFlags_t flags, int range_min = 0, int range_max = 0)
	VFUNCTION(79, void, get_text_size, unsigned long font, const wchar_t* text, int& w, int& h)
	VFUNCTION(28, void, draw_string, const wchar_t* text, int size, int unk = 0)
	VFUNCTION(19, void, draw_line, int x, int y, int x1, int y1)

	/*
	 * draw_filled_rect
	 * Draws a filled rectangle
	 */
	void draw_filled_rect(int x, int y, int w, int h)
	{
		vtable<void(__thiscall*)(void*, int, int, int, int)>(this, 16)(this, x, y, w + x, h + y);
	}

	/*
	 * draw_outlined_rect
	 * Draws a outlined rectangle
	 */
	void draw_outlined_rect(int x, int y, int w, int h)
	{
		vtable<void(__thiscall*)(void*, int, int, int, int)>(this, 18)(this, x, y, w + x, h + y);
	}

	/*
	 * draw_string
	 * Draws a string
	 */
	void draw_string(int x, int y, unsigned long ulFont, Colour colour, std::string chText, ...)
	{
		char chMergedBuffer[1024];
		chMergedBuffer[0] = '\0';

		va_list vlist;
		__crt_va_start(vlist, chText);
		size_t len = vsprintf_s(chMergedBuffer, chText.c_str(), vlist);
		__crt_va_end(vlist);

		auto wchar = new wchar_t[len + 1];
		mbstowcs(wchar, chMergedBuffer, len + 1);

		set_text_colour(colour);
		set_text_font(ulFont);
		set_text_pos(x, y);
		draw_string(wchar, len);

		delete[] wchar;
	}

	/*
	 * get_text_size
	 * Returns the text width
	 */
	void get_text_size(unsigned long ulFont, int& _w, int& _h, std::string chText, ...)
	{
		char chMergedBuffer[1024];
		chMergedBuffer[0] = '\0';

		va_list vlist;
		__crt_va_start(vlist, chText);
		size_t len = vsprintf_s(chMergedBuffer, chText.c_str(), vlist);
		__crt_va_end(vlist);

		auto wchar = new wchar_t[len + 1];
		mbstowcs(wchar, chMergedBuffer, len + 1);

		int iW, iH;
		get_text_size(ulFont, wchar, iW, iH);

		_w = iW;
		_h = iH;

		delete[] wchar;
	}

	/*
	 * draw_string
	 * Draws a string
	 */
	void draw_string(int x, int y, unsigned long ulFont, StringAlign_t eAlign, Colour colour, std::string chText, ...)
	{
		char chMergedBuffer[1024];
		chMergedBuffer[0] = '\0';

		va_list vlist;
		__crt_va_start(vlist, chText);
		size_t len = vsprintf_s(chMergedBuffer, chText.c_str(), vlist);
		__crt_va_end(vlist);

		auto wchar = new wchar_t[len + 1];
		mbstowcs(wchar, chMergedBuffer, len + 1);

		int iW, iH;
		get_text_size(ulFont, wchar, iW, iH);

		switch (eAlign)
		{
			case TEXT_ALIGN_CENTER:
				x -= iW / 2;
				break;
			case TEXT_ALIGN_RIGHT:
				x -= iW;
				break;
			case TEXT_ALIGN_CENTER_CENTER:
				x -= iW / 2;
				y -= iH / 2;
				break;
			case TEXT_ALIGN_CENTER_TOP:
				x -= iW / 2;
				y -= iH;
				break;
			case TEXT_ALIGN_CENTER_BOT:
				x -= iW / 2;
				y += iH;
				break;
			case TEXT_ALIGN_LEFT_CENTER:
				y -= iH / 2;
				break;
			case TEXT_ALIGN_LEFT_TOP:
				y -= iH;
				break;
			case TEXT_ALIGN_LEFT_BOT:
				y += iH;
				break;
			case TEXT_ALIGN_RIGHT_CENTER:
				x -= iW;
				y -= iH / 2;
				break;
			case TEXT_ALIGN_RIGHT_TOP:
				x -= iW;
				y -= iH;
				break;
			case TEXT_ALIGN_RIGHT_BOT:
				x -= iW;
				y += iH;
				break;
			default: break;
		}

		set_text_colour(colour);
		set_text_font(ulFont);
		set_text_pos(x, y);
		draw_string(wchar, len);

		delete[] wchar;
	}
};

/*
 * C_InputSystem
 * Input Class
 */
class C_InputSystem
{
public:

	VFUNCTION(11, void, input_enabled, bool enabled)
};

/*
 * C_ClientMode
 * ClientMode Class
 */
class C_ClientMode
{
public:
};

/*
 * C_EngineTrace
 * EngineTrace Interface
 */
class C_EngineTrace
{
public:

	VFUNCTION(0, int, get_point_contents, const Vector3& end_position, int mask, C_BaseEntity** entity);
	VFUNCTION(3, void, clip_ray_to_entity, ray& _ray, int mask, C_BaseEntity* entity, C_Trace* trace)
	VFUNCTION(5, void, trace_ray, ray& _ray, int mask, C_TraceFilter* filter, C_Trace* trace)

	/*
	 * trace
	 * Traces a ray in a simple state
	 */
	C_Trace trace(Vector3 start, Vector3 end, int mask, C_BaseEntity* filter = nullptr)
	{
		C_Trace _trace;
		C_TraceFilter _filter(filter, TRACE_EVERYTHING);

		trace_ray(ray(start, end), mask, &_filter, &_trace);

		return _trace;
	}
};

/*
 * C_Material
 * Material Class
 */
class C_Material
{
public:
	VFUNCTION(0, const char*, get_name)
	VFUNCTION(1, const char*, get_texture_group_name)
	VFUNCTION(12, void, increment_reference_count)
	VFUNCTION(27, void, alpha_modulate, float a)
	VFUNCTION(28, void, colour_modulate, float r, float g, float b)
	VFUNCTION(29, void, set_material_var_flag, material_flags flags, bool unk0)
	VFUNCTION(30, void, get_material_var_flag, material_flags flags)
	VFUNCTION(44, float, get_alpha_modulate)
	VFUNCTION(45, void, get_colour_modulation, float* r, float* g, float* b)
};

/*
 * C_MaterialSystem
 * MaterialSystem Class
 */
class C_MaterialSystem
{
public:
	VFUNCTION(83, C_Material*, create_material, const char* name, C_KeyValues* key_values)
	VFUNCTION(84, C_Material*, find_material, const char* unk0, const char* unk1, bool unk2, bool unk3)
	VFUNCTION(86, unsigned short, first_material)
	VFUNCTION(87, unsigned short, next_material, unsigned short h)
	VFUNCTION(88, unsigned short, invalid_material)
	VFUNCTION(89, C_Material*, get_material, unsigned short h)
};

/*
 * C_ModelInfo
 * ModelInfo Class
 */
class C_ModelInfo
{
public:

	VFUNCTION(30, studio_hdr*, get_studio_model, const C_Model* model)
	VFUNCTION(3, const char*, get_model_name, const C_Model* model)
	VFUNCTION(17, void, get_model_materials, C_Model* model, int unk0, C_Material** material)
};

/*
 * C_ModelRender
 * ModelRender Class
 */
class C_ModelRender
{
public:
	VFUNCTION(1, void, force_material_override, C_Material* material, override_type type = OVERRIDE_NORMAL, int b0 = 0)
};

/*
 * C_StudioRender
 * StudioRender Class
 */
class C_StudioRender
{
public:
	VFUNCTION(33, void, force_material_override, C_Material* material, override_type type = OVERRIDE_NORMAL, int b0 = 0)
};

/*
 * C_RenderView
 * RenderView Class
 */
class C_RenderView
{
public:
	VFUNCTION(4, void, set_blend, float blend)

	void set_colour_modulation(Colour colour)
	{
		float array[3] = {colour.r / 255.f, colour.g / 255.f, colour.b / 255.f};
		vtable<void(__thiscall*)(void*, const float*)>(this, 6)(this, array);
	}
};

/*
 * C_CmdInput
 * CmdInput Class
 */
class C_CmdInput
{
public:
	void* pvftable; //0x00
	bool m_fTrackIRAvailable; //0x04
	bool m_fMouseInitialized; //0x05
	bool m_fMouseActive; //0x06
	bool m_fJoystickAdvancedInit; //0x07
	PAD(0x2C) //0x08
	void* m_pKeys; //0x34
	PAD(0x64) //0x38
	int pad_0x41;
	int pad_0x42;
	bool m_fCameraInterceptingMouse; //0x9C
	bool m_fCameraInThirdPerson; //0x9D
	bool m_fCameraMovingWithMouse; //0x9E
	Vector3 m_vecCameraOffset; //0xA0
	bool m_fCameraDistanceMove; //0xAC
	int m_nCameraOldX; //0xB0
	int m_nCameraOldY; //0xB4
	int m_nCameraX; //0xB8
	int m_nCameraY; //0xBC
	bool m_CameraIsOrthographic; //0xC0
	Vector3 m_angPreviousViewAngles; //0xC4
	Vector3 m_angPreviousViewAnglesTilt; //0xD0
	float m_flLastForwardMove; //0xDC
	int m_nClearInputState; //0xE0
	PAD(0x8) //0xE4
	C_UserCmd* m_pCommands; //0xEC
	void* m_pVerifiedCommands; //0xF0
public:
	VFUNCTION(32, int, cam_isthirdperson, int slot = -1)
};

/*
 * C_EventManager
 * Event Manager Class
 */
class C_EventManager
{
public:
};

/*
 * C_GameEvent
 * Game Event Class
 */
class C_GameEvent
{
public:
	virtual ~C_GameEvent()
	{
	}

	// TODO: Change from sdk reversed class to a VFUNCTION macro set
	virtual const char* GetName() const = 0;
	virtual bool IsReliable() const = 0;
	virtual bool IsLocal() const = 0;
	virtual bool IsEmpty(const char* keyName = nullptr) = 0;
	virtual bool GetBool(const char* keyName = nullptr, bool defaultValue = false) = 0;
	virtual int GetInt(const char* keyName = nullptr, int defaultValue = 0) = 0;
	virtual float GetFloat(const char* keyName = nullptr, float defaultValue = 0.0f) = 0;
	virtual const char* GetString(const char* keyName = nullptr, const char* defaultValue = "") = 0;
	virtual void SetBool(const char* keyName, bool value) = 0;
	virtual void SetInt(const char* keyName, int value) = 0;
	virtual void SetFloat(const char* keyName, float value) = 0;
	virtual void SetString(const char* keyName, const char* value) = 0;
};

/*
 * C_MatchFramework
 * Match Framework Class
 */
class C_MatchFramework
{
public:
};

/*
 * C_PhysicsSurface
 * Physics Surface Class
 */
class C_PhysicsSurface
{
public:
	VFUNCTION(5, surface_data*, get_surface_data, int index);
};

/*
 * C_InterfaceList
 * Interface list where all interfaces are defined
 */

class C_InterfaceList
{
public:
	C_InterfaceScanner scanner;

	// Interfaces
	C_EngineClient* engine;
	C_Client* client;
	C_ClientEntityList* entitylist;
	C_EngineCvar* cvar;
	C_ClientPrediction* prediction;
	C_GameMovement* movement;
	C_MoveHelper* movehelper;
	C_Panel* panel;
	C_EngineVGUI* vgui;
	C_VGUISurface* surface;
	C_InputSystem* input;
	C_GlobalData* globaldata;
	C_ClientMode* clientmode;
	C_EngineTrace* trace;
	C_MaterialSystem* materialsystem;
	C_ModelInfo* modelinfo;
	C_ModelRender* modelrender;
	C_StudioRender* studiorender;
	C_RenderView* renderview;
	C_CmdInput* cmdinput;
	C_EnginePointerToClientState* clientstate;
	C_EventManager* eventmanager;
	C_MatchFramework* matchframework;
	C_PhysicsSurface* physicssurface;

	C_LagCompensation* lagcompensation;
	C_Resolver* resolver;
	C_WalkBot* walkbot;
	C_Configurations* data;
};
