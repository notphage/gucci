// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017D
// *********************************

#pragma once

extern void __fastcall paint_hook(void* ecx, void*, PaintMode_t mode);
extern bool __fastcall createmove_hook(void* ecx, void* edx, float sequence, C_UserCmd* cmd);
extern void __fastcall framestagenotify_hook(void* ecx, void* edx, frame_stage stage);
extern void __stdcall overrideview_hook(C_ViewSetup* view_setup);
extern bool __fastcall inprediction_hook(void* ecx, void*);
extern void __stdcall runcommand_hook(C_BaseEntity* entity, C_UserCmd* cmd, void* move_helper);
extern bool __fastcall firegameevent_hook(void* ecx, void* edx, C_GameEvent* game_event);
extern void* __stdcall get_match_session_hook();
extern void __fastcall draw_model_hook(void* ecx, void*, void* results, const draw_model_info& info, Matrix3x4* bone_to_world, float* flex_weights, float* flex_delayed_weights, const Vector3& model_origin, int flags);

/*
* C_HookList
* Hook list where all hooks are defined
*/
class C_HookList
{
public:
	C_HookManager manager;

	// Paint
	typedef void (__thiscall *fnPaint)(void* ecx, PaintMode_t mode);
	fnPaint oPaint;
	C_PaintManager paint;

	// CreateMove
	typedef bool (__fastcall *fnCreateMove)(void* ecx, void* edx, float sequence, C_UserCmd* cmd);
	fnCreateMove oCreateMove;
	C_CreateMove createmove;

	// FrameStageNotify
	typedef void (__thiscall *fnFrameStageNotify)(void* ecx, frame_stage stage);
	fnFrameStageNotify oFrameStageNotify;

	// OverrideView
	typedef void (__stdcall *fnOverrideView)(C_ViewSetup* view_setup);
	fnOverrideView oOverrideView;

	// InPrediction
	typedef bool (__fastcall *fnInPrediction)(void* ecx);
	fnInPrediction oInPrediction;

	// RunCommand
	typedef void (__stdcall *fnRunCommand)(C_BaseEntity* entity, C_UserCmd* cmd, void* move_helper);
	fnRunCommand oRunCommand;

	// FireGameEvent
	typedef bool (__fastcall *fnFireGameEvent)(void* ecx, void* edx, C_GameEvent* game_event);
	fnFireGameEvent oFireGameEvent;

	// GetMatchSession
	typedef void*(__stdcall *fnGetMatchSession)();
	fnGetMatchSession oGetMatchSession;

	// DrawModel
	typedef void (__thiscall* fnDrawModel)(void*, void*, const draw_model_info&, Matrix3x4*, float*, float*, const Vector3&, int);
	fnDrawModel oDrawModel;
};
