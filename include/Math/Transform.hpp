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
		void SetRotation(float& newRot){rotation = newRot;}

		Vector2f GetScale(){return scale;}
		void SetScale(Vector2f& newScale){scale = newScale;}
	private:
		Vector2f position;
		float rotation = 0;
		Vector2f scale;
	};

}

#endif