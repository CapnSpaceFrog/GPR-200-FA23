#ifndef MATH_VECTOR
#define MATH_VECTOR

namespace GizmosLib
{
	namespace Math
	{
		template <typename T>
		struct Vector2
		{
		public:
			T x;
			T y;

			Vector2() : x{ 0 }, y{ 0 } {};

			Vector2(T v0, T v1) : x{ v0 }, y{ v1 } {};

			Vector2 operator+(const Vector2& rhs);
		};

		template <typename T>
		struct Vector3
		{
		public:
			T x;
			T y;
			T z;

			Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {};

			Vector3(T v0, T v1, T v2) : x{ v0 }, y{ v1 }, z{ v2 } {};

			Vector3 operator+(const Vector3& rhs);
		};

		template <typename T>
		struct Vector4
		{
		public:
			T x;
			T y;
			T z;
			T w;

			Vector4() : x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 } {};

			Vector4(T v0, T v1, T v2, T v3) : x{ v0 }, y{ v1 }, z{ v2 }, w{ v3 } {};

			Vector4 operator+(const Vector4& rhs);
		};

	}
}

#endif