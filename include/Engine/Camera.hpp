#ifndef SYDPHYSICS_CAMERA_H
#define SYDPHYSICS_CAMERA_H

#include <Engine/Entity.hpp>

namespace SydPhysics
{
	class Camera : public Entity
	{
	private:
		float scale = 1;
	public:
		Camera(Vector2f p_pos, Vector2f p_scale) : Entity(p_pos, p_scale){}
		~Camera(){};

		float& GetScale();
		void SetScale(float newScale);
		
		Vector2f ScreenToWorldPosition(Vector2f& screenPos);
		Vector2f WorldToScreenPosition(Vector2f& worldPos);
	};

}

#endif