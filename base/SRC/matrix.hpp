// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class Matrix3x4
{
public:
	float* operator[](int i) { return m[i]; }
	const float* operator[](int i) const { return m[i]; }

	float m[3][4];
};

class Matrix4x4
{
public:
	float* operator[](int i) { return m[i]; }
	const float* operator[](int i) const { return m[i]; }

	float m[4][4];
};
