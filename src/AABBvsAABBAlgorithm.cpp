#include <Collision/NarrowPhase/AABBvsAABBAlgorithm.hpp>
#include <limits>

bool AABBvsAABBAlgorithm::TestCollision(AABBShape& A, Transform& transformA, AABBShape& B, Transform& transformB, CollisionInfo& collisionInfo)
{
	Vector2f boxAPos = transformA.GetPosition();
	Vector2f boxBPos = transformB.GetPosition();

	Vector2f boxASize = A.GetHalfSize();
	Vector2f boxBSize = B.GetHalfSize();

	bool intersection = AABBTest(boxAPos, boxBPos, boxASize, boxBSize);

	if(intersection)
	{
		//Top right
		Vector2f maxA = boxAPos + boxASize;
		Vector2f maxB = boxBPos + boxBSize;

		//Bottom left
		Vector2f minA = boxAPos - boxASize;
		Vector2f minB = boxBPos - boxBSize;

		static const Vector2f faces[4]
		{
			Vector2f(-1,0), //If right of B touches A, normal is (-1,0)
			Vector2f(1,0),	//Left of B to A
			Vector2f(0,-1), //Top of B to A
			Vector2f(0,1) //Bottom of B to A
		};
		
		float distances[4] = 
		{
			(maxB.x - minA.x), //Right of B to left of A
			(maxA.x - minB.x), //Right of A to left of B

			(maxB.y - minA.y), //Top of B to bottom of A
			(maxA.y - minB.y) //Top of A to bottom of B
		};

		//Test all sides to see which has deepest depth
		float depth = std::numeric_limits<float>::max();
		Vector2f normal;
		for(int i = 0; i < 4; i++)
		{
			//Smaller depth = closer
			if(distances[i] < depth)
			{
				depth = distances[i];
				normal = faces[i];
			}
		}

		collisionInfo.AddContactPoint(Vector2f(), boxAPos-boxBPos, normal, depth);
		return true;
	}

	return false;
}	

bool AABBvsAABBAlgorithm::AABBTest(Vector2f const& posA, Vector2f const& posB, Vector2f const& sizeA, Vector2f const& sizeB)
{
	Vector2f delta = posB - posA ;
	Vector2f totalSize = sizeA + sizeB ;	

	if (abs(delta.x) < totalSize.x && abs(delta.y) < totalSize.y) 
	{
		return true;
	}
	return false;
}