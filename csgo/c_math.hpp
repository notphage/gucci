// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

#define PI 3.14159265358979323846f

class C_Math
{
public:
	static void random_seed(int seed);
	static float random_float(float min, float max);
	static bool world_2_screen(const Vector3& world, Vector3& screen);
	static Vector3 vector_transform(Vector3 vector, Matrix3x4 matrix);
	void sin_cos(float radian, float* sin, float* cos) const;
	void angle_vectors(const Angle& angles, Vector3* forward = nullptr, Vector3* right = nullptr, Vector3* up = nullptr) const;
	void vector_angles(const Vector3& forward, Angle& angles) const;
	static void transform_matrix(Vector3 input, Matrix3x4 matrix, Vector3& output);
	static Angle calc_angle(Vector3 vec1, Vector3 vec2);
	static Vector3 calc_hitbox(Matrix3x4 matrix[128], studio_bbox* hitbox, Vector3 offset = Vector3());
	void angle_matrix(const Angle& angles, Matrix3x4& matrix) const;
	float dot_product(Vector3 a, Vector3 b) const;
	void vector_rotate(const Vector3& in1, const Angle& in2, Vector3& out) const;
	float normalize_angle(float angle) const;

	/*
	 * rad_2_deg
	 * Converts a radian to a degree
	 */
	static constexpr float C_Math::rad_2_deg(float radian)
	{
		return radian * (180.f / PI);
	}

	/*
	 * deg_2_rad
	 * Converts a degree to a radian
	 */
	static constexpr float C_Math::deg_2_rad(float degree)
	{
		return degree * (PI / 180.f);
	}
};
