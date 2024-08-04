#include "Engine/Test/TestAccessor.h"
#include "Niflect/NiflectAccessor.h"
#include "Niflect/Serialization/JsonFormat.h"

namespace TestAccessor
{
	class CTestClassMy
	{
	public:
		void TestInit()
		{
			m_float_0 = 1.0f;
			m_array_1.resize(2);
			m_array_1[0] = 2.1f;
			m_array_1[1] = 2.2f;
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
		class TArrayAccessor : public Niflect::CAccessor
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
					auto elemBase = &instance[idx];
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
					auto elemBase = &instance[idx];
					elemAccessor->LoadFromRwNode(elemBase, rwItem);
				}
				return true;
			}

		private:
			CAccessor* GetElementAccessor() const
			{
				return this->GetChild(0);
			}
		};
	}

	void TestClasses()
	{
		if (false)//¼òµ¥ BuiltIn Float
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
		if (true)
		{
			using namespace Engine;
			auto accessor0 = Niflect::MakeShared<CCompoundAccessor>();
			{
				auto accessor1 = Niflect::MakeShared<CFloatAccessor>();
				accessor1->InitMemberMeta("m_float_0", Niflect::GetMemberVariableOffset(&CTestClassMy::m_float_0));
				accessor0->AddChild(accessor1);
			}
			{
				auto accessor1 = Niflect::MakeShared<TArrayAccessor<Niflect::TArrayNif<float> > >();
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
			CTestClassMy srcData;
			srcData.TestInit();
			CRwNode root;
			accessor0->SaveToRwNode(&srcData, &root);
			CTestClassMy dstData;
			accessor0->LoadFromRwNode(&dstData, &root);
			ASSERT(srcData == dstData);
			printf("");
		}
	}
}