// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_Configurations
{
public:
	std::unordered_map<uint64_t, DWORD*> data;

	void register_data(std::string name, DWORD* address);
	void save_data(std::string name);
};
