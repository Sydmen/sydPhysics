#include <Engine/Entity.hpp>
#include <Physics/PhysicsObject.hpp>
#include <Math/Vector2f.hpp>

using namespace SydPhysics;

PhysicsObject::PhysicsObject(float mass, Entity* p_entity):
myEntity(p_entity)
{
	if(mass > 0)
	{
		invMass = 1/mass;
	}
	else
	{
		invMass = 0;
	}
}

void PhysicsObject::SayHello()
{
	std::cout << "Hi :3" << std::endl;
}

Vector2f PhysicsObject::GetForce()
{
	return force;
}

//Angular stuff
Vector2f PhysicsObject::GetVelocityAtPoint(Vector2f& point)
{
	//http://www.chrishecker.com/images/c/c2/Gdmphys2.pdf
	//Figure 3
	Vector2f orgin = myEntity->GetTransform().GetPosition();
	Vector2f rotVelocity = angVel * Vector2f(orgin.y - point.y, point.x - orgin.x);
	return vel + rotVelocity;
}

void PhysicsObject::AddForceAtPoint(Vector2f& point, Vector2f& force)
{
	//http://www.chrishecker.com/images/c/c2/Gdmphys2.pdf
	//Figure 4
	Vector2f origin = myEntity->GetTransform().GetPosition();
	Vector2f perpVector = Vector2f(point.y - origin.y, origin.x - point.x);
	torque += Vector2f::DotProduct(perpVector, force);
}

void PhysicsObject::ClearForces()
{
	force = Vector2f();
}

void PhysicsObject::ApplyLinearImpulse(Vector2f& force)
{
	awake = true;
	vel += force * invMass;
}

void PhysicsObject::AddForce(Vector2f addedForce)
{
	awake = true;
	force += addedForce;
}