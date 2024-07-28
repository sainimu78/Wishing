#pragma once
#include "Niflect/Test/NiflectGenerated/MyModule/MyTransform.gen.h"

namespace MyTestClassScope
{
	template <typename T>
	class TMyVector
	{
	public:
		T m_x;
		T m_y;
		T m_z;
	};

	template <typename T>
	class TMyQuaternion
	{
	public:
		T m_x;
		T m_y;
		T m_z;
		T m_w;
	};

	template <typename T>
	class TMyTransform
	{
	public:
		TMyVector<T> m_translation;
		TMyQuaternion<T> m_rotation;
		TMyVector<T> m_scale;
	};

	typedef TMyTransform<float> CMyTransformFloat;

	template <typename T>
	static void TestInit_TMyTransform(TMyTransform<T>& srcData)
	{
		srcData.m_translation.m_x = 1.0f;
		srcData.m_translation.m_y = 2.0f;
		srcData.m_translation.m_z = 3.0f;
		srcData.m_rotation.m_x = 4.0f;
		srcData.m_rotation.m_y = 5.0f;
		srcData.m_rotation.m_z = 6.0f;
		srcData.m_rotation.m_w = 7.0f;
		srcData.m_scale.m_x = 8.0f;
		srcData.m_scale.m_y = 9.0f;
		srcData.m_scale.m_z = 10.0f;
	}
}