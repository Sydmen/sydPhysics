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
	ShapeType pairType = (ShapeType)((int)colliderA->shapeType |(int)colliderB->shapeType);

	//Sphere vs Sphere
	if(pairType == ShapeType::SPHERE)
	{
		return mSphereVsSphereAlgorithm.TestCollision((SphereShape&)*colliderA, transformA, (SphereShape&)*colliderB, transformB, collisionInfo);	
	}

	//AABB Vs AABB
	if(pairType == ShapeType::AABB)
	{
		return mAABBvsAABBAlgorithm.TestCollision((AABBShape&)*colliderA, transformA, (AABBShape&)*colliderB, transformB, collisionInfo);
	}

	//Poly on poly
	// if(pairType == ShapeType::POLY)
	// {
	// 	return PolyVsPolyAlgorithm::TestCollision((PolygonShape&)*colliderA, transformA, (PolygonShape&)*colliderB, transformB, collisionInfo);
	// }

	//AABB vs Sphere
	if(colliderA->shapeType == ShapeType::AABB && colliderB->shapeType == ShapeType::SPHERE)
	{
		return mAABBvsSphereAlgorithm.TestCollision((AABBShape&)*colliderA, transformA, (SphereShape&)*colliderB, transformB, collisionInfo);
	}
	
	if(colliderB->shapeType == ShapeType::AABB && colliderA->shapeType == ShapeType::SPHERE)
	{
		//Swap
		collisionInfo.a = B;
		collisionInfo.b = A;
		
		return mAABBvsSphereAlgorithm.TestCollision((AABBShape&)*colliderB, transformB, (SphereShape&)*colliderA, transformA, collisionInfo);
	}



	return false;
}