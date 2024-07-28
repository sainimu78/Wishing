#pragma once
#include "Niflect/Serialization/Tree/TreeReadWrite2.h"
#include "Niflect/Base/NiflectAddr.h"

namespace Niflect
{
	using namespace TreeReadWrite2;

	class CField;
	class CNiflectType;

	class CProperty;

	using CSharedProperty = TSharedPtr<CProperty>;

	class CProperty
	{
	public:
		CProperty()
			: m_cachedBase(NULL)
			, m_type(NULL)
			, m_isValueProperty(false)
			, m_parent(NULL)
			//, m_field(NULL)
			, m_enabledPathBasedSerializer(false)
		{
		}

	public:
		void InitMeta(const CString& name, const AddrType& cachedBase, bool enabledPathBasedSerializer, bool isValueProperty)
		{
			m_name = name;
			//m_type = type;
			m_cachedBase = cachedBase;
			m_enabledPathBasedSerializer = enabledPathBasedSerializer;
			//m_parent = parent;
			//m_isValueProperty = isValueProperty;
		}
		void InitParent(CProperty* parent)
		{
			m_parent = parent;
		}
		//void SetField(CField* field)
		//{
		//	m_field = field;
		//}
		//bool IsValueProperty() const
		//{
		//	return m_isValueProperty;
		//}
		const CString& GetName() const
		{
			return m_name;
		}
		CProperty* GetParent() const
		{
			return m_parent;
		}
		//const AddrType& GetBase() const
		//{
		//	return m_base;
		//}

	public:
		void AddChild(const CSharedProperty& prop)
		{
			this->InsertChild(prop, this->GetChildrenCount());
		}
		void InsertChild(const CSharedProperty& prop, uint32 idx)
		{
			m_vecChild.insert(m_vecChild.begin() + idx, prop);
		}
		uint32 GetChildrenCount() const
		{
			return static_cast<uint32>(m_vecChild.size());
		}
		CProperty* GetChild(uint32 idx) const
		{
			return m_vecChild[idx].Get();
		}

	public:
		bool SaveWithCachedBase(CRwNode& rw) const
		{
			return this->SaveToRwNode(m_cachedBase, rw);
		}
		bool LoadWithCachedBase(CRwNode& rw) 
		{
			return this->LoadFromRwNode(m_cachedBase, rw);
		}
		void SaveWithRootBase(const AddrType& rootBase, CRwNode& rw) const
		{
			if (!m_enabledPathBasedSerializer)
			{
				this->SaveWithCachedBase(rw);
			}
			else
			{
				TArrayNif<const CProperty*> vecProp;
				auto par = this;
				while (par != NULL)
				{
					vecProp.insert(vecProp.begin(), par);
					par = par->GetParent();
				}

				uint32 frontIndex = 1;
				auto& prop = vecProp[frontIndex];
				prop->SaveByPropertyPathRecurs(vecProp, frontIndex, rootBase, rw);
			}
		}

	public:
		virtual bool SaveToRwNode(const AddrType& base, CRwNode& rw) const = 0;
		virtual bool LoadFromRwNode(AddrType& base, const CRwNode& rw) const = 0;
		virtual bool SaveByPropertyPathRecurs(const TArrayNif<const CProperty*>& vecProp, uint32& frontIndex, const AddrType& base, CRwNode& rw) const = 0;

	private:
		CString m_name;
		CNiflectType* m_type;
		TArrayNif<CSharedProperty> m_vecChild;
		AddrType m_cachedBase;
		//CField* m_field;
		bool m_isValueProperty;
		CProperty* m_parent;
		bool m_enabledPathBasedSerializer;
	};

	class CDefaultProperty : public CProperty
	{
	public:
		virtual bool SaveToRwNode(const AddrType& base, CRwNode& rw) const
		{
			return false;
		}
		virtual bool LoadFromRwNode(AddrType& base, const CRwNode& rw) const
		{
			return false;
		}
		virtual bool SaveByPropertyPathRecurs(const TArrayNif<const CProperty*>& vecProp, uint32& frontIndex, const AddrType& base, CRwNode& rw) const
		{
			return false;
		}
	};
}