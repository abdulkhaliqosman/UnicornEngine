#pragma once

#include <intrin.h>

#include <immintrin.h>

namespace unicore
{
	class Vector4f
	{
	public:
		using value_type = float;
		struct alignas(16) vector_type
		{
			float data[4] = { 0.0f };
		};

		inline Vector4f() : m_Data() { _mm_set_ps1(0.0f); }
		inline constexpr Vector4f(float x, float y, float z, float w) : m_Data(_mm_set_ps(w, z, y, x)) { }

		inline Vector4f(float v[4]) : m_Data(_mm_set_ps(v[0], v[1], v[2], v[3])) { }

		inline explicit Vector4f(vector_type& v) : m_Data(_mm_load_ps(v.data)) { }
		inline explicit Vector4f(__m128 data) : m_Data(data) {}

		float GetX() const;
		float GetY() const;
		float GetZ() const;
		float GetW() const;

        void SetX(float f);
        void SetY(float f);
        void SetZ(float f);
        void SetW(float f);

		inline __m128& GetData() { return m_Data; }
		inline const __m128& GetData() const { return m_Data; }

		const Vector4f& operator+= (const Vector4f&);
		const Vector4f& operator*= (float);

		static float Dot(const Vector4f& lhs, const Vector4f& rhs);
		static Vector4f Cross(const Vector4f& lhs, const Vector4f& rhs);

        static inline constexpr Vector4f Zero() { return Vector4f(0.0f, 0.0f, 0.0f, 0.0f); }
        static inline constexpr Vector4f One() { return Vector4f(1.0f, 1.0f, 1.0f, 1.0f); }
        static inline constexpr Vector4f Origin() { return Vector4f(0.0f, 0.0f, 0.0f, 1.0f); }
        static inline constexpr Vector4f Right() { return Vector4f(1.0f, 0.0f, 0.0f, 0.0f); }
        static inline constexpr Vector4f Left() { return Vector4f(-1.0f, 0.0f, 0.0f, 0.0f); }
        static inline constexpr Vector4f Up() { return Vector4f(0.0f, 1.0f, 0.0f, 0.0f); }
        static inline constexpr Vector4f Down() { return Vector4f(0.0f, -1.0f, 0.0f, 0.0f); }
        static inline constexpr Vector4f Forward() { return Vector4f(0.0f, 0.0f, 1.0f, 0.0f); }
        static inline constexpr Vector4f Back() { return Vector4f(0.0f, 0.0f, -1.0f, 0.0f); }

		

	private:
		__m128 m_Data;
	};

	inline float Vector4f::GetX() const
	{
		vector_type tmp;
		_mm_store_ps(tmp.data, m_Data);
		return tmp.data[0];
	}

	inline float Vector4f::GetY() const
	{
        vector_type tmp;
        _mm_store_ps(tmp.data, m_Data);
        return tmp.data[1];
	}

	inline float Vector4f::GetZ() const
	{
        vector_type tmp;
        _mm_store_ps(tmp.data, m_Data);
        return tmp.data[2];
	}

	inline float Vector4f::GetW() const
	{
        vector_type tmp;
        _mm_store_ps(tmp.data, m_Data);
        return tmp.data[3];
	}

    inline void Vector4f::SetX(float f)
	{
        vector_type tmp;
        _mm_store_ps(tmp.data, m_Data);
		tmp.data[0] = f;
		m_Data = _mm_load_ps(tmp.data);
	}

    inline void Vector4f::SetY(float f)
    {
        vector_type tmp;
        _mm_store_ps(tmp.data, m_Data);
        tmp.data[1] = f;
        m_Data = _mm_load_ps(tmp.data);
    }

    inline void Vector4f::SetZ(float f)
    {
        vector_type tmp;
        _mm_store_ps(tmp.data, m_Data);
        tmp.data[2] = f;
        m_Data = _mm_load_ps(tmp.data);
    }

    inline void Vector4f::SetW(float f)
    {
        vector_type tmp;
        _mm_store_ps(tmp.data, m_Data);
        tmp.data[3] = f;
        m_Data = _mm_load_ps(tmp.data);
    }

	inline const Vector4f& Vector4f::operator+= (const Vector4f& rhs)
	{
		m_Data = _mm_add_ps(m_Data, rhs.GetData());
		return *this;
	}

	inline const Vector4f& Vector4f::operator*= (float f)
	{
		__m128 rhs = _mm_set1_ps(f);
		m_Data = _mm_mul_ps(m_Data, rhs);
		return *this;
	}

	inline Vector4f operator+(const Vector4f& lhs, const Vector4f& rhs)
	{
		return Vector4f(_mm_add_ps(lhs.GetData(), rhs.GetData()));
	}

	inline Vector4f operator-(const Vector4f& lhs, const Vector4f& rhs)
	{
		return Vector4f(_mm_sub_ps(lhs.GetData(), rhs.GetData()));
	}

    inline Vector4f operator-(const Vector4f& rhs)
    {
        return Vector4f::Zero() - rhs;
    }

	inline Vector4f operator*(const Vector4f& lhs, float f)
	{
		__m128 rhs = _mm_set1_ps(f);
		return Vector4f(_mm_mul_ps(lhs.GetData(), rhs));
	}

	inline Vector4f operator*(float f, const Vector4f& rhs)
	{
		__m128 lhs = _mm_set1_ps(f);
		return Vector4f(_mm_mul_ps(lhs, rhs.GetData()));
	}

	inline float Vector4f::Dot(const Vector4f& lhs, const Vector4f& rhs)
	{
		return __builtin_ia32_dpps(lhs.GetData(), rhs.GetData(), static_cast<char>(0xFF))[0];
	}

	inline Vector4f Vector4f::Cross(const Vector4f& lhs, const Vector4f& rhs)
	{
        float a1 = lhs.GetX(); float b1 = rhs.GetX();
        float a2 = lhs.GetY(); float b2 = rhs.GetY();
        float a3 = lhs.GetZ(); float b3 = rhs.GetZ();
        float a4 = lhs.GetW(); float b4 = rhs.GetW();


		return Vector4f { a2 * b3 - a3 * b2, a3 * b1 - a1 * b3, a1 * b2 - a2 * b1, a4 * b4 };
	}
}
