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

Vector2f Camera::WorldToScreenPosition(Vector2f& worldPos)
{
	Vector2f screenPos = worldPos;
	screenPos -= transform.GetPosition();
	screenPos *= scale;
	return screenPos;
}