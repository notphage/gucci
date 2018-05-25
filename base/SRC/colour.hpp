// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class Colour
{
public:
	uint8_t r, g, b, a;

	constexpr explicit Colour(uint8_t _r = 255, uint8_t _g = 255, uint8_t _b = 255, uint8_t _a = 255) : r(_r), g(_g), b(_b), a(_a)
	{
	}

	constexpr explicit Colour(const uint8_t* v) : r(v[0]), g(v[1]), b(v[2]), a(v[3])
	{
	}

	~Colour()
	{
	}

	auto empty() const -> bool
	{
		return r == 0 && g == 0 && b == 0 && a == 0;
	}

	auto clear() -> void
	{
		r = 0;
		g = 0;
		b = 0;
		a = 0;
	}

	auto operator==(const Colour& other) const -> bool
	{
		return (r == other.r && g == other.g && b == other.b && a == other.a);
	}

	auto operator!=(const Colour& other) const -> bool
	{
		return !(*this == other);
	}

	template <typename A>
	auto operator+(A other) const -> Colour
	{
		auto buf = *this;
		buf += static_cast<uint8_t>(other);
		return buf;
	}

	template <typename A>
	auto operator-(A other) const -> Colour
	{
		auto buf = *this;
		buf -= static_cast<uint8_t>(other);
		return buf;
	}

	template <typename A>
	auto operator*(A other) const -> Colour
	{
		auto buf = *this;
		buf *= static_cast<uint8_t>(other);
		return buf;
	}

	template <typename A>
	auto operator/(A other) const -> Colour
	{
		auto buf = *this;
		buf /= static_cast<uint8_t>(other);
		return buf;
	}

	template <typename A>
	auto operator+=(A other) -> Colour&


	
	{
		r += static_cast<uint8_t>(other);
		g += static_cast<uint8_t>(other);
		b += static_cast<uint8_t>(other);
		a += static_cast<uint8_t>(other);

		return *this;
	}

	template <typename A>
	auto operator-=(A other) -> Colour&


	
	{
		r -= static_cast<uint8_t>(other);
		g -= static_cast<uint8_t>(other);
		b -= static_cast<uint8_t>(other);
		a -= static_cast<uint8_t>(other);

		return *this;
	}

	template <typename A>
	auto operator*=(A other) -> Colour&


	
	{
		r *= static_cast<uint8_t>(other);
		g *= static_cast<uint8_t>(other);
		b *= static_cast<uint8_t>(other);
		a *= static_cast<uint8_t>(other);

		return *this;
	}

	template <typename A>
	auto operator/=(A other) -> Colour&


	
	{
		r /= static_cast<uint8_t>(other);
		g /= static_cast<uint8_t>(other);
		b /= static_cast<uint8_t>(other);
		a /= static_cast<uint8_t>(other);

		return *this;
	}

	auto operator+(const Colour& other) const -> Colour
	{
		auto buf = *this;

		buf.r += other.r;
		buf.g += other.g;
		buf.b += other.b;
		buf.a += other.a;

		return buf;
	}

	auto operator-(const Colour& other) const -> Colour
	{
		auto buf = *this;

		buf.r -= other.r;
		buf.g -= other.g;
		buf.b -= other.b;
		buf.a -= other.a;

		return buf;
	}

	auto operator+=(const Colour& other) -> Colour&


	
	{
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;

		return (*this);
	}

	auto operator-=(const Colour& other) -> Colour&


	
	{
		r -= other.r;
		g -= other.g;
		b -= other.b;
		a -= other.a;

		return (*this);
	}

	template <typename T>
	Colour hsv_to_rgb(T h, T s, T v) const
	{
		int _r, _g, _b;

		if (s != 0)
		{
			int i;
			int f, p, q, t;

			h == 360 ? h = 0 : h = h / 60;
			i = static_cast<int>(trunc(h));
			f = h - i;

			p = v * (1 - s);
			q = v * (1 - s * f);
			t = v * (1 - s * (1 - f));

			switch (i)
			{
				case 0:
					_r = v;
					_g = t;
					_b = p;
					break;

				case 1:
					_r = q;
					_g = v;
					_b = p;
					break;

				case 2:
					_r = p;
					_g = v;
					_b = t;
					break;

				case 3:
					_r = p;
					_g = q;
					_b = v;
					break;

				case 4:
					_r = t;
					_g = p;
					_b = v;
					break;

				default:
					_r = v;
					_g = p;
					_b = q;
					break;
			}
		}
		else
		{
			_r = v;
			_g = v;
			_b = v;
		}

		return Colour(static_cast<uint8_t>(_r * 255), static_cast<uint8_t>(_g * 255), static_cast<uint8_t>(_b * 255));
	}

	friend std::ostream& operator<<(std::ostream& os, const Colour& v)
	{
		os << v.r << "\t" << v.g << "\t" << v.b << "\t" << v.a << std::endl;

		return os;
	}
};
