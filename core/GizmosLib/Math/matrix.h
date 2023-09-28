#ifndef _MATRIX_
#define _MATRIX_

//3x3 MATRIX
struct Matrix3x3
{
	Matrix3x3();

	Matrix3x3 IdentityMatrix();

	Matrix3x3 ScaleMatrix();
};

struct Matrix4x4
{
	Matrix4x4();

	Matrix4x4 ScaleMatrix();
};

#endif