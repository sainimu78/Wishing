#pragma once
#include "Niflect/Test/MyTransform.h"
#include <sstream>
#include "Niflect/Property/FieldProperty.h"

namespace MyTestClassScope
{
	using namespace TreeReadWrite2;

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
	
	template <typename T>
	class TMyTransformTranslationProperty : public Niflect::CProperty
	{
	public:
		virtual bool SaveToRwNode(const Niflect::AddrType& base, CRwNode& rw) const override
		{
			auto& instance = *static_cast<TMyTransform<T>*>(base);
			auto& rwValue = rw->ToValue();
			rwValue->SetString(MyVectorToString<T>(instance.m_translation));
			return true;
		}
		virtual bool LoadFromRwNode(Niflect::AddrType& base, const CRwNode& rw) const override
		{
			auto& instance = *static_cast<TMyTransform<T>*>(base);
			auto& rwValue = rw->ToValue();
			instance.m_translation = StringToMyVector<T>(rwValue->GetString());
			return true;
		}
		virtual bool SaveByPropertyPathRecurs(const Niflect::TArrayNif<const Niflect::CProperty*>& vecProp, uint32& frontIndex, const Niflect::AddrType& base, CRwNode& rw) const override
		{
			ASSERT(frontIndex == vecProp.size() - 1);
			ASSERT(vecProp[frontIndex] == this);
			return this->SaveToRwNode(base, rw);
		}
	};

	template <typename T>
	class TMyTransformRotationProperty : public Niflect::CProperty
	{
	public:
		virtual bool SaveToRwNode(const Niflect::AddrType& base, CRwNode& rw) const override
		{
			auto& instance = *static_cast<TMyTransform<T>*>(base);
			auto& rwValue = rw->ToValue();
			rwValue->SetString(MyQuaternionToString<T>(instance.m_rotation));
			return true;
		}
		virtual bool LoadFromRwNode(Niflect::AddrType& base, const CRwNode& rw) const override
		{
			auto& instance = *static_cast<TMyTransform<T>*>(base);
			auto& rwValue = rw->ToValue();
			instance.m_rotation = StringToMyQuaternion<T>(rwValue->GetString());
			return true;
		}
		virtual bool SaveByPropertyPathRecurs(const Niflect::TArrayNif<const Niflect::CProperty*>& vecProp, uint32& frontIndex, const Niflect::AddrType& base, CRwNode& rw) const override
		{
			ASSERT(frontIndex == vecProp.size() - 1);
			ASSERT(vecProp[frontIndex] == this);
			return this->SaveToRwNode(base, rw);
		}
	};

	template <typename T>
	class TMyTransformScaleProperty : public Niflect::CProperty
	{
	public:
		virtual bool SaveToRwNode(const Niflect::AddrType& base, CRwNode& rw) const override
		{
			auto& instance = *static_cast<TMyTransform<T>*>(base);
			auto& rwValue = rw->ToValue();
			rwValue->SetString(MyVectorToString<T>(instance.m_scale));
			return true;
		}
		virtual bool LoadFromRwNode(Niflect::AddrType& base, const CRwNode& rw) const override
		{
			auto& instance = *static_cast<TMyTransform<T>*>(base);
			auto& rwValue = rw->ToValue();
			instance.m_scale = StringToMyVector<T>(rwValue->GetString());
			return true;
		}
		virtual bool SaveByPropertyPathRecurs(const Niflect::TArrayNif<const Niflect::CProperty*>& vecProp, uint32& frontIndex, const Niflect::AddrType& base, CRwNode& rw) const override
		{
			ASSERT(frontIndex == vecProp.size() - 1);
			ASSERT(vecProp[frontIndex] == this);
			return this->SaveToRwNode(base, rw);
		}
	};
	
	//class CJustSaveMySer : public Niflect::IMySer
	//{
	//public:
	//	virtual bool MySave(const Niflect::AddrType& base, const Niflect::TArrayNif<Niflect::CProperty*>& vecProp, uint32& frontIndex, CRwNode& rw) const override
	//	{
	//		ASSERT(frontIndex == vecProp.size() - 1);
	//		auto& prop = vecProp[frontIndex];
	//		return prop->SaveToRwNode(base, rw);
	//	}
	//};

	template <typename T>
	class TMyTransformField : public Niflect::CField
	{
	//public:
	//	void SetSaveToRwNode(const Niflect::CSharedAccessorSaveToRwNode& accessor)
	//	{
	//		m_saveToRwNode = accessor;
	//	}
	//	void SetLoadFromRwNode(const Niflect::CSharedAccessorLoadFromRwNode& accessor)
	//	{
	//		m_loadFromRwNode = accessor;
	//	}
	//	void SetCreatePropertyTree(const Niflect::CSharedAccessorCreatePropertyTree& accessor)
	//	{
	//		m_createPropertyTree = accessor;
	//	}

	protected:
		virtual bool FieldSaveToRwNode(const Niflect::AddrType& base, CRwNode& rw) const override
		{
			auto& instance = *static_cast<TMyTransform<T>*>(base);
			AddRwString(rw, "m_translation", MyVectorToString<T>(instance.m_translation));
			AddRwString(rw, "m_rotation", MyQuaternionToString<T>(instance.m_rotation));
			AddRwString(rw, "m_scale", MyVectorToString<T>(instance.m_scale));
			return true;
		}
		virtual bool FieldLoadFromRwNode(Niflect::AddrType& base, const CRwNode& rw) const override
		{
			auto& instance = *static_cast<TMyTransform<T>*>(base);
			instance.m_translation = StringToMyVector<T>(FindRwString(rw, "m_translation"));
			instance.m_rotation = StringToMyQuaternion<T>(FindRwString(rw, "m_rotation"));
			instance.m_scale = StringToMyVector<T>(FindRwString(rw, "m_scale"));
			return true;
		}
		virtual bool FieldInitProperty(const Niflect::AddrType& base, Niflect::CProperty* prop, const Niflect::CCreatingPropertyTreeContext& context) const override
		{
			prop->InitMeta(this->GetName(), base, context.m_requiredPathBasedSerializer, false);

			{
				auto childProp = Niflect::MakeShared<TMyTransformTranslationProperty<T> >();
				childProp->InitMeta("My Translation", base, context.m_requiredPathBasedSerializer, true);
				childProp->InitParent(prop);
				prop->AddChild(childProp);
			}
			{
				auto childProp = Niflect::MakeShared<TMyTransformRotationProperty<T> >();
				childProp->InitMeta("My Rotation", base, context.m_requiredPathBasedSerializer, true);
				childProp->InitParent(prop);
				prop->AddChild(childProp);
			}
			{
				auto childProp = Niflect::MakeShared<TMyTransformScaleProperty<T> >();
				childProp->InitMeta("My Scale", base, context.m_requiredPathBasedSerializer, true);
				childProp->InitParent(prop);
				prop->AddChild(childProp);
			}
			return true;
		}

	//public:
	//	virtual bool AccessorSaveToRwNode(const Niflect::AddrType& base, CRwNode& rw) const override
	//	{
	//		return m_saveToRwNode->Do(this, base, rw);
	//	}
	//	virtual bool AccessorLoadFromRwNode(Niflect::AddrType& base, const CRwNode& rw) const override
	//	{
	//		return m_loadFromRwNode->Do(this, base, rw);
	//	}
	//	//virtual Niflect::CSharedProperty AccessorCreatePropertyTree(const Niflect::AddrType& base) const override
	//	//{
	//	//	return m_createPropertyTree->Do(this, base);
	//	//}

	//private:
	//	Niflect::CSharedAccessorSaveToRwNode m_saveToRwNode;
	//	Niflect::CSharedAccessorLoadFromRwNode m_loadFromRwNode;
	//	Niflect::CSharedAccessorCreatePropertyTree m_createPropertyTree;
	};

	typedef TMyTransformField<float> CMyTransformFloatField;
}