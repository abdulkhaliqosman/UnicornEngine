#pragma once
#include "core/math/vector4f.h"

namespace unicore
{
	class Quaternion4f : Vector4f
	{
	public:
		inline Quaternion4f() : Vector4f(){}
		inline Quaternion4f(float i, float j, float k, float real) : Vector4f(i, j, k, real) {}

		inline float GetI() const { return GetX(); }
		inline float GetJ() const { return GetY(); }
		inline float GetK() const { return GetZ(); }
		inline float GetReal() const{ return GetW(); }

		Quaternion4f GetConjugate() const;
		float GetNorm() const;
		float GetNormSq() const;
		Quaternion4f GetInverse() const;

		Vector4f& GetAsVector() { return *this; }

		static Quaternion4f AxisAngle(const Vector4f& axis, float angleRad);

		static Quaternion4f Product(const Quaternion4f& rhs, float);
		static Quaternion4f Product(const Quaternion4f& lhs, const Quaternion4f& rhs);
	};

    inline Quaternion4f operator*(const Quaternion4f& lhs, const Quaternion4f& rhs)
    {
        return Quaternion4f::Product(lhs, rhs);
    }

    inline Quaternion4f operator*(float lhs, const Quaternion4f& rhs)
    {
        return Quaternion4f::Product(rhs, lhs);
    }

    inline Quaternion4f operator*(const Quaternion4f& lhs, float rhs)
    {
        return Quaternion4f::Product(lhs, rhs);
    }

    inline Quaternion4f operator/(const Quaternion4f& lhs, float rhs)
    {
        return Quaternion4f::Product(lhs, 1 / rhs);
    }

	inline Quaternion4f Quaternion4f::GetConjugate() const
	{
		return Quaternion4f(-GetI(), -GetJ(), -GetK(), GetReal());
	}

	inline float Quaternion4f::GetNormSq() const
	{
		return Product(*this, GetConjugate()).GetReal();
	}

    inline float Quaternion4f::GetNorm() const
    {
        return sqrtf(GetNormSq());
    }

	inline Quaternion4f Quaternion4f::GetInverse() const
	{
		return GetConjugate() / GetNormSq();
	}

	inline Quaternion4f Quaternion4f::AxisAngle(const Vector4f& axis, float angleRad)
	{
		float sinHalf = sinf(angleRad * 0.5f);
		float cosHalf = cosf(angleRad * 0.5f);

		return Quaternion4f{ 
			axis.GetX() * sinHalf, 
			axis.GetY() * sinHalf,
			axis.GetZ() * sinHalf, 
			cosHalf 
		};
	}

	inline Quaternion4f Quaternion4f::Product(const Quaternion4f& lhs, float rhs)
	{
        return Quaternion4f{ lhs.GetX() * rhs, lhs.GetY() * rhs, lhs.GetZ() * rhs, lhs.GetReal() * rhs };
	}

    inline Quaternion4f Quaternion4f::Product(const Quaternion4f& lhs, const Quaternion4f& rhs)
    {
        float sa = lhs.GetReal(); float sb = rhs.GetReal();

        Vector4f a{ lhs.GetI(), lhs.GetJ(), lhs.GetK(), 0 };
        Vector4f b{ rhs.GetI(), rhs.GetJ(), rhs.GetK(), 0 };

        float real = sa * sb - Vector4f::Dot(a, b);
        Vector4f imag = sa * b + sb * a + Vector4f::Cross(a, b);
        return Quaternion4f{ imag.GetX(), imag.GetY(), imag.GetZ(), real };
    }
}
