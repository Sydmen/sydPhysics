#include <Math/Vector2f.hpp>
using namespace SydPhysics;

namespace SydPhysics
{
	void Vector2f::print()
	{
		std::cout << x << ", " << y << std::endl;
	}

	void Vector2f::Negate()
	{
		x = -x;
		y = -x;
	}

	float Vector2f::GetLength()
	{
		return std::sqrt((x*x)+(y*y));
	}

	void Vector2f::Normalize()
	{
		float length = GetLength();
		x /= length;
		y /= length;
	}

	Vector2f& Vector2f::Normalized()
	{
		this->Normalize();
		return *this;
	}

	float Vector2f::DotProduct(Vector2f const& vector1, Vector2f const& vector2)
	{
		return (vector1.x * vector2.x) + (vector1.y * vector2.y);
	}

	Vector2f Vector2f::Clamp(Vector2f const& vector, Vector2f const& min, Vector2f const& max)
	{
		Vector2f res;
		//Check if min is bigger than max
		if(min.x > max.x || min.y > max.y) return res;

		//Clamp X
		if(vector.x < min.x) res.x = min.x;
		else if(vector.x > max.x) res.x = max.x;
		else res.x = vector.x;
		
		//Clamp Y
		if(vector.y < min.y) res.y = min.y;
		else if(vector.y > max.y) res.y = max.y;
		else res.y = vector.y;

		return res;
	}

	bool Vector2f::operator== (Vector2f const& vector) const {
		return(x == vector.x && y == vector.y);
	}

	//Addition
	Vector2f operator+(Vector2f const& vector1, Vector2f const& vector2)
	{
		return Vector2f(vector1.x + vector2.x, vector1.y + vector2.y);
	}

	//Subtraction
	Vector2f operator-(Vector2f const& vector1, Vector2f const& vector2)
	{
		return Vector2f(vector1.x - vector2.x, vector1.y - vector2.y);
	}

	//Multiplication
	Vector2f operator*(Vector2f const& vector, float const& number)
	{
		return Vector2f(vector.x * number, vector.y * number);
	}

	Vector2f operator*(float const& number, Vector2f const& vector)
	{
		return vector * number;
	}

	//Division
	Vector2f operator/(Vector2f const& vector, float const& number)
	{
		return Vector2f(vector.x / number, vector.y / number);
	}

	//Addition with assignment
	Vector2f& Vector2f::operator+=(Vector2f const& vector)
	{
		x += vector.x;
		y += vector.y;
		return *this;
	}

	Vector2f& Vector2f::operator-=(Vector2f const& vector)
	{
		x -= vector.x;
		y -= vector.y;
		return *this;
	}
	
	Vector2f& Vector2f::operator*=(float const& number)
	{
		x *= number;
		y *= number;
		return *this;
	}

	Vector2f& Vector2f::operator/=(float const& number)
	{
		x /= number;
		y /= number;
		return *this;
	}
}