#pragma once

#include <intrin.h>
#include <mmintrin.h>

namespace uni
{
	class Vector4f
	{
	public:
		using value_type = float;

		inline Vector4f() : m_Data() { _mm_set_ps1(0.0f); }
		inline Vector4f(float x, float y, float z, float w) : m_Data(_mm_set_ps(w, z, y, x)) { }
		inline explicit Vector4f(__m128 data) : m_Data(data) {}

		const value_type& operator[](size_t idx) const;
		value_type& operator[](size_t idx);

		inline __m128& GetData() { return m_Data; }
		inline const __m128& GetData() const { return m_Data; }

		const Vector4f& operator+= (const Vector4f&);
		const Vector4f& operator*= (float);

		static float Dot(const Vector4f& lhs, const Vector4f& rhs);

		static inline Vector4f Zero()    { return Vector4f( 0.0f,  0.0f,  0.0f, 0.0f); }
		static inline Vector4f Origin()  { return Vector4f( 0.0f,  0.0f,  0.0f, 1.0f); }
		static inline Vector4f Right()   { return Vector4f( 1.0f,  0.0f,  0.0f, 0.0f); }
		static inline Vector4f Left()    { return Vector4f(-1.0f,  0.0f,  0.0f, 0.0f); }
		static inline Vector4f Up()      { return Vector4f( 0.0f,  1.0f,  0.0f, 0.0f); }
		static inline Vector4f Down()    { return Vector4f( 0.0f, -1.0f,  0.0f, 0.0f); }
		static inline Vector4f Forward() { return Vector4f( 0.0f,  0.0f,  1.0f, 0.0f); }
		static inline Vector4f Back()    { return Vector4f( 0.0f,  0.0f, -1.0f, 0.0f); }

	private:
		__m128 m_Data;
	};

	inline const float& Vector4f::operator[](size_t idx) const
	{
		return m_Data.m128_f32[idx];
	}

	inline float& Vector4f::operator[](size_t idx)
	{
		return m_Data.m128_f32[idx];
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
		return _mm_dp_ps(lhs.GetData(), rhs.GetData(), 0xFF).m128_f32[0];
	}
}