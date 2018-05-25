// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class Angle
{
public:
	float p, y, r;

	constexpr explicit Angle(float _x = 0.f, float _y = 0.f, float _z = 0.f) : p(_x), y(_y), r(_z)
	{
	}

	constexpr explicit Angle(const float* v) : p(v[0]), y(v[1]), r(v[2])
	{
	}

	~Angle()
	{
	}

	auto empty() const -> bool
	{
		return p == 0.f && y == 0.f && r == 0.f;
	}

	auto clear() -> void
	{
		p = 0.f;
		y = 0.f;
		r = 0.f;
	}

	auto operator==(const Angle& other) const -> bool
	{
		return (p == other.p && y == other.y && r == other.r);
	}

	auto operator!=(const Angle& other) const -> bool
	{
		return !(*this == other);
	}

	auto operator[](int i) -> float&


	
	{
		return reinterpret_cast<float*>(this)[i];
	}

	auto operator[](int i) const -> float
	{
		return ((float*)this)[i];
	}

	template <typename A>
	auto operator+(A other) const -> Angle
	{
		auto buf = *this;
		buf += static_cast<float>(other);
		return buf;
	}

	template <typename A>
	auto operator-(A other) const -> Angle
	{
		auto buf = *this;
		buf -= static_cast<float>(other);
		return buf;
	}

	template <typename A>
	auto operator*(A other) const -> Angle
	{
		auto buf = *this;
		buf *= static_cast<float>(other);
		return buf;
	}

	template <typename A>
	auto operator/(A other) const -> Angle
	{
		auto buf = *this;
		buf /= static_cast<float>(other);
		return buf;
	}

	template <typename A>
	auto operator+=(A other) -> Angle&


	
	{
		p += static_cast<float>(other);
		y += static_cast<float>(other);
		r += static_cast<float>(other);

		return *this;
	}

	template <typename A>
	auto operator-=(A other) -> Angle&


	
	{
		p -= static_cast<float>(other);
		y -= static_cast<float>(other);
		r -= static_cast<float>(other);

		return *this;
	}

	template <typename A>
	auto operator*=(A other) -> Angle&


	
	{
		p *= static_cast<float>(other);
		y *= static_cast<float>(other);
		r *= static_cast<float>(other);

		return *this;
	}

	template <typename A>
	auto operator/=(A other) -> Angle&


	
	{
		p /= static_cast<float>(other);
		y /= static_cast<float>(other);
		r /= static_cast<float>(other);

		return *this;
	}

	auto operator+(const Angle& other) const -> Angle
	{
		auto buf = *this;

		buf.p += other.p;
		buf.y += other.y;
		buf.r += other.r;

		return buf;
	}

	auto operator-(const Angle& other) const -> Angle
	{
		auto buf = *this;

		buf.p -= other.p;
		buf.y -= other.y;
		buf.r -= other.r;

		return buf;
	}

	auto operator+=(const Angle& other) -> Angle&


	
	{
		p += other.p;
		y += other.y;
		r += other.r;

		return (*this);
	}

	auto operator-=(const Angle& other) -> Angle&


	
	{
		p -= other.p;
		y -= other.y;
		r -= other.r;

		return (*this);
	}

	auto length_2d() const -> float
	{
		return sqrt(length_sqr_2d());
	}

	auto length_sqr_2d() const -> float
	{
		return p * p + y * y;
	}

	auto length() const -> float
	{
		return sqrt(length_sqr());
	}

	auto length_sqr() const -> float
	{
		return p * p + y * y + r * r;
	}

	auto distance(const Angle& other) const -> float
	{
		return (other - (*this)).length();
	}

	auto is_oob() const -> bool
	{
		return fabs(p) > 89.f || fabs(y) > 180.f || fabs(r) > 0.f;
	}

	auto clamp() -> void
	{
		p = std::clamp(p, -89.f, 89.f);
		y = std::clamp(y, -180.f, 180.f);
		r = 0.f;
	}

	//auto normalize() -> void
	//{
	//	auto& angle = *this;
	//
	//	for (auto i = 0; i <= 2; i++)
	//	{
	//		if (angle[i] > 180.f || angle[i] < -180.f)
	//		{
	//			auto revolutions = round(abs(angle[i] / 360.f));
	//
	//			if (angle[i] < 0.f)
	//				angle[i] = angle[i] + 360.f * revolutions;
	//			else
	//				angle[i] = angle[i] - 360.f * revolutions;
	//		}
	//	}
	//}

	auto normalize() -> void
	{
		auto& angle = *this;

		for (auto i = 0; i <= 2; i++)
			if (angle[i] > 180.f || angle[i] < -180.f)
				angle[i] = (angle[i] < 0.f) ? angle[i] + 360.f * round(abs(angle[i] / 360.f)) : angle[i] - 360.f * round(abs(angle[i] / 360.f));
	}

	auto normalized() const -> Angle
	{
		auto vec = *this;
		vec.normalize();
		return vec;
	}

	friend std::ostream& operator<<(std::ostream& os, const Angle& v)
	{
		os << v.p << "\t" << v.y << "\t" << v.r << std::endl;

		return os;
	}
};
