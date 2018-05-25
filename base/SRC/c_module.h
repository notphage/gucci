// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once
#include "framework.hpp"

class C_Address;

class C_Module
{
	std::map<std::string, HINSTANCE__*> modules;

	static bool is_valid_export(C_Address Address);
public:
	void dump_module_list(DWORD ProccessID = GetCurrentProcessId());
	std::map<std::string, HINSTANCE__*> get_loaded_modules() const;
	HINSTANCE__* get_loaded_module_handle(std::string Module);
	uintptr_t get_export(std::string Module, std::string Export);
	static uintptr_t get_export(HINSTANCE__* Module, std::string Export);
};
