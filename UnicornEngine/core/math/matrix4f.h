#pragma once
#include "vector4f.h"

namespace uni
{
	class Matrix4f
	{
	public:
		using column_type = Vector4f;
		using value_type = column_type::value_type;
		Matrix4f() :m_Data{} {}
		Matrix4f(const Vector4f& c0, const Vector4f& c1,
			const Vector4f& c2, const Vector4f& c3);

		inline column_type& operator[](size_t idx) { return m_Data[idx]; }
		inline const column_type& operator[](size_t idx) const { return m_Data[idx]; }

		Matrix4f& operator+=(const Matrix4f&);
		Matrix4f& operator*=(float);

		void Transpose();

		Matrix4f GetTranspose() const;

		
	private:
		Vector4f m_Data[4];
	};

	inline Matrix4f::Matrix4f(const Vector4f& c0, const Vector4f& c1,
		const Vector4f& c2, const Vector4f& c3) :m_Data{c0, c1, c2, c3} { }

	inline void Matrix4f::Transpose()
	{
		_MM_TRANSPOSE4_PS(
			m_Data[0].GetData(), m_Data[1].GetData(),
			m_Data[2].GetData(), m_Data[3].GetData()
		);
	}

	inline Matrix4f Matrix4f::GetTranspose() const
	{
		Matrix4f result (*this);
		result.Transpose();

		return result; // NRVO should make this free
	}

	inline Matrix4f& Matrix4f::operator+=(const Matrix4f& rhs)
	{
		m_Data[0] += rhs[0];
		m_Data[1] += rhs[1];
		m_Data[2] += rhs[2];
		m_Data[3] += rhs[3];

		return *this;
	}

	inline Matrix4f& Matrix4f::operator*=(float rhs)
	{
		m_Data[0] *= rhs;
		m_Data[1] *= rhs;
		m_Data[2] *= rhs;
		m_Data[3] *= rhs;
	}

	inline Matrix4f operator*(const Matrix4f& lhs, const Matrix4f& rhs)
	{
		Matrix4f result;
		auto rhsT = rhs.GetTranspose();

		result[0][0] = Vector4f::Dot(lhs[0], rhs[0]);
		result[0][1] = Vector4f::Dot(lhs[1], rhs[0]);
		result[0][2] = Vector4f::Dot(lhs[2], rhs[0]);
		result[0][3] = Vector4f::Dot(lhs[3], rhs[0]);

		result[1][0] = Vector4f::Dot(lhs[0], rhs[1]);
		result[1][1] = Vector4f::Dot(lhs[1], rhs[1]);
		result[1][2] = Vector4f::Dot(lhs[2], rhs[1]);
		result[1][3] = Vector4f::Dot(lhs[3], rhs[1]);

		result[2][0] = Vector4f::Dot(lhs[0], rhs[2]);
		result[2][1] = Vector4f::Dot(lhs[1], rhs[2]);
		result[2][2] = Vector4f::Dot(lhs[2], rhs[2]);
		result[2][3] = Vector4f::Dot(lhs[3], rhs[2]);

		result[3][0] = Vector4f::Dot(lhs[0], rhs[3]);
		result[3][1] = Vector4f::Dot(lhs[1], rhs[3]);
		result[3][2] = Vector4f::Dot(lhs[2], rhs[3]);
		result[3][3] = Vector4f::Dot(lhs[3], rhs[3]);
	}
}