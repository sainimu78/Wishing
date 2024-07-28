#pragma once
#include "Niflect/Field/TemplateField.h"
#include "Niflect/Property/FieldProperty.h"

namespace Niflect
{
	//using CPairField = CCompoundField;

	//class IMapElement
	//{
	//public:
	//	virtual AddrType GetElementBaseAddr() = 0;
	//};
	//using CSharedMapElement = TSharedPtr<IMapElement>;

	//class IMapIterator
	//{
	//public:
	//	virtual bool IsEnd() const = 0;
	//	virtual void Next() = 0;
	//	virtual CSharedMapElement GetElement() const = 0;
	//};
	//using CSharedMapIterator = TSharedPtr<IMapIterator>;

	//class IMapTempElement
	//{
	//public:
	//	virtual AddrType GetElementBaseAddr() = 0;
	//	virtual void InsertTo(AddrType base) const = 0;
	//};
	//using CSharedMapTempElement = TSharedPtr<IMapTempElement>;

	//class IMapAccessor
	//{
	//public:
	//	virtual CSharedMapIterator GetBeginIterator(const AddrType& base) const = 0;
	//	virtual CSharedMapTempElement CreateElement() const = 0;
	//};
	//using CSharedMapAccessor = TSharedPtr<IMapAccessor>;

	//class CMapField : public CContainerField
	//{
	//public:
	//	void SetAccessor(const CSharedMapAccessor& accessor)
	//	{
	//		m_accessor = accessor;
	//	}

	//public:
	//	virtual bool SaveToRwNode(const AddrType& base, CRwNode& rw) const override
	//	{
	//		auto it = m_accessor->GetBeginIterator(base);
	//		auto& rwArray = rw->ToArray();
	//		while (!it->IsEnd())
	//		{
	//			auto& rwItem = rwArray->AddItemNode();
	//			auto elem = it->GetElement();
	//			auto elemBase = elem->GetElementBaseAddr();
	//			this->GetElementField()->SaveToRwNode(elemBase, rwItem);
	//			it->Next();
	//		}
	//		return true;
	//	}
	//	virtual bool LoadFromRwNode(AddrType& base, const CRwNode& rw) const override
	//	{
	//		auto& rwArray = rw->ToArray();
	//		auto count = GetRwItemsCount(rwArray);
	//		for (uint32 idx = 0; idx < count; ++idx)
	//		{
	//			auto& rwItem = rwArray->GetItemNode(idx);
	//			auto elem = m_accessor->CreateElement();
	//			auto elemBase = elem->GetElementBaseAddr();
	//			this->GetElementField()->LoadFromRwNode(elemBase, rwItem);
	//			elem->InsertTo(base);
	//		}
	//		return true;
	//	}

	//public:
	//	virtual CSharedProperty CreatePropertyTree(const AddrType& base) override
	//	{
	//		auto parentProp = Niflect::MakeShared<Niflect::CFieldProperty>();
	//		parentProp->InitMeta(this->GetName(), base, false);
	//		parentProp->SetField(this);
	//		auto it = m_accessor->GetBeginIterator(base);
	//		while (!it->IsEnd())
	//		{
	//			auto elem = it->GetElement();
	//			auto elemBase = elem->GetElementBaseAddr();
	//			auto elemProp = this->GetElementField()->CreatePropertyTree(elemBase);
	//			parentProp->AddChild(elemProp);
	//			it->Next();
	//		}
	//		return parentProp;
	//	}

	//private:
	//	CField* GetElementField() const
	//	{
	//		return this->GetArgumentField(0);
	//	}

	//public:
	//	static CMapField* Cast(CField* base)
	//	{
	//		ASSERT(dynamic_cast<CMapField*>(base) != NULL);
	//		return static_cast<CMapField*>(base);
	//	}

	//private:
	//	CSharedMapAccessor m_accessor;
	//};
	//
	//template <typename TElem>
	//class CMapElementAddr : public IMapElement
	//{
	//public:
	//	CMapElementAddr(TElem& elem)
	//		: m_elem(elem)
	//	{
	//	}

	//public:
	//	virtual AddrType GetElementBaseAddr() override
	//	{
	//		return &m_elem;
	//	}

	//private:
	//	TElem& m_elem;
	//};

	//template <typename TMapType, typename TElem>
	//class CMapIteratorAddr : public IMapIterator
	//{
	//public:
	//	CMapIteratorAddr(const TMapType& map, const typename TMapType::iterator& it)
	//		: m_map(map)
	//		, m_it(it)
	//	{
	//	}

	//public:
	//	virtual bool IsEnd() const override
	//	{
	//		return m_it == m_map.end();
	//	}
	//	virtual void Next() override
	//	{
	//		m_it++;
	//	}
	//	virtual CSharedMapElement GetElement() const override
	//	{
	//		return MakeShared<CMapElementAddr<TElem> >(*m_it);
	//	}

	//private:
	//	const TMapType& m_map;
	//	typename TMapType::iterator m_it;
	//};

	//template <typename TMapType, typename TElem>
	//class TMapTempElementAddr : public IMapTempElement
	//{
	//public:
	//	virtual AddrType GetElementBaseAddr() override
	//	{
	//		return &m_elem;
	//	}
	//	virtual void InsertTo(AddrType base) const override
	//	{
	//		auto& map = *static_cast<TMapType*>(base);
	//		map.insert(m_elem);
	//	}

	//private:
	//	TElem m_elem;
	//};

	//template <typename TMapType>
	//class TMapAccessorAddr : public IMapAccessor
	//{
	//	using TElem = typename TMapType::allocator_type::value_type;
	//public:
	//	virtual CSharedMapIterator GetBeginIterator(const AddrType& base) const override
	//	{
	//		auto& map = *static_cast<TMapType*>(base);
	//		return MakeShared<CMapIteratorAddr<TMapType, TElem> >(map, map.begin());
	//	}
	//	virtual CSharedMapTempElement CreateElement() const override
	//	{
	//		return MakeShared<TMapTempElementAddr<TMapType, TElem> >();
	//	}
	//};
	//
	//template <typename TType>
	//struct SFieldCreator<CMapField, TType>
	//{
	//	static TSharedPtr<CMapField> Create()
	//	{
	//		auto shared1 = Niflect::MakeShared<CMapField>();
	//		auto field1 = shared1.Get();
	//		field1->SetAccessor(MakeShared<TMapAccessorAddr<TType> >());
	//		return shared1;
	//	}
	//};

	using CPairField = CCompoundField;

	class IMapElement
	{
	public:
		virtual AddrType GetElementBaseAddr() = 0;
	};
	using CSharedMapElement = TSharedPtr<IMapElement>;

	class IMapIterator
	{
	public:
		virtual bool IsEnd() const = 0;
		virtual void Next() = 0;
		virtual CSharedMapElement GetElement() const = 0;
	};
	using CSharedMapIterator = TSharedPtr<IMapIterator>;

	class IMapTempElement
	{
	public:
		virtual AddrType GetElementBaseAddr() = 0;
		virtual void InsertTo(AddrType base) const = 0;
	};
	using CSharedMapTempElement = TSharedPtr<IMapTempElement>;

	class IMapDelegate
	{
	public:
		virtual CSharedMapIterator GetBeginIterator(const AddrType& base) const = 0;
		virtual CSharedMapTempElement CreateElement() const = 0;
	};
	using CSharedMapDelegate = TSharedPtr<IMapDelegate>;

	class CMapField : public CContainerField
	{
	public:
		void InitDelegate(const CSharedMapDelegate& delegate)
		{
			m_delegate = delegate;
		}

	public:
		virtual bool FieldSaveToRwNode(const AddrType& base, CRwNode& rw) const override
		{
			auto it = m_delegate->GetBeginIterator(base);
			auto& rwArray = rw->ToArray();
			while (!it->IsEnd())
			{
				auto& rwItem = rwArray->AddItemNode();
				auto elem = it->GetElement();
				auto elemBase = elem->GetElementBaseAddr();
				this->GetElementField()->SaveToRwNode(elemBase, rwItem);
				it->Next();
			}
			return true;
		}
		virtual bool FieldLoadFromRwNode(AddrType& base, const CRwNode& rw) const override
		{
			auto& rwArray = rw->ToArray();
			auto count = GetRwItemsCount(rwArray);
			for (uint32 idx = 0; idx < count; ++idx)
			{
				auto& rwItem = rwArray->GetItemNode(idx);
				auto elem = m_delegate->CreateElement();
				auto elemBase = elem->GetElementBaseAddr();
				this->GetElementField()->LoadFromRwNode(elemBase, rwItem);
				elem->InsertTo(base);
			}
			return true;
		}

	public:
		virtual bool FieldInitProperty(const AddrType& base, CProperty* prop, const CCreatingPropertyTreeContext& context) const override
		{
			prop->InitMeta(this->GetName(), base, context.m_requiredPathBasedSerializer, false);

			auto it = m_delegate->GetBeginIterator(base);
			while (!it->IsEnd())
			{
				auto elem = it->GetElement();
				auto elemBase = elem->GetElementBaseAddr();
				
				auto elemProp = MakeShared<CFieldProperty>(this, MakeShared<CPropertyPathSerializerAddr>(CAddrOffset::None));
				this->GetElementField()->FieldInitProperty(elemBase, elemProp.Get(), context);

				elemProp->InitParent(prop);
				prop->AddChild(elemProp);
				it->Next();
			}
			return true;
		}

	private:
		CField* GetElementField() const
		{
			return this->GetArgumentField(0);
		}

	public:
		static CMapField* Cast(CField* base)
		{
			ASSERT(dynamic_cast<CMapField*>(base) != NULL);
			return static_cast<CMapField*>(base);
		}

	private:
		CSharedMapDelegate m_delegate;
	};
	
	template <typename TElem>
	class CMapElementStlCompliant : public IMapElement
	{
	public:
		CMapElementStlCompliant(TElem& elem)
			: m_elem(elem)
		{
		}

	public:
		virtual AddrType GetElementBaseAddr() override
		{
			return &m_elem;
		}

	private:
		TElem& m_elem;
	};

	template <typename TMapType, typename TElem>
	class CMapIteratorStlCompliant : public IMapIterator
	{
	public:
		CMapIteratorStlCompliant(const TMapType& map, const typename TMapType::iterator& it)
			: m_map(map)
			, m_it(it)
		{
		}

	public:
		virtual bool IsEnd() const override
		{
			return m_it == m_map.end();
		}
		virtual void Next() override
		{
			m_it++;
		}
		virtual CSharedMapElement GetElement() const override
		{
			return MakeShared<CMapElementStlCompliant<TElem> >(*m_it);
		}

	private:
		const TMapType& m_map;
		typename TMapType::iterator m_it;
	};

	template <typename TMapType, typename TElem>
	class TMapTempElementStlCompliant : public IMapTempElement
	{
	public:
		virtual AddrType GetElementBaseAddr() override
		{
			return &m_elem;
		}
		virtual void InsertTo(AddrType base) const override
		{
			auto& map = *static_cast<TMapType*>(base);
			map.insert(m_elem);
		}

	private:
		TElem m_elem;
	};

	template <typename TMapType>
	class TMapDelegateStlCompliant : public IMapDelegate
	{
		using TElem = typename TMapType::allocator_type::value_type;
	public:
		virtual CSharedMapIterator GetBeginIterator(const AddrType& base) const override
		{
			auto& map = *static_cast<TMapType*>(base);
			return MakeShared<CMapIteratorStlCompliant<TMapType, TElem> >(map, map.begin());
		}
		virtual CSharedMapTempElement CreateElement() const override
		{
			return MakeShared<TMapTempElementStlCompliant<TMapType, TElem> >();
		}
	};
	
	template <typename TType>
	struct SFieldCreator<CMapField, TType>
	{
		static TSharedPtr<CMapField> Create()
		{
			auto shared1 = Niflect::MakeShared<CMapField>();
			auto field1 = shared1.Get();
			field1->InitDelegate(MakeShared<TMapDelegateStlCompliant<TType> >());
			return shared1;
		}
	};
}