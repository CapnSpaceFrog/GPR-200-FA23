#ifndef _MATRIX_
#define _MATRIX_

namespace GizmosLib
{
	namespace Math
	{
		//3x3 MATRIX
		template <typename T>
		struct Matrix3x3
		{
			Matrix3x3();

			Matrix3x3 IdentityMatrix();

			Matrix3x3 ScaleMatrix();
		};

		//4x4 MATRIX
		template <typename T>
		struct Matrix4x4
		{
			Matrix4x4();

			Matrix4x4 ScaleMatrix();
		};
	}
}
#endif