#include "Engine/Test/TestAccessor.h"
#include "Niflect/NiflectAccessor.h"
#include "Niflect/Serialization/JsonFormat.h"

namespace Engine
{
	using namespace RwTree;

	class CFloatAccessor : public Niflect::CAccessor
	{
	public:
		virtual bool SaveToRwNode(const AddrType base, CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto& instance = *static_cast<const float*>(offsetBase);
			ASSERT(!rw->IsValue());
			auto rwValue = rw->ToValue();
			rwValue->SetFloat(instance);
			return true;
		}
		virtual bool LoadFromRwNode(AddrType base, const CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto& instance = *static_cast<float*>(offsetBase);
			ASSERT(rw->IsValue());
			auto rwValue = rw->GetValue();
			instance = rwValue->GetFloat();
			return true;
		}
	};

	class CUint8Accessor : public Niflect::CAccessor
	{
	public:
		virtual bool SaveToRwNode(const AddrType base, CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto& instance = *static_cast<const uint8*>(offsetBase);
			ASSERT(!rw->IsValue());
			auto rwValue = rw->ToValue();
			rwValue->SetUint8(instance);
			return true;
		}
		virtual bool LoadFromRwNode(AddrType base, const CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto& instance = *static_cast<uint8*>(offsetBase);
			ASSERT(rw->IsValue());
			auto rwValue = rw->GetValue();
			instance = rwValue->GetUint8();
			return true;
		}
	};

	class CBoolAccessor : public Niflect::CAccessor
	{
	public:
		virtual bool SaveToRwNode(const AddrType base, CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto& instance = *static_cast<const bool*>(offsetBase);
			ASSERT(!rw->IsValue());
			auto rwValue = rw->ToValue();
			rwValue->SetBool(instance);
			return true;
		}
		virtual bool LoadFromRwNode(AddrType base, const CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto& instance = *static_cast<bool*>(offsetBase);
			ASSERT(rw->IsValue());
			auto rwValue = rw->GetValue();
			instance = rwValue->GetBool();
			return true;
		}
	};

	class CCompoundAccessor : public Niflect::CAccessor
	{
	public:
		virtual bool SaveToRwNode(const AddrType base, CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto count = this->GetChildrenCount();
			for (uint32 idx = 0; idx < count; ++idx)
			{
				auto childAccessor = this->GetChild(idx);
				ASSERT(!childAccessor->GetName().empty());
				auto rwChild = CreateRwNode();
				if (childAccessor->SaveToRwNode(offsetBase, rwChild.Get()))
					AddExistingRwNode(rw, childAccessor->GetName(), rwChild);
			}
			return true;
		}
		virtual bool LoadFromRwNode(AddrType base, const CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto count = this->GetChildrenCount();
			for (uint32 idx = 0; idx < count; ++idx)
			{
				auto childAccessor = this->GetChild(idx);
				ASSERT(!childAccessor->GetName().empty());
				auto rwChild = FindRwNode(rw, childAccessor->GetName());
				childAccessor->LoadFromRwNode(offsetBase, rwChild);
			}
			return true;
		}
	};

	template <typename TStlArray>
	class TStlArrayAccessor : public Niflect::CAccessor
	{
	public:
		virtual bool SaveToRwNode(const AddrType base, CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto& instance = *static_cast<const TStlArray*>(offsetBase);
			ASSERT(!rw->IsArray());
			auto rwArray = rw->ToArray();
			auto elemAccessor = this->GetElementAccessor();
			for (auto idx = 0; idx < instance.size(); ++idx)
			{
				auto rwItem = CreateRwNode();
				//auto elemBase = &instance[idx];//如std::vector<bool>无法支持, 因此额外定义特化模板 GetElementBaseToX, 也可改用std::vector<uint8>, 或另定义Accessor
				bool stlBoolItemHandler;
				auto elemBase = GetElementBaseToRead(instance[idx], stlBoolItemHandler);
				if (elemAccessor->SaveToRwNode(elemBase, rwItem.Get()))
					rwArray->AddItem(rwItem);
			}
			return true;
		}
		virtual bool LoadFromRwNode(AddrType base, const CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto& instance = *static_cast<TStlArray*>(offsetBase);
			ASSERT(rw->IsArray());
			auto rwArray = rw->GetArray();
			auto elemAccessor = this->GetElementAccessor();
			instance.resize(rwArray->GetItemsCount());
			for (auto idx = 0; idx < instance.size(); ++idx)
			{
				auto rwItem = rwArray->GetItem(idx);
				//auto elemBase = &instance[idx];
				bool stlBoolItemHandler;
				auto elemBase = GetElementBaseToWriteBegin(instance[idx], stlBoolItemHandler);
				if (elemAccessor->LoadFromRwNode(elemBase, rwItem))
					GetElementBaseToWriteEnd(instance[idx], stlBoolItemHandler);
			}
			return true;
		}

	private:
		template <typename TItem>
		static const AddrType GetElementBaseToRead(const TItem& item, bool& stlBoolItemHandler)
		{
			return &item;
		}
		template <>
		static const AddrType GetElementBaseToRead<typename TStlArray::const_reference>(const typename TStlArray::const_reference& item, bool& stlBoolItemHandler)
		{
			stlBoolItemHandler = item;
			return &stlBoolItemHandler;
		}
		template <typename TItem>
		static AddrType GetElementBaseToWriteBegin(TItem& item, bool& stlBoolItemHandler)
		{
			return &item;
		}
		template <>
		static AddrType GetElementBaseToWriteBegin<typename TStlArray::reference>(typename TStlArray::reference& item, bool& stlBoolItemHandler)
		{
			return &stlBoolItemHandler;
		}
		template <typename TItem>
		static void GetElementBaseToWriteEnd(TItem& item, bool& stlBoolItemHandler)
		{
		}
		template <>
		static void GetElementBaseToWriteEnd<typename TStlArray::reference>(typename TStlArray::reference& item, bool& stlBoolItemHandler)
		{
			item = stlBoolItemHandler;
		}

	private:
		CAccessor* GetElementAccessor() const
		{
			return this->GetChild(0);
		}
	};
}

namespace Engine
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

	template <typename T>
	bool operator==(const TMyVector<T>& lhs, const TMyVector<T>& rhs)
	{
		return
			lhs.m_x == rhs.m_x &&
			lhs.m_y == rhs.m_y &&
			lhs.m_z == rhs.m_z
			;
	}
	template <typename T>
	bool operator==(const TMyQuaternion<T>& lhs, const TMyQuaternion<T>& rhs)
	{
		return
			lhs.m_x == rhs.m_x &&
			lhs.m_y == rhs.m_y &&
			lhs.m_z == rhs.m_z &&
			lhs.m_w == rhs.m_w
			;
	}
	template <typename T>
	bool operator==(const TMyTransform<T>& lhs, const TMyTransform<T>& rhs)
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
	Niflect::CString MyVectorToString(const TMyVector<T>& v)
	{
		std::basic_stringstream<Niflect::CString::value_type, Niflect::CString::traits_type, Niflect::CString::allocator_type> ss;
		ss << v.m_x << ',' << v.m_y << ',' << v.m_z;
		return ss.str();
	}
	template <typename T>
	TMyVector<T> StringToMyVector(const Niflect::CString& str)
	{
		std::basic_stringstream<Niflect::CString::value_type, Niflect::CString::traits_type, Niflect::CString::allocator_type> ss(str);
		TMyVector<T> v;
		char d;
		ss >> v.m_x >> d >> v.m_y >> d >> v.m_z;
		return v;
	}

	template <typename T>
	Niflect::CString MyQuaternionToString(const TMyQuaternion<T>& v)
	{
		std::basic_stringstream<Niflect::CString::value_type, Niflect::CString::traits_type, Niflect::CString::allocator_type> ss;
		ss << v.m_x << ',' << v.m_y << ',' << v.m_z << ',' << v.m_w;
		return ss.str();
	}
	template <typename T>
	TMyQuaternion<T> StringToMyQuaternion(const Niflect::CString& str)
	{
		std::basic_stringstream<Niflect::CString::value_type, Niflect::CString::traits_type, Niflect::CString::allocator_type> ss(str);
		TMyQuaternion<T> v;
		char d;
		ss >> v.m_x >> d >> v.m_y >> d >> v.m_z >> d >> v.m_w;
		return v;
	}
}

namespace Engine
{
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
}

namespace TestAccessor
{
	class CTestClassMy
	{
	public:
		CTestClassMy()
			: m_float_0(0.0f)
			, m_float_2(0.0f)
		{

		}

		void TestInit()
		{
			m_float_0 = 1.0f;
			m_array_1.resize(3);
			m_array_1[0] = 2.1f;
			m_array_1[1] = 2.2f;
			m_array_1[2] = 2.3f;
			m_float_2 = 1.1f;
		}

		bool operator==(const CTestClassMy& rhs) const
		{
			return
				(m_float_0 == rhs.m_float_0) &&
				(m_array_1 == rhs.m_array_1) &&
				(m_float_2 == rhs.m_float_2)
				;
		}

		float m_float_0;
		Niflect::TArrayNif<float> m_array_1;
		float m_float_2;
	};

	class CTestClassMy2 : public CTestClassMy
	{
		typedef CTestClassMy inherited;
	public:
		CTestClassMy2()
			: m_derived_bool_0(false)
			, m_derived_float_2(0.0f)
			, m_derived_bool_4(true)
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
					(m_derived_bool_4 == rhs.m_derived_bool_4)
					;
			}
			return false;
		}

		bool m_derived_bool_0;
		Niflect::TArrayNif<float> m_derived_array_1;
		float m_derived_float_2;
		Niflect::TArrayNif<bool> m_derived_array_3;
		bool m_derived_bool_4;
	};

	static Niflect::CSharedAccessor BuildAccessor_CTestClassMy()
	{
		using namespace Engine;

		auto accessor0 = Niflect::MakeShared<CCompoundAccessor>();
		{
			auto accessor1 = Niflect::MakeShared<CFloatAccessor>();
			accessor1->InitMemberMeta("m_float_0", Niflect::GetMemberVariableOffset(&CTestClassMy::m_float_0));
			accessor0->AddChild(accessor1);
		}
		{
			auto accessor1 = Niflect::MakeShared<TStlArrayAccessor<Niflect::TArrayNif<float> > >();
			accessor1->InitMemberMeta("m_array_1", Niflect::GetMemberVariableOffset(&CTestClassMy::m_array_1));
			{
				auto accessor2 = Niflect::MakeShared<CFloatAccessor>();
				accessor2->InitMemberMeta("reserved_dim0", Niflect::CAddrOffset::None);
				accessor1->AddChild(accessor2);
			}
			accessor0->AddChild(accessor1);
		}
		{
			auto accessor1 = Niflect::MakeShared<CFloatAccessor>();
			accessor1->InitMemberMeta("m_float_2", Niflect::GetMemberVariableOffset(&CTestClassMy::m_float_2));
			accessor0->AddChild(accessor1);
		}
		return accessor0;
	}
	static Niflect::CSharedAccessor BuildAccessor_CTestClassMy2()
	{
		using namespace Engine;

		auto accessor0 = Niflect::MakeShared<CCompoundAccessor>();
		{
			auto accessor1 = Niflect::MakeShared<CBoolAccessor>();
			accessor1->InitMemberMeta("m_derived_bool_0", Niflect::GetMemberVariableOffset(&CTestClassMy2::m_derived_bool_0));
			accessor0->AddChild(accessor1);
		}
		{
			auto accessor1 = Niflect::MakeShared<TStlArrayAccessor<Niflect::TArrayNif<float> > >();
			accessor1->InitMemberMeta("m_derived_array_1", Niflect::GetMemberVariableOffset(&CTestClassMy2::m_derived_array_1));
			{
				auto accessor2 = Niflect::MakeShared<CFloatAccessor>();
				accessor2->InitMemberMeta("reserved_dim0", Niflect::CAddrOffset::None);
				accessor1->AddChild(accessor2);
			}
			accessor0->AddChild(accessor1);
		}
		{
			auto accessor1 = Niflect::MakeShared<CFloatAccessor>();
			accessor1->InitMemberMeta("m_derived_float_2", Niflect::GetMemberVariableOffset(&CTestClassMy2::m_derived_float_2));
			accessor0->AddChild(accessor1);
		}
		{
			auto accessor1 = Niflect::MakeShared<TStlArrayAccessor<Niflect::TArrayNif<bool> > >();
			accessor1->InitMemberMeta("m_derived_array_3", Niflect::GetMemberVariableOffset(&CTestClassMy2::m_derived_array_3));
			{
				auto accessor2 = Niflect::MakeShared<CBoolAccessor>();
				accessor2->InitMemberMeta("reserved_dim0", Niflect::CAddrOffset::None);
				accessor1->AddChild(accessor2);
			}
			accessor0->AddChild(accessor1);
		}
		{
			auto accessor1 = Niflect::MakeShared<CBoolAccessor>();
			accessor1->InitMemberMeta("m_derived_bool_4", Niflect::GetMemberVariableOffset(&CTestClassMy2::m_derived_bool_4));
			accessor0->AddChild(accessor1);
		}
		return accessor0;
	}

	void TestClasses()
	{
		if (false)//简单 BuiltIn Float
		{
			using namespace Engine;
			auto accessor0 = Niflect::MakeShared<CFloatAccessor>();
			float srcData = 1.23f;
			CRwNode root;
			accessor0->SaveToRwNode(&srcData, &root);
			float dstData = 0.0f;
			accessor0->LoadFromRwNode(&dstData, &root);
			printf("%f\n", dstData);
		}
		if (false)//简单数组
		{
			using namespace Engine;
			auto accessor0 = Niflect::MakeShared<TStlArrayAccessor<Niflect::TArrayNif<float> > >();
			{
				auto accessor1 = Niflect::MakeShared<CFloatAccessor>();
				accessor1->InitMemberMeta("reserved_dim0", Niflect::CAddrOffset::None);
				accessor0->AddChild(accessor1);
			}
			Niflect::TArrayNif<float> srcData;
			srcData.resize(2);
			srcData[0] = 1.2f;
			srcData[1] = 2.3f;
			CRwNode root;
			accessor0->SaveToRwNode(&srcData, &root);
			Niflect::TArrayNif<float> dstData;
			accessor0->LoadFromRwNode(&dstData, &root);
			for (auto& it : dstData)
				printf("%f\n", it);
			printf("");
		}
		if (true)
		{
			using namespace Engine;
			auto accessor0 = Niflect::MakeShared<TMyTransformAccessor<float> >();
			TMyTransform<float> srcData;
			TestInit_TMyTransform(srcData);
			CRwNode root;
			accessor0->SaveToRwNode(&srcData, &root);
			TMyTransform<float> dstData;
			accessor0->LoadFromRwNode(&dstData, &root);
			ASSERT(srcData == dstData);
			printf("");
		}
		if (false)//STL中, 被特殊处理 bool 数组
		{
			using namespace Engine;
			auto accessor0 = Niflect::MakeShared<TStlArrayAccessor<Niflect::TArrayNif<bool> > >();
			{
				auto accessor1 = Niflect::MakeShared<CBoolAccessor>();
				accessor1->InitMemberMeta("reserved_dim0", Niflect::CAddrOffset::None);
				accessor0->AddChild(accessor1);
			}
			Niflect::TArrayNif<bool> srcData;
			srcData.resize(2);
			srcData[0] = false;
			srcData[1] = true;
			CRwNode root;
			accessor0->SaveToRwNode(&srcData, &root);
			Niflect::TArrayNif<bool> dstData;
			accessor0->LoadFromRwNode(&dstData, &root);
			for (auto& it : dstData)
				printf("%s\n", it ? "true" : "false");
			printf("");
		}
		if (false)
		{
			using namespace Engine;
			auto accessor0 = BuildAccessor_CTestClassMy();
			CTestClassMy srcData;
			srcData.TestInit();
			CRwNode root;
			accessor0->SaveToRwNode(&srcData, &root);
			CTestClassMy dstData;
			accessor0->LoadFromRwNode(&dstData, &root);
			ASSERT(srcData == dstData);
			printf("");
		}
		if (false)
		{
			using namespace Engine;
			auto accessor0 = BuildAccessor_CTestClassMy();
			auto accessor1 = BuildAccessor_CTestClassMy2();
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
	}
}