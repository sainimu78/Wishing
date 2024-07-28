#pragma once
#include "Niflect/Field/NiflectField.h"
#include "Niflect/Test/MyTransform.h"
#include <sstream>
#include "Niflect/Util/StringUtil.h"
#include "Niflect/Test/NiflectGenerated/MyModule/MyClass.gen.h"

namespace MyTestClassScope
{
	class CMyClassBase0_0_0
	{
	public:
		CMyClassBase0_0_0()
			: m_base_base_float_0(123.321f)
			, m_base_base_float_1(123.321f)
		{
		}
		float GetBaseBaseFloat1() const
		{
			return m_base_base_float_1;
		}
		void SetBaseBaseFloat1(float v)
		{
			m_base_base_float_1 = v;
		}
		float m_base_base_float_0;
		float m_base_base_float_1;
	};
	class CMyClassBase0_0
	{
	public:
		CMyClassBase0_0()
			: m_base_float_0(123.321f)
			, m_base_float_2(123.321f)
		{
		}
		const CMyClassBase0_0_0& GetBaseSub1() const
		{
			return m_base_sub_1;
		}
		void SetBaseSub1(const CMyClassBase0_0_0& sub)
		{
			m_base_sub_1 = sub;
		}
		CMyClassBase0_0_0 GetBaseSub1_Copy() const
		{
			return m_base_sub_1;
		}
		float m_base_float_0;
		CMyClassBase0_0_0 m_base_sub_1;
		float m_base_float_2;
	};
	class CMyClass0_0 : public CMyClassBase0_0_0
	{
	public:
		CMyClass0_0()
			: m_float_0(123.321f)
			, m_float_2(123.321f)
		{
		}
		uint32 GetArrayCount() const
		{
			return static_cast<uint32>(m_array_3.size());
		}
		void SetArrayCount(uint32 count)
		{
			m_array_3.resize(count);
		}
		float GetArrayFloat(uint32 idx) const
		{
			return m_array_3[idx];
		}
		void SetArrayFloat(const float& v, uint32 idx)
		{
			m_array_3[idx] = v;
		}
		const Niflect::TArrayNif<float>& GetArray() const
		{
			return m_array_3;
		}
		Niflect::TArrayNif<float> GetArray_Copy() const
		{
			return m_array_3;
		}
		void SetArray(const Niflect::TArrayNif<float>& a)
		{
			m_array_3 = a;
		}
		float GetFloat2() const
		{
			return m_float_2;
		}
		void SetFloat2(const float& v)
		{
			m_float_2 = v;
		}
		const CMyClassBase0_0& GetSub1() const
		{
			return m_sub_1;
		}
		void SetSub1(const CMyClassBase0_0& sub)
		{
			m_sub_1 = sub;
		}
		CMyClassBase0_0 GetSub1_Copy() const
		{
			return m_sub_1;
		}

		float m_float_0;
		CMyClassBase0_0 m_sub_1;
		float m_float_2;
		Niflect::TArrayNif<float> m_array_3;
		Niflect::TArrayNif<Niflect::TArrayNif<float> > m_array_array_4;
		Niflect::TArrayNif<CMyClassBase0_0> m_array_sub_5;
		TMyTransform<float> m_tm_6;
		Niflect::TMap<float, float> m_map_7;
		Niflect::TMap<Niflect::CString, float> m_map_8;
	};

	class CMyClass0
	{
	public:
		class CMySub0
		{
		};
	public:
		CMyClass0()
			: m_float_0(123.321f)
			, m_float_1(123.321f)
			, m_float_pointer_2(NULL)
		{
		}
		float m_float_0;
		float m_float_1;
		float* m_float_pointer_2;
	};

	class CMyClassBase0
	{
	public:
		CMyClassBase0()
			: m_base_float_1(123.321f)
			, m_base_float_2(123.321f)
			, m_base_float_pointer2D_3(NULL)
		{
		}
		Niflect::CString m_base_str_0;
		bool MyFunc0(float arg0, const CMyClass0& arg1, bool* arg2, CMyClass0* arg3, float** arg4)
		{
			printf("Invoke MyFunc0: %f, %f, %s, %f, %f\n", arg0, arg1.m_float_1, *arg2 ? "true" : "false", arg3->m_float_1, arg4[1][2]);
			if ((arg0 == 1.0f) &&
				(arg1.m_float_1 == 123.321f) &&
				(*arg2 == true) &&
				(arg3->m_float_1 == 2.0f) &&
				(arg4[1][2] == 9.0f)
				)
			{
				return true;
			}
			return false;
		}
		float m_base_float_1;
		float m_base_float_2;
		float** m_base_float_pointer2D_3;
	};

	enum class EMyEnum_OptionStyle
	{
		None,
		Option0,
		Option1,
		Option2,
	};

	enum EMyEnum_MaskStyle
	{
		None,
		Mask0,
		Mask1,
		Mask2,
	};

	class CMyClass1 : public CMyClassBase0
	{
	public:
		CMyClass1()
			: m_float_0(123.321f)
			, m_float_3(123.321f)
			, m_float_5(123.321f)
			, m_float_7(123.321f)
			, m_float_9(123.321f)
			, m_float_11(123.321f)
			, m_float_13(123.321f)
			, m_enum_14(EMyEnum_OptionStyle::None)
			, m_float_15(123.321f)
		{
		}
		float m_float_0;
		CMyClass0 m_obj_1;
		Niflect::TArrayNif<float> m_array_2;
		float m_float_3;
		Niflect::TArrayNif<CMyClass0> m_array_4;
		float m_float_5;
		Niflect::TArrayNif<Niflect::TArrayNif<float> > m_array_6;
		float m_float_7;
		TMyTransform<float> m_tm_8;
		float m_float_9;
		Niflect::CString m_str_10;
		float m_float_11;
		Niflect::TMap<Niflect::CString, float> m_map_12;
		float m_float_13;
		EMyEnum_OptionStyle m_enum_14;
		float m_float_15;
	};

	static void TestInit_CMyClass1(CMyClass1& srcData)
	{
		const char* fmt = "A number in string %f";
		uint32 cnt = 0;
		auto Inc = [](uint32& cnt)
		{
			return static_cast<float>(++cnt);
		};

		srcData.m_base_str_0 = NiflectUtil::FormatString(fmt, Inc(cnt));
		srcData.m_base_float_1 = Inc(cnt);
		srcData.m_base_float_2 = Inc(cnt);
		static float s_data2D0;
		static float* s_data1D0 = &s_data2D0;
		srcData.m_base_float_pointer2D_3 = &s_data1D0;
		**srcData.m_base_float_pointer2D_3 = Inc(cnt);
		srcData.m_float_0 = Inc(cnt);
		srcData.m_obj_1.m_float_0 = Inc(cnt);
		srcData.m_obj_1.m_float_1 = Inc(cnt);
		static float s_data0;
		srcData.m_obj_1.m_float_pointer_2 = &s_data0;
		*srcData.m_obj_1.m_float_pointer_2 = Inc(cnt);
		srcData.m_array_2.push_back(Inc(cnt));
		srcData.m_array_2.push_back(Inc(cnt));
		srcData.m_array_2.push_back(Inc(cnt));
		srcData.m_float_3 = Inc(cnt);
		srcData.m_array_4.resize(3);
		srcData.m_array_4[0].m_float_0 = Inc(cnt);
		srcData.m_array_4[0].m_float_1 = Inc(cnt);
		srcData.m_array_4[1].m_float_0 = Inc(cnt);
		srcData.m_array_4[1].m_float_1 = Inc(cnt);
		srcData.m_array_4[2].m_float_0 = Inc(cnt);
		srcData.m_array_4[2].m_float_1 = Inc(cnt);
		srcData.m_float_5 = Inc(cnt);
		srcData.m_array_6.resize(2);
		srcData.m_array_6[0].push_back(Inc(cnt));
		srcData.m_array_6[0].push_back(Inc(cnt));
		srcData.m_array_6[1].push_back(Inc(cnt));
		srcData.m_array_6[1].push_back(Inc(cnt));
		srcData.m_array_6[1].push_back(Inc(cnt));
		srcData.m_float_7 = Inc(cnt);
		srcData.m_tm_8.m_translation.m_x = Inc(cnt);
		srcData.m_tm_8.m_translation.m_y = Inc(cnt);
		srcData.m_tm_8.m_translation.m_z = Inc(cnt);
		srcData.m_tm_8.m_rotation.m_x = Inc(cnt);
		srcData.m_tm_8.m_rotation.m_y = Inc(cnt);
		srcData.m_tm_8.m_rotation.m_z = Inc(cnt);
		srcData.m_tm_8.m_rotation.m_w = Inc(cnt);
		srcData.m_tm_8.m_scale.m_x = Inc(cnt);
		srcData.m_tm_8.m_scale.m_y = Inc(cnt);
		srcData.m_tm_8.m_scale.m_z = Inc(cnt);
		srcData.m_float_9 = Inc(cnt);
		srcData.m_str_10 = NiflectUtil::FormatString(fmt, Inc(cnt));
		srcData.m_float_11 = Inc(cnt);
		srcData.m_map_12["Bucuo"] = Inc(cnt);
		srcData.m_map_12["Shima"] = Inc(cnt);
		srcData.m_float_13 = Inc(cnt);
		srcData.m_enum_14 = EMyEnum_OptionStyle::Option1;
		srcData.m_float_15 = Inc(cnt);
	}

	//Niflect::CSharedField CreateFieldTree_CMyClass0();
	//Niflect::CSharedField CreateFieldTree_CMyClassBase0();
	//Niflect::CSharedField CreateFieldTree_CMyClass1();
}