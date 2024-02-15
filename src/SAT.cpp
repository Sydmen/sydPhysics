#include <Math/SAT.hpp>
#include <Math/Transform.hpp>

using namespace SydPhysics;

Vector2f SAT::FindMinMaxProjection(PolygonShape& poly, Vector2f axis)
{
	float projection = Vector2f::DotProduct(poly.mVerts[0], axis);
	float min = projection;
	float max = projection;

	int n = poly.mVerts.size();
	for(int i = 1; i < n; i++)
	{
		projection = Vector2f::DotProduct(poly.mVerts[1], axis);
		max = max > projection ? max : projection;
		min = min < projection ? min : projection;
	}

	return Vector2f(min,max);
}