#include <Collision/NarrowPhase/SphereVsSphereAlgorithm.hpp>

bool SphereVsSphereAlgorithm::TestCollision(SphereShape& A, Transform& transformA, SphereShape& B, Transform& transformB, CollisionInfo& collisionInfo)
{
	float radiusSum = A.GetRadius() + B.GetRadius();
	Vector2f delta = transformB.GetPosition() - transformA.GetPosition();
	float dist = delta.GetLength();

	//Collision
	if(dist < radiusSum)
	{
		//Get info about collision
		float penetration = (radiusSum - dist);
		Vector2f normal = delta.Normalized();
		Vector2f localA = normal * A.GetRadius();
		Vector2f localB = (normal * -1) * B.GetRadius();

		collisionInfo.AddContactPoint(localA, localB, normal, penetration);
		
		//Collision is present
		return true;
	}

	return false;
}