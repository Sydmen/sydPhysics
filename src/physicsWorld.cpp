#include <iostream>

#include <Engine/Entity.hpp>
#include <Math/Vector2f.hpp>
#include <Physics/PhysicsWorld.hpp>
#include <Collision/CollisionDetection.hpp>

#include <memory>

using namespace SydPhysics;
using namespace std;
PhysicsWorld::PhysicsWorld(const WorldSettings& worldSettings)
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
		Vector2f force = rb->GetForce() * rb->GetInvMass();

		if(rb->GetInvMass() > 0)
		{
			force += gravity;
		}

		rb->SetVelocity(rb->GetVelocity() + (force * dt));
		rb->ClearForces();

		//(1/12) * m * (h^2 + w^2)
	}
}

void PhysicsWorld::IntegrateVelocity(float dt)
{
	float dampFactor = mWorldSettings.frameDamping;

	for(auto& rb : rigidbodies)
	{
		//Get velocity for timestep
		Vector2f velocity = rb->GetVelocity();	

		Entity* entity = rb->GetEntity();
		Transform& transform = entity->GetTransform();

		if(entity == nullptr)
		{ 
			std::cout << "Entity not found. Skipping." << std::endl;
			continue;
		}

		//Add velocity to acceleration
		Vector2f currentPos = transform.GetPosition();
		Vector2f newPos = currentPos + (velocity * dt);
		transform.SetPosition(newPos);

		//Frame damping
		velocity *= (1-dampFactor);
		rb->SetVelocity(velocity);

		//TODO: Adding angular acceleration
		float rotation = transform.GetRotation();
		float angVel = rb->GetAngularVelocity();

		rotation += angVel * dt;

		//transform.SetRotation(rotation);
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
	Transform& transformA = objA.GetTransform();
	Transform& transformB = objB.GetTransform();

	//Projection
	float massTotal = objA.GetInvMass() + objB.GetInvMass();

	Vector2f projA = transformA.GetPosition() - (point.normal * (point.depth * (objA.GetInvMass() / massTotal)));
	Vector2f projB = transformB.GetPosition() + (point.normal * (point.depth * (objB.GetInvMass() / massTotal)));

	transformA.SetPosition(projA);
	transformB.SetPosition(projB);

	//Calculate impusle force
	//Velocities needed to escape
	//THE LOCAL POINTS ARE ALREADY CALCULATED
	//DO NOT TRY AND DO TRANSFORMATION
	Vector2f contactVelocity = point.localB-point.localA;

	//Get impusle force rel to normal
	float impulseForce = Vector2f::DotProduct(contactVelocity, point.normal);

	//Random resitution value
	//TO DO
	//Create world settings class so I can define this and gravity in a convienent place
	float restitution = mWorldSettings.restitutionCoeffectient;
	
	//Get final impulse
	float j = (-(1.0f+restitution) * impulseForce) / (massTotal);
	Vector2f fullImpulse = point.normal * j;

	if(isnan(fullImpulse.x) || isnan(fullImpulse.y))
	{
		cout<<"Impulse is NaN, ignoring"<<endl;
		fullImpulse = Vector2f();
	}

	objB.ApplyLinearImpulse(fullImpulse);
	fullImpulse *= -1;
	objA.ApplyLinearImpulse(fullImpulse);
}