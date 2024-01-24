#ifndef SYDPHYSICS_COLLISIONSHAPE_H
#define SYDPHYSICS_COLLISIONSHAPE_H

namespace SydPhysics
{
	enum class ShapeType
	{
		AABB = 1,
		POLY = 2,
		SPHERE = 4,
		NONE = 256
	};

	class CollisionShape
	{
	public:
		CollisionShape(){
			myShape = ShapeType::NONE;
		}
		~CollisionShape() {}

		ShapeType myShape;
	};
}

#endif