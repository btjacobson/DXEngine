#pragma once

#include <memory>

#include "Vector3D.h"

class Matrix4x4
{
public:
	Matrix4x4()
	{

	}

	void SetIdentity()
	{
		::memset(m_Mat, 0, sizeof(float) * 16);
		m_Mat[0][0] = 1;
		m_Mat[1][1] = 1;
		m_Mat[2][2] = 1;
		m_Mat[3][3] = 1;
	}

	void SetTranslation(const Vector3D& translation)
	{
		SetIdentity();
		m_Mat[3][0] = translation.m_X;
		m_Mat[3][1] = translation.m_Y;
		m_Mat[3][2] = translation.m_Z;
	}

	void SetScale(const Vector3D& scale)
	{
		SetIdentity();
		m_Mat[0][0] = scale.m_X;
		m_Mat[1][1] = scale.m_Y;
		m_Mat[2][2] = scale.m_Z;
	}

	void operator *=(const Matrix4x4& matrix)
	{
		Matrix4x4 out;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				out.m_Mat[i][j] =
					m_Mat[i][0] * matrix.m_Mat[0][j] + m_Mat[i][1] * matrix.m_Mat[1][j] +
					m_Mat[i][2] * matrix.m_Mat[2][j] + m_Mat[i][3] * matrix.m_Mat[3][j];
			}
		}
		::memcpy(m_Mat, out.m_Mat, sizeof(float) * 16);
	}

	void SetOrthoLH(float width, float height, float nearPlane, float farPlane)
	{
		SetIdentity();
		m_Mat[0][0] = 2.0f / width;
		m_Mat[1][1] = 2.0f / height;
		m_Mat[2][2] = 1.0f / (farPlane - nearPlane);
		m_Mat[3][2] = -(nearPlane / (farPlane - nearPlane));
	}

	~Matrix4x4()
	{

	}

	float m_Mat[4][4] = {};
};