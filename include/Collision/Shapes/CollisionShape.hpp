#ifndef SYDPHYSICS_COLLISIONSHAPE_H
#define SYDPHYSICS_COLLISIONSHAPE_H

#include <Math/Mathematics.hpp>

namespace SydPhysics
{
	enum class ShapeType
	{
		NONE = 0,
		AABB = 1,
		POLY = 2,
		SPHERE = 4	
	};

	class CollisionShape
	{
	public:
		CollisionShape(){
			shapeType = ShapeType::NONE;
		}
		~CollisionShape() {}
	
		virtual void rotate(float rot, float c, float s){return;}

		ShapeType shapeType;
	protected:
		float rotation;
	};
}

#endif