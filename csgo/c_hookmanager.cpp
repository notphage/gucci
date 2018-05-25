// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * hook_vtable
 * Used to modify a specific function in a vtable and overwrite its function to the new function specified.
 */
template <typename T>
T C_HookManager::hook_vtable(void* pOriginal, void* pNew, int iIndex)
{
	if (pOriginal == nullptr || pNew == nullptr)
		return nullptr;

	DWORD pBackupProtection;
	auto pOriginalVirtual = *static_cast<DWORD*>(pOriginal) + 4 * iIndex;
	auto pBackupFunc = reinterpret_cast<void*>(*reinterpret_cast<DWORD*>(pOriginalVirtual));

	VirtualProtect(reinterpret_cast<void*>(pOriginalVirtual), 4, 0x40, &pBackupProtection);
	*reinterpret_cast<DWORD*>(pOriginalVirtual) = reinterpret_cast<DWORD>(pNew);
	VirtualProtect(reinterpret_cast<void*>(pOriginalVirtual), 4, pBackupProtection, &pBackupProtection);

	G::console.print("0x%X ", pBackupFunc);
	G::console.print("-> ");
	G::console.print(eColour::GREEN, "0x%X\n", pNew);

	return static_cast<T>(pBackupFunc);
}

/*
 * start
 * Hooks all functions to what ever memory we are going to flash them to.
 */
void C_HookManager::start()
{
	G::console.print("\n-> Hook Functions\n\n");

	G::hooks.oPaint = G::hooks.manager.hook_vtable<C_HookList::fnPaint>(G::interfaces.vgui, paint_hook, 14);
	G::hooks.oCreateMove = G::hooks.manager.hook_vtable<C_HookList::fnCreateMove>(G::interfaces.clientmode, createmove_hook, 24);
	G::hooks.oFrameStageNotify = G::hooks.manager.hook_vtable<C_HookList::fnFrameStageNotify>(G::interfaces.client, framestagenotify_hook, 36);
	G::hooks.oOverrideView = G::hooks.manager.hook_vtable<C_HookList::fnOverrideView>(G::interfaces.clientmode, overrideview_hook, 18);
	G::hooks.oInPrediction = G::hooks.manager.hook_vtable<C_HookList::fnInPrediction>(G::interfaces.prediction, inprediction_hook, 14);
	G::hooks.oRunCommand = G::hooks.manager.hook_vtable<C_HookList::fnRunCommand>(G::interfaces.prediction, runcommand_hook, 19);
	G::hooks.oFireGameEvent = G::hooks.manager.hook_vtable<C_HookList::fnFireGameEvent>(G::interfaces.eventmanager, firegameevent_hook, 9);
	G::hooks.oDrawModel = G::hooks.manager.hook_vtable<C_HookList::fnDrawModel>(G::interfaces.studiorender, draw_model_hook, 29);
	//G::hooks.oGetMatchSession = G::hooks.manager.hook_vtable<C_HookList::fnGetMatchSession>(G::interfaces.matchframework, get_match_session_hook, 13);
}
