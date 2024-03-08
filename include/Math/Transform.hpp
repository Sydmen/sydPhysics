#ifndef SYDPHYSICS_TRANSFORM_H
#define SYDPHYSICS_TRANSFORM_H

#include <Math/Vector2f.hpp>

namespace SydPhysics{

	class Transform
	{
	public:
		Transform();
		Transform(Vector2f pos);
		Transform(Vector2f pos, Vector2f scl);
		
		Vector2f GetPosition(){return position;}
		void SetPosition(Vector2f& newPos){position = newPos;}

		float GetRotation(){return rotation;}
		
		void SetRotation(float newRot)
		{
			//cachce sine and cosine values when rotated
			rotation = newRot;
			c = cosf(rotation);
			s = sinf(rotation);
		}
		
		Vector2f GetScale(){return scale;}
		void SetScale(Vector2f& newScale){scale = newScale;}

		float c = 1;
		float s = 0;
	private:
		Vector2f position;
		float rotation = 0;
		Vector2f scale;
	};

}

#endif