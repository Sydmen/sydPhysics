#ifndef SYDPHYSICS_AABB_VS_SPHERE_COLLISION_H
#define SYDPHYSICS_AABB_VS_SPHERE_COLLISION_H

#include <Collision/NarrowPhase/NarrowPhaseAlgorithm.hpp>
#include <Collision/Shapes/AABBShape.hpp>
#include <Collision/Shapes/SphereShape.hpp>

namespace SydPhysics
{
	class AABBvsSphereAlgorithm : public NarrowPhaseAlgorithm
	{
	public:
		AABBvsSphereAlgorithm() = default;
		~AABBvsSphereAlgorithm(){};
		
		bool TestCollision(AABBShape& A, Transform& transformA, SphereShape& B, Transform& transformB, CollisionInfo& collisionInfo);
	};
}

#endif