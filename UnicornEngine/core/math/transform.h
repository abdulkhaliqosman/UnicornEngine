#pragma once

#include "matrix4f.h"

namespace uni
{
	class Transform
	{
	public:
		static Matrix4f Translation(const Vector4f& position);
	};

	inline Matrix4f Transform::Translation(const Vector4f& position)
	{
		return Matrix4f()
	}
}