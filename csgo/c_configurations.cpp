// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * register_handle
 */
void C_Configurations::register_data(std::string name, DWORD* address)
{
	if (address == nullptr)
		return;

	data[Crypto::CRC::crc(name.c_str())] = address;
}

/*
 * save_data
 */
void C_Configurations::save_data(std::string name)
{
	//std::ofstream output;

	//output.open(name.c_str(), std::ios::out | std::ios_base::app);

	//if (output.fail())
	//	return;

	for (auto element : data)
	{
		std::cout << element.first << " " << element.second << std::endl;
	}
}
