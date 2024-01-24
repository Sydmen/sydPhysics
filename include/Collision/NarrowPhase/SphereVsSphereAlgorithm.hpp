#ifndef SYDPHYSICS_SPHERE_ON_SPHERE_COLLISION_H
#define SYDPHYSICS_SPHERE_ON_SPHERE_COLLISION_H

#include <Collision/NarrowPhase/NarrowPhaseAlgorithm.hpp>
#include <Collision/Shapes/SphereShape.hpp>

namespace SydPhysics
{
	class SphereVsSphereAlgorithm : public NarrowPhaseAlgorithm
	{
	public:
		SphereVsSphereAlgorithm() = default;
		~SphereVsSphereAlgorithm(){};
		
		bool TestCollision(SphereShape& A, Transform* transformA, SphereShape& B, Transform* transformB, CollisionInfo& collisionInfo);
	};
}

#endif