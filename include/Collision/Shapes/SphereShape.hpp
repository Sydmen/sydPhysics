#ifndef SYDPHYSICS_SPHERESHAPE_H
#define SYDPHYSICS_SPHERESHAPE_H

#include <Collision/Shapes/CollisionShape.hpp>

namespace SydPhysics
{
	class SphereShape : public CollisionShape
	{
	public:
		SphereShape(float r = 1.0)
		{
			myShape = ShapeType::SPHERE;
			radius = r;
		}
		~SphereShape() {}

		float GetRadius()const{
			return radius;
		}
	protected:
		float radius;
	};
}

#endif