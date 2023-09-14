#include "vector.h"

using namespace GizmosLib::Math;

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T> &rhs)
{
	return Vector2(x + rhs.x, y + rhs.y);
}

template <typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& rhs)
{
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

template <typename T>
Vector4<T> Vector4<T>::operator+(const Vector4<T>& rhs)
{
	return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}