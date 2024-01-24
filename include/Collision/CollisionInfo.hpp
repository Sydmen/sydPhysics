#ifndef SYDPHYSICS_COLLISIONINFO_H
#define SYDPHYSICS_COLLISIONINFO_H

#include <Physics/PhysicsObject.hpp>
#include <Math/Mathematics.hpp>

namespace SydPhysics
{
	struct ContactPoint
	{
		Vector2f localA;
		Vector2f localB;
		Vector2f normal;
		float depth;
	};

	struct CollisionInfo
	{
		PhysicsObject* a;
		PhysicsObject* b;

		ContactPoint point;
		void AddContactPoint(const Vector2f& localA, const Vector2f& localB, const Vector2f& normal, float& depth)
		{
			point.localA = localA;
			point.localB = localB;
			point.normal = normal;
			point.depth = depth;
		}	

		void print()
		{
			std::cout << "Object A: " << a << std::endl;
			std::cout << "Object B: " << b << std::endl;
			std::cout << "Local A (" << point.localA.x << ", " << point.localA.y << ")" << std::endl;
			std::cout << "Local B (" << point.localB.x << ", " << point.localB.y << ")" << std::endl;
			std::cout << "Normal (" << point.normal.x << ", " << point.normal.y << ")" << std::endl;
			std::cout << "Depth: " << point.depth << std::endl;
			std::cout << std::endl;
		}
	};
}

#endif