#ifndef _MATRIX_4_X_4_
#define _MATRIX_4_X_4_

#include "Vector4.hpp"

struct Matrix4x4 
{
	float m_Matrix[4][4];

	Matrix4x4()
	{
		Zero();
	}

	void Zero()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m_Matrix[i][j] = 0;
	}

	void Identity()
	{
		Zero();

		for (int i = 0; i < 4; i++)
			m_Matrix[i][i] = 1;
	}

	Vector4 operator*(const Vector4 &other)
	{
		float temp[4] {other.x, other.y, other.z, other.w};
		float result[4] {0, 0, 0, 0};

		for (int i = 0; i < 4; i++) 
			for (int j = 0; j < 4; j++)
				result[i] += m_Matrix[i][j] * temp[j];

		return Vector4(result[0], result[1], result[2], result[3]);
	}
};

#endif