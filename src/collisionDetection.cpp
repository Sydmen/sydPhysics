#include <Collision/CollisionDetection.hpp>
#include <limits>

using namespace SydPhysics;
using namespace std;

CollisionDetection::CollisionDetection(){}

bool CollisionDetection::ObjectIntersection(PhysicsObject* A, PhysicsObject* B, CollisionInfo& collisionInfo)
{
	const CollisionShape* colliderA = A->GetCollider();
	const CollisionShape* colliderB = B->GetCollider();

	//No collision present
	if(!colliderA || !colliderB) return false;

	collisionInfo.a = A;
	collisionInfo.b = B;

	Transform& transformA = A->GetTransform();
	Transform& transformB = B->GetTransform();
	
	//Check if a pair exists
	ShapeType pairType = (ShapeType)((int)colliderA->myShape |(int)colliderB->myShape);
	if(pairType == ShapeType::SPHERE)
	{
		return mSphereVsSphereAlgorithm.TestCollision((SphereShape&)*colliderA, transformA, (SphereShape&)*colliderB, transformB, collisionInfo);	
	}

	if(pairType == ShapeType::AABB)
	{
		return mAABBvsAABBAlgorithm.TestCollision((AABBShape&)*colliderA, transformA, (AABBShape&)*colliderB, transformB, collisionInfo);
	}

	if(colliderA->myShape == ShapeType::AABB && colliderB->myShape == ShapeType::SPHERE)
	{
		return mAABBvsSphereAlgorithm.TestCollision((AABBShape&)*colliderA, transformA, (SphereShape&)*colliderB, transformB, collisionInfo);
	}
	
	if(colliderB->myShape == ShapeType::AABB && colliderA->myShape == ShapeType::SPHERE)
	{
		//Swap
		collisionInfo.a = B;
		collisionInfo.b = A;
		
		return mAABBvsSphereAlgorithm.TestCollision((AABBShape&)*colliderB, transformB, (SphereShape&)*colliderA, transformA, collisionInfo);
	}


	return false;
}