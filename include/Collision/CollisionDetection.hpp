#ifndef SYDPHYSICS_COLLISIONDETECTION_H
#define SYDPHYSICS_COLLISIONDETECTION_H

#include <Math/Mathematics.hpp>
#include <Physics/PhysicsObject.hpp>

#include <Collision/Shapes/CollisionShape.hpp>
#include <Collision/Shapes/SphereShape.hpp>
#include <Collision/Shapes/AABBShape.hpp>
#include <Collision/Shapes/PolygonShape.hpp>

#include <Collision/NarrowPhase/SphereVsSphereAlgorithm.hpp>
#include <Collision/NarrowPhase/AABBvsAABBAlgorithm.hpp>
#include <Collision/NarrowPhase/AABBvsSphereAlgorithm.hpp>
#include <Collision/NarrowPhase/PolyVsPolyAlgorithm.hpp>

namespace SydPhysics
{
	class CollisionDetection
	{
	public:
		CollisionDetection();

		bool ObjectIntersection(PhysicsObject* A, PhysicsObject* B, CollisionInfo& collisionInfo);

	protected:
		SphereVsSphereAlgorithm mSphereVsSphereAlgorithm;
		AABBvsAABBAlgorithm mAABBvsAABBAlgorithm;
		AABBvsSphereAlgorithm mAABBvsSphereAlgorithm;
	};
}

#endif