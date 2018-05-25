// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "c_address.h"

uintptr_t C_Address::get_address() const
{
	return uAddress;
}

bool C_Address::is_valid_address() const
{
	return uAddress != static_cast<uintptr_t>(0);
}

uint8_t C_Address::at(int iOffset) const
{
	return *reinterpret_cast<uint8_t*>(uAddress + iOffset);
}
