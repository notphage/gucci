// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * random_seed
 * Sets the random seed
 */
void C_Math::random_seed(int seed)
{
	static auto random_seed = reinterpret_cast<void(*)(int)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed"));

	random_seed(seed);
}

/*
 * random_float
 * Generates a random float
 */
float C_Math::random_float(float min, float max)
{
	static auto random_float = reinterpret_cast<float(*)(float, float)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomFloat"));

	return random_float(min, max);
}

/*
 * world_2_screen
 * Converts a world vector to a screen vector
 */
bool C_Math::world_2_screen(const Vector3& world, Vector3& screen)
{
	auto matrix = G::interfaces.engine->world_to_screen_matrix();

	screen = Vector3(matrix[0][0] * world.x + matrix[0][1] * world.y + matrix[0][2] * world.z + matrix[0][3], matrix[1][0] * world.x + matrix[1][1] * world.y + matrix[1][2] * world.z + matrix[1][3], 0.f);

	auto w = matrix[3][0] * world.x + matrix[3][1] * world.y + matrix[3][2] * world.z + matrix[3][3];

	if (w < 0.001f)
		return false;

	screen /= w;

	int width, height;
	G::interfaces.engine->get_screen_size(width, height);

	screen = Vector3(width / 2.f + screen.x * width / 2.f, height / 2.f - screen.y * height / 2.f, 0.f);

	return true;
}

/*
  * vector_transform
  * Transforms a vector to a matrix
  */
Vector3 C_Math::vector_transform(Vector3 vector, Matrix3x4 matrix)
{
	return Vector3(vector.dot(matrix[0]) + matrix[0][3], vector.dot(matrix[1]) + matrix[1][3], vector.dot(matrix[2]) + matrix[2][3]);
}

/*
 * sin_cos
 * Returns the sin and cosine of a given radian
 */
void C_Math::sin_cos(float radian, float* sin, float* cos) const
{
	*sin = std::sin(radian);
	*cos = std::cos(radian);
}

/*
 * angle_vectors
 * Converts a angle to a vector
 */
void C_Math::angle_vectors(const Angle& angles, Vector3* forward, Vector3* right, Vector3* up) const
{
	float sp, sy, sr, cp, cy, cr;

	sin_cos(deg_2_rad(angles.p), &sp, &cp);
	sin_cos(deg_2_rad(angles.y), &sy, &cy);
	sin_cos(deg_2_rad(angles.r), &sr, &cr);

	if (forward != nullptr)
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right != nullptr)
	{
		right->x = -1 * sr * sp * cy + -1 * cr * -sy;
		right->y = -1 * sr * sp * sy + -1 * cr * cy;
		right->z = -1 * sr * cp;
	}

	if (up != nullptr)
	{
		up->x = cr * sp * cy + -sr * -sy;
		up->y = cr * sp * sy + -sr * cy;
		up->z = cr * cp;
	}
}

/*
 * vector_angles
 * Converts a vector to a angle
 */
void C_Math::vector_angles(const Vector3& forward, Angle& angles) const
{
	if (forward.x == 0.f && forward.y == 0.f)
	{
		angles.p = forward.z > 0.f ? -90.f : 90.f;
		angles.y = 0.f;
	}
	else
	{
		angles.p = G::math.rad_2_deg(atan2(-forward.z, forward.length_2d()));
		angles.y = G::math.rad_2_deg(atan2(forward.y, forward.x));
	}

	angles.r = 0.f;
}

/*
 * transform_matrix
 * Transforms a matrix
 */
void C_Math::transform_matrix(Vector3 input, Matrix3x4 matrix, Vector3& output)
{
	output.x = input.dot(matrix[0]) + matrix[0][3];
	output.y = input.dot(matrix[1]) + matrix[1][3];
	output.z = input.dot(matrix[2]) + matrix[2][3];
}

/*
 * calc_angle
 * Calculates an angle from 2 given vectors
 */
Angle C_Math::calc_angle(Vector3 vec1, Vector3 vec2)
{
	Angle angle;
	G::math.vector_angles((vec2 - vec1).normalized(), angle);

	return angle.normalized();
}


/*
 * calc_hitbox
 * Calculates a hitbox from its bbox
 */
Vector3 C_Math::calc_hitbox(Matrix3x4 matrix[128], studio_bbox* hitbox, Vector3 offset)
{
	Vector3 min, max;
	transform_matrix(hitbox->m_mins, matrix[hitbox->m_bone], min);
	transform_matrix(hitbox->m_maxs, matrix[hitbox->m_bone], max);

	return (min + max) / 2.f + offset;
}

/*
 * angle_matrix
 * Converts an angle to a matrix
 */
void C_Math::angle_matrix(const Angle& angles, Matrix3x4& matrix) const
{
	float sr, sp, sy, cr, cp, cy;

	sin_cos(G::math.deg_2_rad(angles.p), &sp, &cp);
	sin_cos(G::math.deg_2_rad(angles.y), &sy, &cy);
	sin_cos(G::math.deg_2_rad(angles.r), &sr, &cr);

	matrix[0][0] = cp * cy;
	matrix[1][0] = cp * sy;
	matrix[2][0] = -sp;

	auto crcy = cr * cy, crsy = cr * sy, srcy = sr * cy, srsy = sr * sy;

	matrix[0][1] = sp * srcy - crsy;
	matrix[1][1] = sp * srsy + crcy;
	matrix[2][1] = sr * cp;

	matrix[0][2] = (sp * crcy + srsy);
	matrix[1][2] = (sp * crsy - srcy);
	matrix[2][2] = cr * cp;

	matrix[0][3] = 0.f;
	matrix[1][3] = 0.f;
	matrix[2][3] = 0.f;
}

/*
 * dot_product
 * Performs a dot product on 2 given vectors
 */
float C_Math::dot_product(Vector3 a, Vector3 b) const
{
	float one[] = {a.x, a.y, a.z};
	float two[] = {b.x, b.y, b.z};

	return std::inner_product(one, one + 3, two, 0.f);
}

/*
 * vector_rotate
 * Mathmatically rotates a vector
 */
void C_Math::vector_rotate(const Vector3& in1, const Angle& in2, Vector3& out) const
{
	auto rotate = [](const Vector3& _in1, const Matrix3x4& _in2, Vector3& _out)
			{
				auto dot_product = [](const Vector3& v1, const float* v2)
						{
							return v1.x * v2[0] + v1.y * v2[1] + v1.z * v2[2];
						};

				_out.x = dot_product(_in1, _in2[0]);
				_out.y = dot_product(_in1, _in2[1]);
				_out.z = dot_product(_in1, _in2[2]);
			};

	Matrix3x4 matrix;
	angle_matrix(in2, matrix);
	rotate(in1, matrix, out);
}

/*
 * normalize_angle
 * Normalizes a angle
 */
float C_Math::normalize_angle(float angle) const
{
	if (angle > 180.f || angle < -180.f)
	{
		auto revolutions = round(abs(angle / 360.f));

		if (angle < 0.f)
			angle = angle + 360.f * revolutions;
		else
			angle = angle - 360.f * revolutions;
	}

	return angle;
}
