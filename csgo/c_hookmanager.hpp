// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

/*
 * C_HookManager
 * For hooking virtual functions and memory to other memory / functions
 */
class C_HookManager
{
public:
	template <typename T>
	static T hook_vtable(void* pOriginal, void* pNew, int iIndex);
	static void start();
};
