#include <Collision/NarrowPhase/PolyVsPolyAlgorithm.hpp>
#include <Math/SAT.hpp>

bool PolyVsPolyAlgorithm::TestCollision(PolygonShape& A, Transform& transformA, PolygonShape& B, Transform& transformB, CollisionInfo& collisionInfo)
{	
	for(Vector2f& normal : A.normals)
	{	
		//Get the 1D bounding box of A and B along the normals
		Vector2f minMax1 = SAT::FindMinMaxProjection(A, normal, transformA);
		Vector2f minMax2 = SAT::FindMinMaxProjection(B, normal, transformB);

		//idk how this works
		if((minMax1.x > minMax2.y) || (minMax1.y < minMax2.x))
		{
			return false;
		}
	}	

	for(Vector2f& normal : B.normals)
	{
		Vector2f minMax1 = SAT::FindMinMaxProjection(A, normal, transformA);
		Vector2f minMax2 = SAT::FindMinMaxProjection(B, normal, transformB);
		
		if((minMax1.x > minMax2.y) || (minMax1.y < minMax2.x))
		{
			return false;
		}
	}	

	return true;
}