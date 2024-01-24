#ifndef SYDPHYSICS_VECTOR2F_H
#define SYDPHYSICS_VECTOR2F_H

#include <iostream>
#include <cmath>

namespace SydPhysics
{
	struct Vector2f
	{
		Vector2f()
		:x(0.0f), y(0.0f)
		{}

		Vector2f(float p_x, float p_y)
		:x(p_x), y(p_y)
		{}

		//Helpers
		void print();

		//Math
		float GetLength();

		void Normalize();
		Vector2f& Normalized();

		void Negate();

		static float DotProduct(Vector2f const& vector1, Vector2f const& vector2);

		static Vector2f Clamp(Vector2f const& vector, Vector2f const& min, Vector2f const& max);

		bool operator== (Vector2f const& vector) const;

		//Friends
		friend Vector2f operator+(Vector2f const& vector1, Vector2f const& vector2);
		friend Vector2f operator-(Vector2f const& vector1, Vector2f const& vector2);
		friend Vector2f operator*(Vector2f const& vector, float const& number);
		friend Vector2f operator*(float const& number, Vector2f const& vector);
		friend Vector2f operator/(Vector2f const& vector, float const& number);

		//Seperated because we want to keep the same object
		Vector2f& operator+=(Vector2f const& vector);
		Vector2f& operator-=(Vector2f const& vector);

		//https://www.youtube.com/watch?v=htYh-Tq7ZBI
		Vector2f& operator*=(float const& number);
		Vector2f& operator/=(float const& number);

		float x, y;
	};
}

#endif