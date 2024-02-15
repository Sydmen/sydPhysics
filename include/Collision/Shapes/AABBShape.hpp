#ifndef SYDPHYSICS_AABBSHAPE_H
#define SYDPHYSICS_AABBSHAPE_H

#include <Collision/Shapes/CollisionShape.hpp>

namespace SydPhysics
{
	class AABBShape : public CollisionShape
	{
	public:
		AABBShape(Vector2f size){
			shapeType = ShapeType::AABB;
			halfSize = size;
		}
		~AABBShape(){}

		Vector2f& GetHalfSize(){
			return halfSize;
		}
	protected:
		Vector2f halfSize;
	};
}

#endif