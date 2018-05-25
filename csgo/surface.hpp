// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017D
// *********************************

#pragma once

/*
 * C_Plane
 */
struct C_Plane
{
	Vector3 normal;
	float dist;
	byte type;
	byte signbits;
	PAD(2)
};

/*
 * C_Surface
 */
struct C_Surface
{
	const char* name;
	short surface_props;
	unsigned short flags;
};
