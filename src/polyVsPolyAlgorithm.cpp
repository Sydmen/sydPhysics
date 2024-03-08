#include <Collision/NarrowPhase/PolyVsPolyAlgorithm.hpp>
#include <Math/SAT.hpp>

bool PolyVsPolyAlgorithm::TestCollision(PolygonShape& A, Transform& transformA, PolygonShape& B, Transform& transformB, CollisionInfo& collisionInfo)
{
	for(auto& normal : A.normals)
	{
		//Get the 1D bounding box of A and B along the normals
		Vector2f minMax1 = SAT::FindMinMaxProjection(A, normal, transformA);
		Vector2f minMax2 = SAT::FindMinMaxProjection(B, normal, transformB);
		
		//Just like an AABB check at this point along one dimension
		if(minMax1.y < minMax2.x || minMax1.x > minMax2.y)
		{
			float depth = 0;
			if(minMax1.y < minMax2.x)
			{
				depth = minMax1.y - minMax2.x;
			}
			else
			{
				depth = minMax1.x - minMax2.y;
			}
			
			collisionInfo.AddContactPoint(Vector2f(),Vector2f(),normal,depth);
			return true;
		}
	}	

	for(auto& normal : B.normals)
	{
		Vector2f minMax1 = SAT::FindMinMaxProjection(A, normal, transformA);
		Vector2f minMax2 = SAT::FindMinMaxProjection(B, normal, transformB);
		
		//Max 1 is less than min 2 or min 1 is greater than max 2
		if(minMax1.y < minMax2.x || minMax1.x > minMax2.y)
		{
			float depth = 0;
			if(minMax1.y < minMax2.x)
			{
				depth = minMax1.y - minMax2.x;
			}
			else
			{
				depth = minMax1.x - minMax2.y;
			}
			
			collisionInfo.AddContactPoint(Vector2f(),Vector2f(),normal,depth);
			return true;
		}
	}	

	return false;
}