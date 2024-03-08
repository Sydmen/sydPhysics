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
		PolygonShape(vector<Vector2f> mVerts)
		{
			shapeType = ShapeType::POLY;

			rawVerts = mVerts;
			verts = mVerts;

			calculateNormals();
		}

		~PolygonShape(){}

		void rotate(float rot, float c, float s)
		{
			if(rot == rotation)
			{
				return;
			}

			rotation = rot;

			int n = rawVerts.size();
			
			for(int i = 0; i < n; i++)
			{
				Vector2f rawVert = rawVerts[i];

				verts[i].x = (rawVert.x*c) - (rawVert.y*s);
				verts[i].y = (rawVert.x*s) + (rawVert.y*c);
			}

			calculateNormals();
		}

		void calculateNormals()
		{
			normals.clear();
			int n = rawVerts.size();
			
			//for each edge, create a perp vector for normal vector
			Vector2f edge = verts[n - 1] - verts[0];
			Vector2f perp = Vector2f(edge.y, -edge.x);
			perp.Normalize();
			normals.push_back(perp);

			for(int i = 1; i < n; i++)
			{
				edge = verts[i] - verts[i-1];
				perp = Vector2f(edge.y, -edge.x);
				perp.Normalize();
				normals.push_back(perp);
			}
		}

		void setVert(int index, Vector2f newPos)
		{
			rawVerts[index] = newPos;
		}

		//list of relative verts without transformation
		vector<Vector2f> rawVerts;

		//list of transformed verts
		vector<Vector2f> verts;

		//normals of verts
		vector<Vector2f> normals;
	};
}

#endif