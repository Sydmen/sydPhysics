#include <Collision/NarrowPhase/AABBvsSphereAlgorithm.hpp>

bool AABBvsSphereAlgorithm::TestCollision(AABBShape& A, Transform* transformA, SphereShape& B, Transform* transformB, CollisionInfo& collisionInfo)
{
	Vector2f boxSize = A.GetHalfSize();
	Vector2f delta = (transformB->GetPosition())-(transformA->GetPosition());

	Vector2f nearestPoint = Vector2f::Clamp(delta, (-1*boxSize), boxSize);

	Vector2f localPoint = delta - nearestPoint;

	float dist = localPoint.GetLength();

	if(dist < B.GetRadius())
	{
		Vector2f normal = localPoint.Normalized();
		
		//Stupid edge case
		//If the point enters the box, the delta and nearest point are equal, creating a normal of (0,0)
		//Most likely some smart solution out there
		//Or i just fucked it up who knows anymore
		float depth = (B.GetRadius())-dist;
		
		Vector2f localA = Vector2f();
		Vector2f localB = (-1*normal)*B.GetRadius();
		
		collisionInfo.AddContactPoint(localA, localB, normal, depth);
		return true;
	}


	return false;
}