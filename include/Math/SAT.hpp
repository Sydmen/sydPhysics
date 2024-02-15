#ifndef SYDPHYSICS_SAT_H
#define SYDPHYSICS_SAT_H

#include <Math/Transform.hpp>
#include <Collision/Shapes/PolygonShape.hpp>

namespace SydPhysics
{
	class SAT
	{
	public:
		static Vector2f FindMinMaxProjection(PolygonShape& poly, Vector2f axis);
	};
}

#endif