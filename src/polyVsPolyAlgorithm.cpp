#include <Collision/NarrowPhase/PolyVsPolyAlgorithm.hpp>
#include <Math/SAT.hpp>

bool PolyVsPolyAlgorithm::Collides(PolygonShape& A, PolygonShape& B)
{
	for(auto& normal : A.mNormals)
	{
		Vector2f minMax1 = SAT::FindMinMaxProjection(A, normal);
		Vector2f minMax2 = SAT::FindMinMaxProjection(B, normal);

		//Max 1 is less than min 2 or min 1 is greater than max 2
		if(minMax1.y < minMax2.x || minMax1.x > minMax2.y) return false;
	}	

	for(auto& normal : B.mNormals)
	{
		Vector2f minMax1 = SAT::FindMinMaxProjection(A, normal);
		Vector2f minMax2 = SAT::FindMinMaxProjection(B, normal);
		
		//Max 1 is less than min 2 or min 1 is greater than max 2
		if(minMax1.y < minMax2.x || minMax1.x > minMax2.y) return false;
	}	

	return true;
}