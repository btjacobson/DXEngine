#pragma once


class Vector3D
{
public:
	Vector3D() : m_X(0), m_Y(0), m_Z(0)
	{

	}

	Vector3D(float x, float y, float z) : m_X(x), m_Y(y), m_Z(z)
	{

	}

	Vector3D(const Vector3D& vector) : m_X(vector.m_X), m_Y(vector.m_Y), m_Z(vector.m_Z)
	{

	}

	static Vector3D Lerp(const Vector3D& start, const Vector3D& end, float delta)
	{
		Vector3D v;
		v.m_X = start.m_X * (1.0f - delta) + end.m_X * (delta);
		v.m_Y = start.m_Y * (1.0f - delta) + end.m_Y * (delta);
		v.m_Z = start.m_Z * (1.0f - delta) + end.m_Z * (delta);

		return v;
	}

	~Vector3D()
	{

	}

	float m_X;
	float m_Y;
	float m_Z;
};