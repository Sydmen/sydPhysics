#include <iostream>

#include <Engine/Entity.hpp>
#include <Math/Vector2f.hpp>
#include <Physics/PhysicsWorld.hpp>
#include <Collision/CollisionDetection.hpp>

#include <memory>

using namespace SydPhysics;
using namespace std;
PhysicsWorld::PhysicsWorld(const PhysicsWorldSettings& worldSettings)
{
	mWorldSettings = worldSettings;
}

//This whole function is nasty
//I hate whoever wrote this
//Cause i did
PhysicsObject* PhysicsWorld::CreatePhysicsObject(Entity* entity, float mass, CollisionShape* shape, bool kinematic)
{
	unique_ptr<PhysicsObject> newObject(new PhysicsObject(mass, entity));
	
	newObject->SetKinematic(kinematic);

	if(shape != nullptr){
		newObject->SetCollider(shape);
	}

	//what does this even do lmao
	rigidbodies.emplace_back(move(newObject));
	return rigidbodies.back().get();
}

void PhysicsWorld::Update(float dt)
{
	IntegrateAcceleration(dt);
	IntegrateVelocity(dt);
	CheckCollisions(dt);
}

void PhysicsWorld::IntegrateAcceleration(float dt)
{
	Vector2f gravity = mWorldSettings.gravity;

	for(auto& rb : rigidbodies)
	{
		if(rb->GetInvMass() > 0)
		{
			rb->AddForce(rb->GetMass() * gravity);
		}

		Vector2f force = rb->GetForce() * rb->GetInvMass();

		rb->SetVelocity(rb->GetVelocity() + (force));
		rb->ClearForces();

		//this code is making the objects spin for some reason?

		//assuming it is a box of size (1,1) with a weight of 1kg
		float angAccel = rb->GetTorque()/0.166;
		rb->SetTorque(0);

		if(angAccel == 0) return;
		rb->SetAngularVelocity(rb->GetAngularVelocity() + angAccel*dt);
	}
}

void PhysicsWorld::IntegrateVelocity(float dt)
{
	float dampFactor = mWorldSettings.frameDamping;

	for(auto& rb : rigidbodies)
	{
		if(rb->isAwake())
		{
			//Get velocity for timestep
			Entity* entity = rb->GetEntity();
			Transform& transform = entity->GetTransform();

			if(entity == nullptr)
			{ 		
				std::cout << "Entity not found!." << std::endl;
				continue;
			}

			Vector2f velocity = rb->GetVelocity();	

			//Check if velocity is small enough to be asleep
			if(velocity.GetLength() < mWorldSettings.awakeEpsilon)
			{
				rb->SetVelocity(Vector2f(0,0));
				rb->SetAwake(false);
			}
			else
			{
				//Add velocity to acceleration
				Vector2f currentPos = transform.GetPosition();
				Vector2f newPos = currentPos + (velocity * dt);
				transform.SetPosition(newPos);

				//Frame damping
				velocity *= (1-dampFactor);
				rb->SetVelocity(velocity);				
			}

			transform.SetRotation(transform.GetRotation() + rb->GetAngularVelocity());

			//for some reason, without this check the object spins alot
			//weird stuff
			if(transform.GetRotation() != 0)
			{
				rb->GetCollider()->rotate(transform.GetRotation(), transform.c, transform.s);
			}
			
			//TODO: Adding angular acceleration
			// float rotation = transform.GetRotation();
			// float angVel = rb->GetAngularVelocity();

			// rotation += angVel * dt;

			//transform.SetRotation(rotation);
		}
	}
}

void PhysicsWorld::CheckCollisions(float dt)
{
	//n^2
	//GROSS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	for(auto& obj1 : rigidbodies)
	{ 
		for(auto& obj2 : rigidbodies)
		{ 
			//Check if addresses are the same
			if(&obj1 == &obj2) continue;

			CollisionInfo info;
			if(mCollisionDetection.ObjectIntersection(obj1.get(), obj2.get(), info))
			{
				ResolveCollision(*info.a, *info.b, info.point);
			}
		} 
	}
} 

void PhysicsWorld::ResolveCollision(PhysicsObject& objA, PhysicsObject& objB, ContactPoint& point)
{
	if(point.normal.isNan())
	{
		cout<<"NaN normal"<<endl;
		return;
	}
	
	Transform& transformA = objA.GetTransform();
	Transform& transformB = objB.GetTransform();
	
	//Projection
	float massTotal = objA.GetInvMass() + objB.GetInvMass();

	//Two infinite mass objects
	if(massTotal == 0) return;

	Vector2f projA = transformA.GetPosition() - (point.normal * (point.depth * (objA.GetInvMass() / massTotal)));
	Vector2f projB = transformB.GetPosition() + (point.normal * (point.depth * (objB.GetInvMass() / massTotal)));
	
	transformA.SetPosition(projA);
	transformB.SetPosition(projB);

	//Calculate impusle force
	//Velocities needed to escape
	//I HAVE BEEN USING POINTS THIS WHOLE TIME
	//I WAS SUPPOSED TO USE VELOCITIES!!!!!!!!!

	Vector2f contactVelocity = objB.GetVelocity()-objA.GetVelocity();

	//Get impusle force rel to normal
	float impulseForce = Vector2f::DotProduct(contactVelocity, point.normal);

	//Newton's law of restitution
	float restitution = mWorldSettings.restitutionCoeffectient;

	//Impulse scalar
	float j = (-(1.0f+restitution) * impulseForce) / (massTotal);

	Vector2f fullImpulse = point.normal * j;

	//There is for sure a better way of doing this
	//However, I am struggling to find one, so a simple check should do for now
	// if(objA.GetInvMass() == 0 || objB.GetInvMass() == 0)
	// {
	// 	fullImpulse *= 2;
	// }

	// float penMult = 1 + point.depth;
	// fullImpulse *= penMult;	

	objB.ApplyLinearImpulse(fullImpulse);
	fullImpulse *= -1;
	objA.ApplyLinearImpulse(fullImpulse);
}