#include <Collision/NarrowPhase/PolyVsPolyAlgorithm.hpp>
#include <Math/SAT.hpp>
#include <limits>

float PolyVsPolyAlgorithm::FindAxisLeastPen(int* faceIndex, PolygonShape& A, Transform& transformA, PolygonShape& B, Transform& transformB)
{
	float bestDist = -__FLT_MAX__;
	int bestIndex;

	for(int i = 0; i < A.vertexCount; i++)
	{
		Vector2f normal = A.normals[i];

		//get support point using A's normal
		Vector2f support = B.GetSupport(normal * -1) + transformB.GetPosition();

		Vector2f vector = A.verts[i] + transformA.GetPosition();

		float dist = Vector2f::DotProduct(normal, support - vector);

		if(dist > bestDist)
		{
			bestDist = dist;
			bestIndex = i;
		}
	}
	
	*faceIndex = bestIndex;
	return bestDist;
}

bool PolyVsPolyAlgorithm::TestCollision(PolygonShape& A, Transform& transformA, PolygonShape& B, Transform& transformB, CollisionInfo& collisionInfo)
{	
	for(Vector2f& normal : A.normals)
	{	
		//Project the verts onto a normal
		//Compared like an AABB of sorts
		Vector2f minMax1 = SAT::FindMinMaxProjection(A, normal, transformA);
		Vector2f minMax2 = SAT::FindMinMaxProjection(B, normal, transformB);

		//there exists a line that can pass through the objects
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

	int faceIndexA;
	int faceIndexB;
	float depthA = FindAxisLeastPen(&faceIndexA, A, transformA, B, transformB);
	float depthB = FindAxisLeastPen(&faceIndexB, B, transformB, A, transformA);

	float depth;
	Vector2f normal;

	if(-1*depthA > -1*depthB)
	{
		depth = depthA;
		normal = A.normals[faceIndexA]*-1;
	}
	else
	{
		depth = depthB;
		normal = B.normals[faceIndexB];
		cout<<"HEY"<<endl;
	}
	
	collisionInfo.AddContactPoint(Vector2f(), Vector2f(), normal, depth);
	
	return true;
}