#pragma once

#include "core/math/math.h"

namespace unicore
{
	class Transform
	{
	public:
		static Matrix4f Translation(const Vector4f& position);
		static Matrix4f Scale(const Vector4f& scale);

		static Matrix4f Rotation(float pitch, float yaw, float roll);

		static Matrix4f RotationPitch(float pitch);
		static Matrix4f RotationYaw(float yaw);
		static Matrix4f RotationRoll(float roll);

	};

	inline Matrix4f Transform::Translation(const Vector4f& position)
	{
		Vector4f pos{ position.GetX(), position.GetY(), position.GetZ(), 1.0f };

		return Matrix4f(
			Vector4f::Right(),
			Vector4f::Up(),
			Vector4f::Forward(),
			pos
		);
	}

	inline Matrix4f Transform::Scale(const Vector4f& scale)
	{
        return Matrix4f(
            scale.GetX() * Vector4f::Right(),
            scale.GetY() * Vector4f::Up(),
            scale.GetZ() * Vector4f::Forward(),
			Vector4f::Origin()
        );
	}

	inline Matrix4f Transform::Rotation(float pitch, float yaw, float roll)
	{
		return RotationPitch(pitch) * RotationYaw(yaw) * RotationRoll(roll);
	}

	inline Matrix4f Transform::RotationPitch(float pitch)
	{
		return Matrix4f{
			Vector4f::Right(),
			Vector4f{0.0f, cosf(pitch), sinf(pitch), 0.0f},
			Vector4f{0.0f, -sinf(pitch), cosf(pitch), 0.0f},
			Vector4f::Origin()
		};

	}

	inline Matrix4f Transform::RotationYaw(float yaw)
	{
        return Matrix4f{
            Vector4f{cosf(yaw), 0.0f, -sinf(yaw), 0.0f},
            Vector4f::Up(),
            Vector4f{sinf(yaw), 0.0f, cosf(yaw), 0.0f},
            Vector4f::Origin()
        };
	}

	inline Matrix4f Transform::RotationRoll(float roll)
	{
        return Matrix4f{
            Vector4f{cosf(roll), sinf(roll), 0.0f, 0.0f},
            Vector4f{-sinf(roll), cosf(roll), 0.0f, 0.0f},
            Vector4f::Forward(),
            Vector4f::Origin()
        };
	}
}
