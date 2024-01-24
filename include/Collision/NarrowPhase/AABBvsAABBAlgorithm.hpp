#ifndef SYPHYS_AABB_ON_AABB_COLLISION_H
#define SYPHYS_AABB_ON_AABB_COLLISION_H

#include <Collision/NarrowPhase/NarrowPhaseAlgorithm.hpp>
#include <Collision/Shapes/AABBShape.hpp>

namespace SydPhysics
{
	class AABBvsAABBAlgorithm : public NarrowPhaseAlgorithm
	{
	public:
		AABBvsAABBAlgorithm() = default;
		~AABBvsAABBAlgorithm(){};
		
		bool TestCollision(AABBShape& A, Transform* transformA, AABBShape& B, Transform* transformB, CollisionInfo& collisionInfo);
		bool AABBTest(Vector2f const& posA, Vector2f const& posB, Vector2f const& sizeA, Vector2f const& sizeB);	
	};
}

#endif