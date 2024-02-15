#ifndef SYDPHYS_POLYSHAPE_H
#define SYDPHYS_POLYSHAPE_H

using namespace std;
#include <vector>

#include <Collision/Shapes/CollisionShape.hpp>
#include <Engine/RenderWindow.hpp>

namespace SydPhysics
{
	class PolygonShape : public CollisionShape
	{
	public:
		PolygonShape(vector<Vector2f> verts)
		{
			shapeType = ShapeType::POLY;

			mVerts = verts;
			mNormals.clear();

			int n = mVerts.size();
			Vector2f edge = mVerts[n - 1] - mVerts[0];
			Vector2f perp = Vector2f(edge.y, -edge.x);
			perp.Normalize();
			mNormals.push_back(perp);

			for(int i = 1; i < n; i++)
			{
				edge = mVerts[i] - mVerts[i-1];
				perp = Vector2f(edge.y, -edge.x);
				perp.Normalize();
				mNormals.push_back(perp);
			}
		}

		~PolygonShape(){}

		//remove this at some point
		void draw(RenderWindow window)
		{
			int n = mVerts.size();
			window.drawLine(mVerts[n-1],mVerts[0]);
			for(int i = 1; i < n; i++)
			{
				window.drawLine(mVerts[i-1], mVerts[i]);
			}
		}

		vector<Vector2f> mVerts;
		vector<Vector2f> mNormals;
	};
}

#endif