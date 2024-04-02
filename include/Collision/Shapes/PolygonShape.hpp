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
			vertexCount = verts.size();

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
			
			for(int i = 0; i < vertexCount; i++)
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
			
			//for each edge, create a perp vector for normal vector
			Vector2f edge = verts[0] - verts[vertexCount-1];
			Vector2f perp = Vector2f(edge.y, -edge.x);
			perp.Normalize();
			normals.push_back(perp);

			for(int i = 1; i < vertexCount; i++)
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

		Vector2f GetSupport(const Vector2f& dir)
		{
			float bestProjection = -__FLT_MAX__;
			Vector2f bestVert;

			for(int i = 0; i < vertexCount; i++)
			{
				Vector2f vert = verts[i];
				float projection = Vector2f::DotProduct(vert, dir);

				if(projection > bestProjection)
				{
					bestVert = vert;
					bestProjection = projection;
				}
			}

			return bestVert;
		}

		//list of relative verts without transformation
		vector<Vector2f> rawVerts;

		//list of transformed verts
		vector<Vector2f> verts;

		//normals of verts
		vector<Vector2f> normals;

		int vertexCount;
	};
}

#endif