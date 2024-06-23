#pragma once

#include "core/math/math.h"

namespace unicore
{
	class Transform
	{
	public:
		static Matrix4x4f Translation(float x, float y, float z);
		static Matrix4x4f Translation(const Vector4f& position);
		static Matrix4x4f Scale(const Vector4f& scale);

		static Matrix4x4f Rotation(float pitch, float yaw, float roll);
		static Matrix4x4f Rotation(const Quaternion4f& rot);

		static Matrix4x4f RotationPitch(float pitch);
		static Matrix4x4f RotationYaw(float yaw);
		static Matrix4x4f RotationRoll(float roll);

		const Vector4f& GetPosition() const { return m_Position; }
		Vector4f& GetPosition() { return m_Position; }
		void SetPosition(const Vector4f& pos) { m_Position = pos; }

        const Vector4f& GetScale() const { return m_Scale; }
        Vector4f& GetScale() { return m_Scale; }
        void SetScale(const Vector4f& scale) { m_Scale = scale; }

        const Quaternion4f& GetRotation() const { return m_Rotation; }
		Quaternion4f& GetRotation() { return m_Rotation; }
        void SetRotation(const Quaternion4f& rot) { m_Rotation = rot; }

		Matrix4x4f ToMatrix() const { return Scale(m_Scale) * Rotation(m_Rotation) * Translation(m_Position); }
	private:

		Vector4f m_Position;
		Vector4f m_Scale = Vector4f::One();
		Quaternion4f m_Rotation;
	};

	inline Matrix4x4f Transform::Translation(const Vector4f& position)
	{
		return Matrix4x4f(
			Vector4f::Right(),
			Vector4f::Up(),
			Vector4f::Forward(),
			Vector4f(position.GetX(), position.GetY(), position.GetZ(), 1.0f)
		);
	}

    inline Matrix4x4f Transform::Translation(float x, float y, float z)
    {
        return Transform::Translation(Vector4f(x, y, z, 1.0f));
    }

	inline Matrix4x4f Transform::Scale(const Vector4f& scale)
	{
        return Matrix4x4f(
            Vector4f(scale.GetX(), 0.0f, 0.0f, 0.0f),
            Vector4f(0.0f, scale.GetY(), 0.0f, 0.0f),
            Vector4f(0.0f, 0.0f, scale.GetZ(), 0.0f),
			Vector4f::Origin()
        );
	}

	inline Matrix4x4f Transform::Rotation(float pitch, float yaw, float roll)
	{
		return RotationPitch(pitch) * RotationYaw(yaw) * RotationRoll(roll);
	}

	inline Matrix4x4f Transform::Rotation(const Quaternion4f& rot)
	{
		return Matrix4x4f::Identity(); // TODO actually implement quat matrix
	}

	inline Matrix4x4f Transform::RotationPitch(float pitch)
	{
		return Matrix4x4f{
			Vector4f::Right(),
			Vector4f{0.0f, cosf(pitch), sinf(pitch), 0.0f},
			Vector4f{0.0f, -sinf(pitch), cosf(pitch), 0.0f},
			Vector4f::Origin()
		};

	}

	inline Matrix4x4f Transform::RotationYaw(float yaw)
	{
        return Matrix4x4f{
            Vector4f{cosf(yaw), 0.0f, -sinf(yaw), 0.0f},
            Vector4f::Up(),
            Vector4f{sinf(yaw), 0.0f, cosf(yaw), 0.0f},
            Vector4f::Origin()
        };
	}

	inline Matrix4x4f Transform::RotationRoll(float roll)
	{
        return Matrix4x4f{
            Vector4f{cosf(roll), sinf(roll), 0.0f, 0.0f},
            Vector4f{-sinf(roll), cosf(roll), 0.0f, 0.0f},
            Vector4f::Forward(),
            Vector4f::Origin()
        };
	}
}
