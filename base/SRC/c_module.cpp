// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "c_module.h"
#include "c_address.h"
#include "TlHelp32.h"

void C_Module::dump_module_list(DWORD ProccessID)
{
	MODULEENTRY32 me32;

	auto hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProccessID);
	if (hModuleSnap == INVALID_HANDLE_VALUE)
		return;

	me32.dwSize = sizeof(MODULEENTRY32);

	if (!Module32First(hModuleSnap, &me32))
	{
		CloseHandle(hModuleSnap);
		return;
	}

	do
	{
		HINSTANCE__* pModule;

		// Sanity Check
		do
			pModule = GetModuleHandleA(me32.szModule);
		while (!pModule);

		modules.insert_or_assign(me32.szModule, pModule);
	}
	while (Module32Next(hModuleSnap, &me32));

	CloseHandle(hModuleSnap);
}

std::map<std::string, HINSTANCE__*> C_Module::get_loaded_modules() const
{
	return modules;
}

bool C_Module::is_valid_export(C_Address Address)
{
	return Address.is_valid_address() && Address.at(0x4) == 0xE9 && Address.at(0x9) == 0xCC;
}

HINSTANCE__* C_Module::get_loaded_module_handle(std::string Module)
{
	for (auto module : modules)
	{
		if (module.first == Module)
			return module.second;
	}

	return nullptr;
}

uintptr_t C_Module::get_export(std::string Module, std::string Export)
{
	auto pModule = get_loaded_module_handle(Module);

	auto fnExport = C_Address(GetProcAddress(pModule, Export.c_str()));

	return is_valid_export(fnExport) ? fnExport.get_address() : static_cast<uintptr_t>(0);
}

uintptr_t C_Module::get_export(HINSTANCE__* Module, std::string Export)
{
	auto fnExport = C_Address(GetProcAddress(Module, Export.c_str()));

	return is_valid_export(fnExport) ? fnExport.get_address() : static_cast<uintptr_t>(0);
}
