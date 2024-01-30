#ifndef SYDPHYS_OBBSHAPE_H
#define SYDPHYS_OBBSHAPE_H

#include <vector>
using namespace std;

namespace SydPhysics
{
	class PolygonShape : public CollisionShape
	{
	public:
		OBBShape()
		{
			myShape = ShapeType::POLY;
		}

		~OBBShape(){}

	protected:
		Vector2f mHalfSize;
		
		//This is the max value in box2d so im gonna borrow it :)
		//Also, i should probably decide if i wanna run with this naming convention or nah
		Vector2f mVerts[8];
		Vector2f mNormals[8];
	}
}

#endif