#pragma once
#include "Niflect/NiflectAccessor.h"

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

	class CStringAccessor : public Niflect::CAccessor
	{
	public:
		virtual bool SaveToRwNode(const AddrType base, CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto& instance = *static_cast<const Niflect::CString*>(offsetBase);
			ASSERT(!rw->IsValue());
			auto rwValue = rw->ToValue();
			rwValue->SetString(instance);
			return true;
		}
		virtual bool LoadFromRwNode(AddrType base, const CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto& instance = *static_cast<Niflect::CString*>(offsetBase);
			ASSERT(rw->IsValue());
			auto rwValue = rw->GetValue();
			instance = rwValue->GetString();
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
	static const AddrType GetElementBaseToRead(const TStlArray& array, uint32 idx, bool& stlBoolItemHandler);

	template <typename TStlArray>
	static AddrType GetElementBaseToWriteBegin(TStlArray& array, uint32 idx, bool& stlBoolItemHandler);

	template <typename TStlArray>
	static void GetElementBaseToWriteEnd(TStlArray& array, uint32 idx, bool& stlBoolItemHandler);

	template <typename TStlArray>
	inline const AddrType GetElementBaseToRead(const TStlArray& array, uint32 idx, bool& stlBoolItemHandler)
	{
		return &array[idx];
	}
	template <>
	inline const AddrType GetElementBaseToRead(const Niflect::TArrayNif<bool>& array, uint32 idx, bool& stlBoolItemHandler)
	{
		stlBoolItemHandler = array[idx];
		return &stlBoolItemHandler;
	}
	template <typename TStlArray>
	inline AddrType GetElementBaseToWriteBegin(TStlArray& array, uint32 idx, bool& stlBoolItemHandler)
	{
		return &array[idx];
	}
	template <>
	inline AddrType GetElementBaseToWriteBegin(Niflect::TArrayNif<bool>& array, uint32 idx, bool& stlBoolItemHandler)
	{
		return &stlBoolItemHandler;
	}
	template <typename TStlArray>
	inline void GetElementBaseToWriteEnd(TStlArray& array, uint32 idx, bool& stlBoolItemHandler)
	{
	}
	template <>
	inline void GetElementBaseToWriteEnd(Niflect::TArrayNif<bool>& array, uint32 idx, bool& stlBoolItemHandler)
	{
		array[idx] = stlBoolItemHandler;
	}

	template <typename TStlArray>
	class TStlArrayAccessor_HandledBitsBasedBoolArray : public Niflect::CAccessor
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
				auto elemBase = GetElementBaseToRead<TStlArray>(instance, idx, stlBoolItemHandler);
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
				auto elemBase = GetElementBaseToWriteBegin<TStlArray>(instance, idx, stlBoolItemHandler);
				if (elemAccessor->LoadFromRwNode(elemBase, rwItem))
					GetElementBaseToWriteEnd<TStlArray>(instance, idx, stlBoolItemHandler);
			}
			return true;
		}

	private:
		CAccessor* GetElementAccessor() const
		{
			return this->GetChild(0);
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
				auto elemBase = &instance[idx];//如std::vector<bool>无法支持, 因此额外定义特化模板 GetElementBaseToX, 也可改用std::vector<uint8>, 或另定义Accessor
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

	//todo: Bits Array 应改为特殊序列化, 如不需要逐个单独保存, 用不同大小的整数保存, 节省空间
	template <typename TStlArray>
	class TStlBitsArrayAccessor : public Niflect::CAccessor
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
				auto elem = instance[idx];
				auto elemBase = &elem;
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
			instance.resize(GetRwItemsCount(rwArray));
			for (auto idx = 0; idx < instance.size(); ++idx)
			{
				auto rwItem = rwArray->GetItem(idx);
				typename TStlArray::value_type elem;
				auto elemBase = &elem;
				if (elemAccessor->LoadFromRwNode(elemBase, rwItem))
					instance[idx] = elem;
			}
			return true;
		}

	private:
		CAccessor* GetElementAccessor() const
		{
			return this->GetChild(0);
		}
	};

	template <typename TStlMap>
	class TStlMapAccessor : public Niflect::CAccessor
	{
		using TElem = typename TStlMap::allocator_type::value_type;
	public:
		virtual bool SaveToRwNode(const AddrType base, CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto& instance = *static_cast<const TStlMap*>(offsetBase);
			ASSERT(!rw->IsArray());
			auto rwArray = rw->ToArray();
			auto elemAccessor = this->GetElementAccessor();
			for (auto& it : instance)
			{
				auto rwItem = CreateRwNode();
				auto elemBase = &it;
				if (elemAccessor->SaveToRwNode(elemBase, rwItem.Get()))
					rwArray->AddItem(rwItem);
			}
			return true;
		}
		virtual bool LoadFromRwNode(AddrType base, const CRwNode* rw) const override
		{
			auto offsetBase = this->GetAddr(base);
			auto& instance = *static_cast<TStlMap*>(offsetBase);
			ASSERT(rw->IsArray());
			auto rwArray = rw->GetArray();
			auto elemAccessor = this->GetElementAccessor();
			auto cnt = rwArray->GetItemsCount();
			for (uint32 idx = 0; idx < cnt; ++idx)
			{
				auto rwItem = rwArray->GetItem(idx);
				TElem item;
				auto elemBase = &item;
				if (elemAccessor->LoadFromRwNode(elemBase, rwItem))
					instance.insert(item);
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
