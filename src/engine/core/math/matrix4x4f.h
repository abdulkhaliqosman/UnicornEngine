#pragma once
#include "vector4f.h"

namespace Unicorn
{
	class Matrix4x4f
	{
	public:
		using column_type = Vector4f;
		using value_type = column_type::value_type;
		Matrix4x4f() :m_Data{} {}
		Matrix4x4f(const Vector4f& c0, const Vector4f& c1,
			const Vector4f& c2, const Vector4f& c3);

		Matrix4x4f(float m[4][4]) : m_Data{ m[0], m[1], m[2], m[3] } {}

		inline column_type& operator[](size_t idx) { return m_Data[idx]; }
		inline const column_type& operator[](size_t idx) const { return m_Data[idx]; }

		Matrix4x4f& operator+=(const Matrix4x4f&);
		Matrix4x4f& operator*=(float);

		void Transpose();

		Matrix4x4f GetTranspose() const;

		inline const float(& GetData() const)[16] { return *reinterpret_cast<const float(*)[16]>(this); }
		
		static Matrix4x4f Identity();
		static Matrix4x4f Zero();

	private:
		Vector4f m_Data[4];
	};

	inline Matrix4x4f::Matrix4x4f(const Vector4f& c0, const Vector4f& c1,
		const Vector4f& c2, const Vector4f& c3) :m_Data{c0, c1, c2, c3} { }

	inline void Matrix4x4f::Transpose()
	{
		_MM_TRANSPOSE4_PS(
			m_Data[0].GetData(), m_Data[1].GetData(),
			m_Data[2].GetData(), m_Data[3].GetData()
		);
	}

	inline Matrix4x4f Matrix4x4f::GetTranspose() const
	{
		Matrix4x4f result (*this);
		result.Transpose();

		return result; // NRVO should make this free
	}

	inline Matrix4x4f& Matrix4x4f::operator+=(const Matrix4x4f& rhs)
	{
		m_Data[0] += rhs[0];
		m_Data[1] += rhs[1];
		m_Data[2] += rhs[2];
		m_Data[3] += rhs[3];

		return *this;
	}

	inline Matrix4x4f& Matrix4x4f::operator*=(float rhs)
	{
		m_Data[0] *= rhs;
		m_Data[1] *= rhs;
		m_Data[2] *= rhs;
		m_Data[3] *= rhs;

		return *this;
	}

	inline Matrix4x4f operator*(const Matrix4x4f& lhs, const Matrix4x4f& rhs)
	{
		Matrix4x4f result;
		auto rhsT = rhs.GetTranspose();

		result[0].SetX(Vector4f::Dot(lhs[0], rhsT[0]));
        result[0].SetY(Vector4f::Dot(lhs[0], rhsT[1]));
        result[0].SetZ(Vector4f::Dot(lhs[0], rhsT[2]));
        result[0].SetW(Vector4f::Dot(lhs[0], rhsT[3]));

		result[1].SetX(Vector4f::Dot(lhs[1], rhsT[0]));
        result[1].SetY(Vector4f::Dot(lhs[1], rhsT[1]));
        result[1].SetZ(Vector4f::Dot(lhs[1], rhsT[2]));
        result[1].SetW(Vector4f::Dot(lhs[1], rhsT[3]));
		
		result[2].SetX(Vector4f::Dot(lhs[2], rhsT[0]));
        result[2].SetY(Vector4f::Dot(lhs[2], rhsT[1]));
        result[2].SetZ(Vector4f::Dot(lhs[2], rhsT[2]));
        result[2].SetW(Vector4f::Dot(lhs[2], rhsT[3]));

		result[3].SetX(Vector4f::Dot(lhs[3], rhsT[0]));
        result[3].SetY(Vector4f::Dot(lhs[3], rhsT[1]));
        result[3].SetZ(Vector4f::Dot(lhs[3], rhsT[2]));
        result[3].SetW(Vector4f::Dot(lhs[3], rhsT[3]));

		return result;
	}

	inline Matrix4x4f Matrix4x4f::Identity()
	{ 
		return Matrix4x4f(
            Vector4f::Right(),
            Vector4f::Up(),
            Vector4f::Forward(),
            Vector4f::Origin()
		);
	}

    inline Matrix4x4f Matrix4x4f::Zero()
    {
		return Matrix4x4f(Vector4f::Zero(), Vector4f::Zero(), Vector4f::Zero(), Vector4f::Zero());
    }
}
