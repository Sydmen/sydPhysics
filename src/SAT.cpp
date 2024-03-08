#include <Math/SAT.hpp>
#include <Math/Transform.hpp>

using namespace SydPhysics;

Vector2f SAT::FindMinMaxProjection(PolygonShape& poly, Vector2f axis, Transform& transform)
{
	axis.Normalize();

	vector<Vector2f> verts = poly.verts;

	float projection = Vector2f::DotProduct(verts[0], axis);
	float min = projection;
	float max = projection;

	int n = verts.size();
	for(int i = 1; i < n; i++)
	{
		//iterate over every point to find the largest and smallest values projected on the given axis
		//This will give us essentially a 1D bounding box of the object on the axis
		projection = Vector2f::DotProduct(verts[i], axis);
		max = max > projection ? max : projection;
		min = min < projection ? min : projection;
	}
	
	return Vector2f(min,max);
}