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

		static Matrix4x4f RotationPitch(float pitch);
		static Matrix4x4f RotationYaw(float yaw);
		static Matrix4x4f RotationRoll(float roll);

	};

	inline Matrix4x4f Transform::Translation(const Vector4f& position)
	{
		return Matrix4x4f(
			Vector4f(1.0f, 0.0f, 0.0f, position.GetX()),
			Vector4f(0.0f, 1.0f, 0.0f, position.GetY()),
			Vector4f(0.0f, 0.0f, 1.0f, position.GetZ()),
			Vector4f::Origin()
		);
	}

    inline Matrix4x4f Transform::Translation(float x, float y, float z)
    {
        return Transform::Translation(Vector4f(x, y, z, 1.0f));
    }

	inline Matrix4x4f Transform::Scale(const Vector4f& scale)
	{
        return Matrix4x4f(
            scale.GetX() * Vector4f::Right(),
            scale.GetY() * Vector4f::Up(),
            scale.GetZ() * Vector4f::Forward(),
			Vector4f::Origin()
        );
	}

	inline Matrix4x4f Transform::Rotation(float pitch, float yaw, float roll)
	{
		return RotationPitch(pitch) * RotationYaw(yaw) * RotationRoll(roll);
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
