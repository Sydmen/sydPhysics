#include <Engine/Camera.hpp>

float& Camera::GetScale()
{
	return scale;
}

void Camera::SetScale(float newScale)
{
	scale = newScale;
}

Vector2f Camera::ScreenToWorldPosition(Vector2f& screenPos)
{
	Vector2f worldPos = screenPos;
	worldPos /= scale;
	worldPos += transform.GetPosition();
	return worldPos;
}