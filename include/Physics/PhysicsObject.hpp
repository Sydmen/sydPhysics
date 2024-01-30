#ifndef SYDPHYSICS_PHYSICSOBJECT_H
#define SYDPHYSICS_PHYSICSOBJECT_H

#include <Engine/Entity.hpp>
#include <Math/Vector2f.hpp>
#include <Collision/Shapes/CollisionShape.hpp>

namespace SydPhysics
{
	class PhysicsObject
	{
	public:
		PhysicsObject(float mass, Entity* p_entity);
		~PhysicsObject(){}

		void SayHello();

		Vector2f GetForce();
		void AddForce(Vector2f force);
		void ClearForces();

		void ApplyLinearImpulse(Vector2f& force);

		//Velocity
		Vector2f GetVelocity()
		{
			return vel;
		}

		void SetVelocity(Vector2f newVel)
		{
			vel = newVel;
		}

		//Angualar velocity
		float GetAngularVelocity() const
		{
			return angVel;
		}

		void SetAngularVelocity(float newVel)
		{
			angVel = newVel;
		}

		Vector2f GetVelocityAtPoint(Vector2f& point);
		void AddForceAtPoint(Vector2f& point, Vector2f& force);

		float GetTorque() const
		{
			return torque;
		}

		void SetTorque(float& newTorque)
		{
			torque = newTorque;
		}

		//Helpers
		Entity* GetEntity() const
		{
			return myEntity;
		}

		Transform& GetTransform() const
		{
			return myEntity->GetTransform();
		}

		float GetMass() const
		{
			return 1/invMass;
		}

		float GetInvMass() const
		{
			return invMass;
		}

		CollisionShape* GetCollider() const
		{
			return myShape;
		}

		void SetCollider(CollisionShape* newShape)
		{
			myShape = newShape;
		}

		//A tad gross dont you think
		//Yes i agree
		//Im glad we agree
		//Thanks me
		//No problem me
		//You think we should grab lunch with me, me?
		//Yes that would be very nice
		//Very well then me
		bool IsKinematic(){return kinematic;}
		void SetKinematic(bool state){kinematic = state;}

		float gravityScale = 1;
	protected:
		float invMass;
		bool kinematic = true;

		Vector2f vel;
		Vector2f force;

		float angVel;
		float torque;

		Entity* myEntity;
		CollisionShape* myShape;
	};
}

#endif