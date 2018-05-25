// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once
#include "framework.hpp"

class C_Address
{
	uintptr_t uAddress;
public:
	template <typename T>
	explicit C_Address(T ObjectLocation)
	{
		uAddress = reinterpret_cast<uintptr_t>(ObjectLocation);
	}

	uintptr_t get_address() const;
	bool is_valid_address() const;
	uint8_t at(int iOffset) const;
};
