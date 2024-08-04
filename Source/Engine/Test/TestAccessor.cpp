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
		if (true)
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