#include <Math/Transform.hpp>

using namespace SydPhysics;

Transform::Transform()
:position(Vector2f(0,0)), scale(Vector2f(1,1))
{}

Transform::Transform(Vector2f pos)
:position(pos), scale(Vector2f(1,1))
{}

Transform::Transform(Vector2f pos, Vector2f scl)
:position(pos), scale(scl)
{}