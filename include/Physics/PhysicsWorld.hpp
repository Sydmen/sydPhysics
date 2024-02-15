#ifndef SYDPHYSICS_PHYSICSWORLD_H
#define SYDPHYSICS_PHYSICSWORLD_H

using namespace std;

#include <Math/Mathematics.hpp>
#include <Physics/PhysicsObject.hpp>
#include <Collision/CollisionDetection.hpp>

#include <vector>
#include <memory>

namespace SydPhysics
{
	class PhysicsWorld
	{
	public:
		struct WorldSettings
		{
			string worldName;
			Vector2f gravity;
			float frameDamping;
			float restitutionCoeffectient;

			WorldSettings()
			{
				worldName = "Unnamed world";
				gravity = Vector2f(0,10);
				frameDamping = 0;
				restitutionCoeffectient = 0.5f;
			}

			~WorldSettings() = default;
		};

		PhysicsWorld(const WorldSettings& worldSettings = WorldSettings());
		~PhysicsWorld(){}
		
		PhysicsObject* CreatePhysicsObject(Entity* entity, float mass, CollisionShape* shape, bool kinematic);
		
		void Update(float dt);
		void IntegrateVelocity(float dt);
		void IntegrateAcceleration(float dt);
		void CheckCollisions(float dt);

		void ResolveCollision(PhysicsObject& objA, PhysicsObject& objB, ContactPoint& info);
	protected:
		WorldSettings mWorldSettings;
		CollisionDetection mCollisionDetection;
		vector<unique_ptr<PhysicsObject>> rigidbodies;
	};
}

#endif