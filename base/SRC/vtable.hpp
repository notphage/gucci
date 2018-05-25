// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

// Calls a virtual
#define VFUNCTION(z, x, y, ...) x y##(__VA_ARGS__)\
	{ \
	    _asm mov eax, dword ptr[ecx]\
	    _asm mov edx, z\
	    _asm imul edx, 4\
	    _asm mov eax, dword ptr[eax + edx]\
	    _asm pop ebp\
	    _asm pop ebp\
	    _asm jmp eax\
	}

// Creates a offset
#define VOFFSET_NR(x, y, z) x y()\
	{ \
		return this + z;\
	}

// Creates a read offset
#define VOFFSET(x, y, z) x y()\
	{ \
		return read<x>(z);\
	}

// Creates a read/write offset
#define VOFFSET_A(x, y, z) x& y()\
	{ \
		return read<x>(z);\
	}

/*
 * vtable
 * Used to create a template function link
 */
template <typename T>
T vtable(void* pAddr, int iIndex)
{
	return (*reinterpret_cast<T**>(pAddr))[iIndex];
}
