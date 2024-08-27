#include "Engine/Test/TestAccessor2.h"
#include <stdio.h>
#include "Niflect/NiflectAccessor.h"
#include "Niflect/NiflectTable.h"
#include "Engine/BuiltinAccessor.h"

namespace Engine
{
	using namespace Niflect;

	template <typename T>
	class TMyVector
	{
	public:
		//TMyVector()
		//	: m_x(0)
		//	, m_y(0)
		//	, m_z(0)
		//{

		//}
		T m_x;
		T m_y;
		T m_z;
	};

	template <typename T>
	class TMyQuaternion
	{
	public:
		//TMyQuaternion()
		//	: m_x(0)
		//	, m_y(0)
		//	, m_z(0)
		//	, m_w(0)
		//{

		//}
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

	template <typename T>
	static bool operator==(const TMyVector<T>& lhs, const TMyVector<T>& rhs)
	{
		return
			lhs.m_x == rhs.m_x &&
			lhs.m_y == rhs.m_y &&
			lhs.m_z == rhs.m_z
			;
	}
	template <typename T>
	static bool operator==(const TMyQuaternion<T>& lhs, const TMyQuaternion<T>& rhs)
	{
		return
			lhs.m_x == rhs.m_x &&
			lhs.m_y == rhs.m_y &&
			lhs.m_z == rhs.m_z &&
			lhs.m_w == rhs.m_w
			;
	}
	template <typename T>
	static bool operator==(const TMyTransform<T>& lhs, const TMyTransform<T>& rhs)
	{
		return
			lhs.m_translation == rhs.m_translation &&
			lhs.m_rotation == rhs.m_rotation &&
			lhs.m_scale == rhs.m_scale
			;
	}

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

	template <typename T>
	static Niflect::CString MyVectorToString(const TMyVector<T>& v)
	{
		std::basic_stringstream<Niflect::CString::value_type, Niflect::CString::traits_type, Niflect::CString::allocator_type> ss;
		ss << v.m_x << ',' << v.m_y << ',' << v.m_z;
		return ss.str();
	}
	template <typename T>
	static TMyVector<T> StringToMyVector(const Niflect::CString& str)
	{
		std::basic_stringstream<Niflect::CString::value_type, Niflect::CString::traits_type, Niflect::CString::allocator_type> ss(str);
		TMyVector<T> v;
		char d;
		ss >> v.m_x >> d >> v.m_y >> d >> v.m_z;
		return v;
	}
	template <typename T>
	static Niflect::CString MyQuaternionToString(const TMyQuaternion<T>& v)
	{
		std::basic_stringstream<Niflect::CString::value_type, Niflect::CString::traits_type, Niflect::CString::allocator_type> ss;
		ss << v.m_x << ',' << v.m_y << ',' << v.m_z << ',' << v.m_w;
		return ss.str();
	}
	template <typename T>
	static TMyQuaternion<T> StringToMyQuaternion(const Niflect::CString& str)
	{
		std::basic_stringstream<Niflect::CString::value_type, Niflect::CString::traits_type, Niflect::CString::allocator_type> ss(str);
		TMyQuaternion<T> v;
		char d;
		ss >> v.m_x >> d >> v.m_y >> d >> v.m_z >> d >> v.m_w;
		return v;
	}

	template <typename T>
	class TMyTransformAccessor : public Niflect::CAccessor
	{
	public:
		virtual bool SaveToRwNode(const AddrType base, CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto& instance = *static_cast<const TMyTransform<T>*>(offsetBase);
			//序列化方式是任意的, 因此可认为支持自定义编码
			AddRwString(rw, "m_translation", MyVectorToString<T>(instance.m_translation));
			AddRwString(rw, "m_rotation", MyQuaternionToString<T>(instance.m_rotation));
			AddRwString(rw, "m_scale", MyVectorToString<T>(instance.m_scale));
			return true;
		}
		virtual bool LoadFromRwNode(AddrType base, const CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto& instance = *static_cast<TMyTransform<T>*>(offsetBase);
			//序列化方式是任意的, 因此可认为支持自定义编码
			instance.m_translation = StringToMyVector<T>(FindRwString(rw, "m_translation"));
			instance.m_rotation = StringToMyQuaternion<T>(FindRwString(rw, "m_rotation"));
			instance.m_scale = StringToMyVector<T>(FindRwString(rw, "m_scale"));
			return true;
		}
	};

	template <typename TAccessor, typename TType>
	static CSharedAccessor CreateFieldLayoutForfFunctionPointerrrrrrrr()
	{
		auto accessor = Niflect::MakeShared<TAccessor>();
		accessor->InitType(StaticGetType<TType>());
		return accessor;
	}

	template <typename T>
	CSharedAccessor CreateSSSSSSSSSSSS();

	template <>
	CSharedAccessor CreateSSSSSSSSSSSS<Niflect::TArrayNif<float> >()
	{
		auto accessor0 = Niflect::MakeShared<TStlArrayAccessor<Niflect::TArrayNif<float> > >();
		accessor0->InitType(StaticGetType<Niflect::TArrayNif<float> >());
		{
			auto type = StaticGetType<float>();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("reserved_dim0", Niflect::CAddrOffset::None);
			accessor0->InitElementAccessor(accessor1);
		}
		return accessor0;
	}
	template <>
	CSharedAccessor CreateSSSSSSSSSSSS<Niflect::TArrayNif<Niflect::CString> >()
	{
		auto accessor0 = Niflect::MakeShared<TStlArrayAccessor<Niflect::TArrayNif<Niflect::CString> > >();
		accessor0->InitType(StaticGetType<Niflect::TArrayNif<Niflect::CString> >());
		{
			auto type = StaticGetType<Niflect::CString>();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("reserved_dim0", Niflect::CAddrOffset::None);
			accessor0->InitElementAccessor(accessor1);
		}
		return accessor0;
	}
	template <>
	CSharedAccessor CreateSSSSSSSSSSSS<Niflect::TArrayNif<TMyTransform<float> > >()
	{
		auto accessor0 = Niflect::MakeShared<TStlArrayAccessor<Niflect::TArrayNif<TMyTransform<float> > > >();
		accessor0->InitType(StaticGetType<Niflect::TArrayNif<TMyTransform<float> > >());
		{
			auto type = StaticGetType<TMyTransform<float> >();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("reserved_dim0", Niflect::CAddrOffset::None);
			accessor0->InitElementAccessor(accessor1);
		}
		return accessor0;
	}
	template <>
	CSharedAccessor CreateSSSSSSSSSSSS<Niflect::TArrayNif<bool> >()
	{
		auto accessor0 = Niflect::MakeShared<TStlBitsArrayAccessor<Niflect::TArrayNif<bool> > >();
		accessor0->InitType(StaticGetType<Niflect::TArrayNif<bool> >());
		return accessor0;
	}
	template <>
	CSharedAccessor CreateSSSSSSSSSSSS<std::vector<bool> >()
	{
		auto accessor0 = Niflect::MakeShared<TStlBitsArrayAccessor<std::vector<bool> > >();
		accessor0->InitType(StaticGetType<std::vector<bool> >());
		return accessor0;
	}
	template <>
	CSharedAccessor CreateSSSSSSSSSSSS<Niflect::TArrayNif<Niflect::TArrayNif<float> > >()
	{
		auto accessor0 = Niflect::MakeShared<TStlArrayAccessor<Niflect::TArrayNif<Niflect::TArrayNif<float> > > >();
		accessor0->InitType(StaticGetType<Niflect::TArrayNif<Niflect::TArrayNif<float> > >());
		{
			auto type = StaticGetType<Niflect::TArrayNif<float> >();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("reserved_dim0", Niflect::CAddrOffset::None);
			accessor0->InitElementAccessor(accessor1);
		}
		return accessor0;
	}
	template <>
	CSharedAccessor CreateSSSSSSSSSSSS<std::pair<Niflect::CString, float> >()
	{
		auto accessor0 = Niflect::MakeShared<CCompoundAccessor>();
		accessor0->InitType(StaticGetType<std::pair<Niflect::CString, float> >());
		{
			auto type = StaticGetType<Niflect::CString>();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("first", GetMemberVariableOffset(&std::pair<Niflect::CString, float>::first));
			accessor0->AddChild(accessor1);
		}
		{
			auto type = StaticGetType<float>();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("second", GetMemberVariableOffset(&std::pair<Niflect::CString, float>::second));
			accessor0->AddChild(accessor1);
		}
		return accessor0;
	}
	template <>
	CSharedAccessor CreateSSSSSSSSSSSS<Niflect::TMap<Niflect::CString, float> >()
	{
		auto accessor0 = Niflect::MakeShared<TStlMapAccessor<Niflect::TMap<Niflect::CString, float> > >();
		accessor0->InitType(StaticGetType<Niflect::TMap<Niflect::CString, float> >());
		{
			auto type = StaticGetType<std::pair<Niflect::CString, float> >();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("reserved_dim0", Niflect::CAddrOffset::None);
			accessor0->InitElementAccessor(accessor1);
		}
		return accessor0;
	}
	template <>
	CSharedAccessor CreateSSSSSSSSSSSS<float>()
	{
		auto accessor0 = Niflect::MakeShared<CFloatAccessor>();
		accessor0->InitType(StaticGetType<float>());
		return accessor0;
	}
	template <>
	CSharedAccessor CreateSSSSSSSSSSSS<bool>()
	{
		auto accessor0 = Niflect::MakeShared<CBoolAccessor>();
		accessor0->InitType(StaticGetType<bool>());
		return accessor0;
	}
	template <>
	CSharedAccessor CreateSSSSSSSSSSSS<Niflect::CString>()
	{
		auto accessor0 = Niflect::MakeShared<CStringAccessor>();
		accessor0->InitType(StaticGetType<Niflect::CString>());
		return accessor0;
	}
}

namespace TestAccessor2
{
	using namespace Engine;

	class CTestClassMy
	{
	public:
		CTestClassMy()
			: m_float_0(0.0f)
			, m_bool_1(false)
			, m_tm_8{}
		{
			printf("CTestClassMy, constructed\n");
		}
		~CTestClassMy()
		{
			printf("CTestClassMy, destructed\n");
		}

		void TestInit()
		{
			m_float_0 = 1.0f;
			m_bool_1 = true;
			m_array_2.resize(3);
			m_array_2[0] = 2.1f;
			m_array_2[1] = 2.2f;
			m_array_2[2] = 2.3f;
			m_array_array_3.resize(2);
			m_array_array_3[0].resize(3);
			m_array_array_3[0][0] = 3.1f;
			m_array_array_3[0][1] = 3.2f;
			m_array_array_3[0][2] = 3.3f;
			m_array_array_3[1].resize(2);
			m_array_array_3[1][0] = 4.1f;
			m_array_array_3[1][1] = 4.2f;
			m_array_4.resize(3);
			m_array_4[0] = true;
			m_array_4[1] = false;
			m_array_4[2] = true;
			m_array_5.resize(5);
			m_array_5[0] = true;
			m_array_5[1] = false;
			m_array_5[2] = true;
			m_array_5[3] = false;
			m_array_5[4] = true;
			m_map_6["nihao"] = 5.1f;
			m_map_6["bucuo"] = 5.2f;
			m_array_7.push_back("shima");
			m_array_7.push_back("zhende");
			m_array_7.push_back("woxin");
			TestInit_TMyTransform(m_tm_8);
		}

		bool operator==(const CTestClassMy& rhs) const
		{
			//if (inherited::operator==(rhs))
			{
				return
					(m_float_0 == rhs.m_float_0)
					&& (m_bool_1 == rhs.m_bool_1)
					&& (m_array_2 == rhs.m_array_2)
					&& (m_array_array_3 == rhs.m_array_array_3)
					&& (m_array_4 == rhs.m_array_4)
					&& (m_array_5 == rhs.m_array_5)
					&& (m_map_6 == rhs.m_map_6)
					&& (m_array_7 == rhs.m_array_7)
					&& (m_tm_8 == rhs.m_tm_8)
					;
			}
			//return false;
		}

	public:
		float m_float_0;
		bool m_bool_1;
		Niflect::TArrayNif<float> m_array_2;
		Niflect::TArrayNif<Niflect::TArrayNif<float> > m_array_array_3;
		Niflect::TArrayNif<bool> m_array_4;
		std::vector<bool> m_array_5;
		Niflect::TMap<Niflect::CString, float> m_map_6;
		Niflect::TArrayNif<Niflect::CString> m_array_7;
		TMyTransform<float> m_tm_8;
	};

	class CTestClassMy2 : public CTestClassMy
	{
		typedef CTestClassMy inherited;
	public:
		CTestClassMy2()
			: m_derived_bool_0(false)
			, m_derived_float_2(0.0f)
			, m_derived_bool_4(false)
		{

		}

		void TestInit()
		{
			inherited::TestInit();

			m_derived_bool_0 = true;
			m_derived_array_1.resize(4);
			m_derived_array_1[0] = 20.1f;
			m_derived_array_1[1] = 20.2f;
			m_derived_array_1[2] = 20.3f;
			m_derived_array_1[3] = 20.4f;
			m_derived_float_2 = 10.1f;
			m_derived_array_3.resize(3);
			m_derived_array_3[0] = true;
			m_derived_array_3[1] = false;
			m_derived_array_3[2] = true;
			m_derived_bool_4 = false;
			m_derived_array_5.resize(3);
			for (auto idx = 0; idx < m_derived_array_5.size(); ++idx)
			{
				auto& it = m_derived_array_5[idx];
				TestInit_TMyTransform(it);
				it.m_scale.m_y += 1 + idx;
			}
		}

		bool operator==(const CTestClassMy2& rhs) const
		{
			if (inherited::operator==(rhs))
			{
				return
					(m_derived_bool_0 == rhs.m_derived_bool_0) &&
					(m_derived_array_1 == rhs.m_derived_array_1) &&
					(m_derived_float_2 == rhs.m_derived_float_2) &&
					(m_derived_array_3 == rhs.m_derived_array_3) &&
					(m_derived_bool_4 == rhs.m_derived_bool_4) &&
					(m_derived_array_5 == rhs.m_derived_array_5)
					;
			}
			return false;
		}

		bool m_derived_bool_0;
		Niflect::TArrayNif<float> m_derived_array_1;
		float m_derived_float_2;
		Niflect::TArrayNif<bool> m_derived_array_3;
		bool m_derived_bool_4;
		Niflect::TArrayNif<TMyTransform<float> > m_derived_array_5;
	};

	Niflect::CSharedAccessor SSSSSSSSSS_CTestClassMy()
	{
		using namespace Niflect;
		auto accessor0 = Niflect::MakeShared<CCompoundAccessor>();
		accessor0->InitType(StaticGetType<CTestClassMy>());
		{
			auto type = StaticGetType<float>();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("m_float_0", GetMemberVariableOffset(&CTestClassMy::m_float_0));
			accessor0->AddChild(accessor1);
		}
		{
			auto type = StaticGetType<bool>();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("m_bool_1", GetMemberVariableOffset(&CTestClassMy::m_bool_1));
			accessor0->AddChild(accessor1);
		}
		{
			auto type = StaticGetType<Niflect::TArrayNif<float> >();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("m_array_2", GetMemberVariableOffset(&CTestClassMy::m_array_2));
			accessor0->AddChild(accessor1);
		}
		{
			auto type = StaticGetType<Niflect::TArrayNif<Niflect::TArrayNif<float> > >();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("m_array_array_3", GetMemberVariableOffset(&CTestClassMy::m_array_array_3));
			accessor0->AddChild(accessor1);
		}
		{
			auto type = StaticGetType<Niflect::TArrayNif<bool> >();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("m_array_4", GetMemberVariableOffset(&CTestClassMy::m_array_4));
			accessor0->AddChild(accessor1);
		}
		{
			auto type = StaticGetType<std::vector<bool> >();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("m_array_5", GetMemberVariableOffset(&CTestClassMy::m_array_5));
			accessor0->AddChild(accessor1);
		}
		{
			auto type = StaticGetType<Niflect::TMap<Niflect::CString, float> >();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("m_map_6", GetMemberVariableOffset(&CTestClassMy::m_map_6));
			accessor0->AddChild(accessor1);
		}
		{
			auto type = StaticGetType<Niflect::TArrayNif<Niflect::CString> >();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("m_array_7", GetMemberVariableOffset(&CTestClassMy::m_array_7));
			accessor0->AddChild(accessor1);
		}
		{
			auto type = StaticGetType<TMyTransform<float> >();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("m_tm_8", GetMemberVariableOffset(&CTestClassMy::m_tm_8));
			accessor0->AddChild(accessor1);
		}
		return accessor0;
	}
	Niflect::CSharedAccessor SSSSSSSSSS_CTestClassMy2()
	{
		using namespace Niflect;
		auto accessor0 = Niflect::MakeShared<CCompoundAccessor>();
		accessor0->InitType(StaticGetType<CTestClassMy2>());
		{
			auto type = StaticGetType<bool>();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("m_derived_bool_0", GetMemberVariableOffset(&CTestClassMy2::m_derived_bool_0));
			accessor0->AddChild(accessor1);
		}
		{
			auto type = StaticGetType<Niflect::TArrayNif<float> >();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("m_derived_array_1", GetMemberVariableOffset(&CTestClassMy2::m_derived_array_1));
			accessor0->AddChild(accessor1);
		}
		{
			auto type = StaticGetType<float>();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("m_derived_float_2", GetMemberVariableOffset(&CTestClassMy2::m_derived_float_2));
			accessor0->AddChild(accessor1);
		}
		{
			auto type = StaticGetType<Niflect::TArrayNif<bool> >();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("m_derived_array_3", GetMemberVariableOffset(&CTestClassMy2::m_derived_array_3));
			accessor0->AddChild(accessor1);
		}
		{
			auto type = StaticGetType<bool>();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("m_derived_bool_4", GetMemberVariableOffset(&CTestClassMy2::m_derived_bool_4));
			accessor0->AddChild(accessor1);
		}
		{
			auto type = StaticGetType<Niflect::TArrayNif<TMyTransform<float> > >();
			auto accessor1 = type->CreateFieldLayout();
			accessor1->InitMemberMeta("m_derived_array_5", GetMemberVariableOffset(&CTestClassMy2::m_derived_array_5));
			accessor0->AddChild(accessor1);
		}
		return accessor0;
	}

	class CPropertyNode;

	using CSharedPropertyNode = Niflect::TSharedPtr<CPropertyNode>;


	class CPropertyNodeFactory
	{
	public:
		void Register(Niflect::CNiflectType* accessorType, Niflect::CNiflectType* propType)
		{
			auto ret = m_mapAccessorToPropType.insert({ accessorType, propType });
			ASSERT(ret.second);
		}
		Niflect::CNiflectType* FindBinding(Niflect::CNiflectType* accessorType) const
		{
			auto itFound = m_mapAccessorToPropType.find(accessorType);
			if (itFound != m_mapAccessorToPropType.end())
				return itFound->second;
			return NULL;
		}

	private:
		Niflect::TMap<CNiflectType*, CNiflectType*> m_mapAccessorToPropType;
	};

	struct SSSSSSSSContext
	{
		const CPropertyNodeFactory& m_factory;
		const CRwNode* m_rw;
		const CAccessor* m_accessor;
	};

	class CPropertyNode
	{
	public:
		virtual void BuildSelf(const SSSSSSSSContext& ctx)
		{
			m_name = ctx.m_accessor->GetName();
		}

	public:
		void AddNode(const CSharedPropertyNode& node)
		{
			m_vecNode.push_back(node);
		}

	public:
		Niflect::CString m_name;
		Niflect::TArrayNif<CSharedPropertyNode> m_vecNode;
	};

	static CSharedPropertyNode BuildPropertyTreeRecurs(const CPropertyNodeFactory& factory, const CRwNode* rwParent, const Niflect::CAccessor* accessorParent);

	class CPropertyGroup : public CPropertyNode
	{
		typedef CPropertyNode inherited;
	public:
		virtual void BuildSelf(const SSSSSSSSContext& ctx) override
		{
			inherited::BuildSelf(ctx);

			auto cnt = ctx.m_accessor->GetChildrenCount();
			for (uint32 idx = 0; idx < cnt; ++idx)
			{
				auto accessorChild = ctx.m_accessor->GetChild(idx);
				auto rwChild = ctx.m_rw->GetNode(idx);
				if (auto propChild = BuildPropertyTreeRecurs(ctx.m_factory, rwChild, accessorChild))
					this->AddNode(propChild);
			}
		}
	};

	class CPropertyArray : public CPropertyNode
	{
		typedef CPropertyNode inherited;
	public:
		virtual void BuildSelf(const SSSSSSSSContext& ctx) override
		{
			inherited::BuildSelf(ctx);

			auto cnt = ctx.m_rw->GetNodesCount();
			auto elemAccessor = ctx.m_accessor->GetElementAccessor();
			for (uint32 idx = 0; idx < cnt; ++idx)
			{
				auto rwChild = ctx.m_rw->GetNode(idx);
				if (auto propChild = BuildPropertyTreeRecurs(ctx.m_factory, rwChild, elemAccessor))
					this->AddNode(propChild);
			}
		}
	};

	CSharedPropertyNode BuildPropertyTreeRecurs(const CPropertyNodeFactory& factory, const CRwNode* rwParent, const Niflect::CAccessor* accessorParent)
	{
		auto accessorType = accessorParent->GetType();
		CSharedPropertyNode prop;
		if (auto propType = factory.FindBinding(accessorType))
			prop = propType->MakeSharedInstance<CPropertyNode>();
		if (prop == NULL)
		{
			if (rwParent->IsValue())
			{
				//ASSERT(false);
			}
			else if (rwParent->IsArray())
			{
				todo: 定义如TStlArrayAccessor的基类相应cast即可, 也可在CAccessor增加表示容器结构Array或Map等的枚举
				ASSERT(false);
			}
			else
			{
				prop = Niflect::MakeShared<CPropertyGroup>();
			}
		}

		if (prop != NULL)
		{
			SSSSSSSSContext ctxChild{ factory, rwParent, accessorParent };
			prop->BuildSelf(ctxChild);
		}
		return prop;
	}
	static void DebugPrintPropertyNodeRecurs(const CPropertyNode* propParent, uint32 level = 0)
	{
		auto strLevel = NiflectUtil::DebugIndentToString(level);
		printf("%s%s\n", strLevel.c_str(), propParent->m_name.c_str());
		level++;
		for (auto& it : propParent->m_vecNode)
			DebugPrintPropertyNodeRecurs(it.Get(), level);
	}

	class CPropertyItem : public CPropertyNode
	{
	public:
		CSharedRwNode m_rwData;
	};

	class CPropertyFloat : public CPropertyItem
	{
		typedef CPropertyItem inherited;
	public:
		virtual void BuildSelf(const SSSSSSSSContext& ctx) override
		{
			inherited::BuildSelf(ctx);

			ASSERT(ctx.m_rw->IsValue());
			auto value = ctx.m_rw->GetValue()->GetFloat();
			m_rwData = CreateRwNode();
			SetRwTypedValue<float>(m_rwData->ToValue(), value);
		}
	};

	void TestFieldLayout()
	{
		if (false)
		{
			using namespace Engine;
			using namespace Niflect;

			Niflect::CNiflectTable tableHolder;
			{
				auto table = &tableHolder;
				table->RegisterType<CClass, Niflect::TArrayNif<float> >("Niflect::TArrayNif<float>", &CreateSSSSSSSSSSSS<Niflect::TArrayNif<float> >);
				table->RegisterType<CClass, float>("float", &CreateSSSSSSSSSSSS<float>);
			}

			auto type = StaticGetType<Niflect::TArrayNif<float> >();
			auto accessor0 = type->CreateFieldLayout();

			Niflect::TArrayNif<float> srcData;
			srcData.resize(2);
			srcData[0] = 1.2f;
			srcData[1] = 2.3f;
			CRwNode root;
			accessor0->SaveToRwNode(&srcData, &root);
			Niflect::TArrayNif<float> dstData;
			accessor0->LoadFromRwNode(&dstData, &root);
			ASSERT(srcData == dstData);
			for (auto& it : dstData)
				printf("%f\n", it);
			printf("");
		}
		if (true)
		{
			using namespace Engine;
			using namespace Niflect;

			Niflect::CNiflectTable tableHolder;
			{
				auto table = &tableHolder;
				table->RegisterType<CNiflectType, float>("float", &CreateFieldLayoutForfFunctionPointerrrrrrrr<CFloatAccessor, float>);
				table->RegisterType<CNiflectType, bool>("bool", &CreateFieldLayoutForfFunctionPointerrrrrrrr<CBoolAccessor, bool>);
				table->RegisterType<CNiflectType, Niflect::CString>("Niflect::CString", &CreateFieldLayoutForfFunctionPointerrrrrrrr<CStringAccessor, Niflect::CString>);
				table->RegisterType<CClass, TMyTransform<float> >("TMyTransform<float>", &CreateFieldLayoutForfFunctionPointerrrrrrrr<TMyTransformAccessor<float>, TMyTransform<float> >);
			}
			{
				auto table = &tableHolder;
				table->RegisterType<CClass, Niflect::TArrayNif<float> >("Niflect::TArrayNif<float>", &CreateSSSSSSSSSSSS<Niflect::TArrayNif<float> >);
				table->RegisterType<CClass, Niflect::TArrayNif<Niflect::TArrayNif<float> > >("Niflect::TArrayNif<Niflect::TArrayNif<float> >", &CreateSSSSSSSSSSSS<Niflect::TArrayNif<Niflect::TArrayNif<float> > >);
				table->RegisterType<CClass, Niflect::TArrayNif<bool> >("Niflect::TArrayNif<bool>", &CreateSSSSSSSSSSSS<Niflect::TArrayNif<bool> >);
				table->RegisterType<CClass, std::vector<bool> >("std::vector<bool>", &CreateSSSSSSSSSSSS<std::vector<bool> >);
				table->RegisterType<CStruct, std::pair<Niflect::CString, float> >("std::pair<Niflect::CString, float>", &CreateSSSSSSSSSSSS<std::pair<Niflect::CString, float> >);
				table->RegisterType<CClass, Niflect::TMap<Niflect::CString, float> >("Niflect::TMap<Niflect::CString, float>", &CreateSSSSSSSSSSSS<Niflect::TMap<Niflect::CString, float> >);
				table->RegisterType<CClass, Niflect::TArrayNif<Niflect::CString> >("Niflect::TArrayNif<Niflect::CString>", &CreateSSSSSSSSSSSS<Niflect::TArrayNif<Niflect::CString> >);
				table->RegisterType<CClass, Niflect::TArrayNif<TMyTransform<float> > >("Niflect::TArrayNif<TMyTransform<float> >", &CreateSSSSSSSSSSSS<Niflect::TArrayNif<TMyTransform<float> > >);
			}

			{
				auto table = &tableHolder;
				table->RegisterType<CClass, CTestClassMy>("CTestClassMy", &SSSSSSSSSS_CTestClassMy);
				table->RegisterType<CClass, CTestClassMy2>("CTestClassMy2", &SSSSSSSSSS_CTestClassMy2);
			}

			{
				auto type = StaticGetType<CTestClassMy>();
				auto accessor0 = type->CreateFieldLayout();

				CTestClassMy srcData;
				srcData.TestInit();
				CRwNode root;
				accessor0->SaveToRwNode(&srcData, &root);
				CTestClassMy dstData;
				accessor0->LoadFromRwNode(&dstData, &root);
				ASSERT(srcData == dstData);
				printf("");
			}
			{
				auto type0 = StaticGetType<CTestClassMy>();
				auto accessor0 = type0->CreateFieldLayout();
				auto type1 = StaticGetType<CTestClassMy2>();
				auto accessor1 = type1->CreateFieldLayout();

				CTestClassMy2 srcData;
				srcData.TestInit();
				CRwNode root;
				accessor0->SaveToRwNode(&srcData, &root);
				accessor1->SaveToRwNode(&srcData, &root);
				CTestClassMy2 dstData;
				accessor0->LoadFromRwNode(&dstData, &root);
				accessor1->LoadFromRwNode(&dstData, &root);
				ASSERT(srcData == dstData);
				printf("");
			}
			{
				{
					auto table = &tableHolder;
					table->RegisterType<CClass, CPropertyFloat>("CPropertyFloat", NULL);
				}

				{
					CPropertyNodeFactory factory;
					factory.Register(StaticGetType<float>(), StaticGetType<CPropertyFloat>());

					CSharedAccessor accessorSrc;
					CRwNode rwSrc;
					{
						auto type0 = StaticGetType<CTestClassMy>();
						accessorSrc = type0->CreateFieldLayout();
						auto instance = type0->MakeSharedInstance<void*>();
						auto& srcData = *reinterpret_cast<CTestClassMy*>(instance.Get());
						srcData.TestInit();
						accessorSrc->SaveToRwNode(&srcData, &rwSrc);
					}

					auto propDst = BuildPropertyTreeRecurs(factory, &rwSrc, accessorSrc.Get());
					//factory.BuildPropertyTreeRecurs(&rwSrc, accessorSrc.Get(), &propDst);
					DebugPrintPropertyNodeRecurs(propDst.Get());
					printf("");
				}
			}
		}
	}
}