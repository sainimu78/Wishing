#pragma once
#include "Niflect/Base/NiflectBase.h"
#include "Niflect/Util/DebugUtil.h"

namespace Niflect
{
	enum class ERwValueType : uint8
	{
		None,
		Bool,
		Int32,
		Float,
		Double,
		String,
	};

	using CInternalRwBuffer = Niflect::CString;//用字符串是为顺便避免String类型的转换

	class CRwValue
	{
	public:
		CRwValue(CInternalRwBuffer& data, ERwValueType& type)
			: m_data(data)
			, m_type(type)
		{
		}
		const ERwValueType& GetType() const
		{
			return m_type;
		}
		void SetBool(bool val)
		{
			m_type = ERwValueType::Bool;
			auto cnt = sizeof(val);
			m_data.resize(cnt);
			memcpy(&m_data[0], &val, cnt);
		}
		const bool& GetBool() const
		{
			ASSERT(m_type == ERwValueType::Bool);
			return *reinterpret_cast<bool*>(&m_data[0]);
		}
		void SetFloat(float val)
		{
			m_type = ERwValueType::Float;
			auto cnt = sizeof(val);
			m_data.resize(cnt);
			memcpy(&m_data[0], &val, cnt);
		}
		const float& GetFloat() const
		{
			ASSERT(m_type == ERwValueType::Float);
			return *reinterpret_cast<float*>(&m_data[0]);
		}
		void SetDouble(double val)
		{
			m_type = ERwValueType::Double;
			auto cnt = sizeof(val);
			m_data.resize(cnt);
			memcpy(&m_data[0], &val, cnt);
		}
		const double& GetDouble() const
		{
			ASSERT(m_type == ERwValueType::Double);
			return *reinterpret_cast<double*>(&m_data[0]);
		}
		void SetInt32(int32 val)
		{
			m_type = ERwValueType::Int32;
			auto cnt = sizeof(val);
			m_data.resize(cnt);
			memcpy(&m_data[0], &val, cnt);
		}
		const int32& GetInt32() const
		{
			ASSERT(m_type == ERwValueType::Int32);
			return *reinterpret_cast<int32*>(&m_data[0]);
		}
		void SetString(const Niflect::CString& val)
		{
			m_type = ERwValueType::String;
			m_data = val;
		}
		const Niflect::CString& GetString() const
		{
			ASSERT(m_type == ERwValueType::String);
			return m_data;
		}

	private:
		CInternalRwBuffer& m_data;
		ERwValueType& m_type;
	};
	using CSharedRwValue = Niflect::TSharedPtr<CRwValue>;

	//template <typename TImpl>
	//class TInternalRwWrapper
	//{
	//public:
	//	TInternalRwWrapper()
	//		: m_p(NULL)
	//	{
	//	}
	//	TInternalRwWrapper(const TInternalRwWrapper& rhs)
	//		: m_p(rhs.m_p)
	//	{
	//	}
	//	TInternalRwWrapper(TImpl* p)
	//		: m_p(p)
	//	{
	//	}
	//	TInternalRwWrapper(const Niflect::TSharedPtr<TImpl>& shared)
	//		: m_p(shared.Get())
	//		, m_shared(shared)
	//	{
	//	}
	//	explicit operator bool() const
	//	{
	//		return m_p != NULL;
	//	}
	//	TImpl* operator->() const
	//	{
	//		return m_p;
	//	}
	//	TImpl* m_p;
	//	Niflect::TSharedPtr<TImpl> m_shared;
	//};

	class CRwNode;
	using CSharedRwNode = Niflect::TSharedPtr<CRwNode>;

	class CRwArray
	{
	public:
		CRwArray(CInternalRwBuffer& data, Niflect::TArrayNif<CSharedRwNode>& vecItem)
			: m_data(data)
			, m_vecItem(vecItem)
		{
		}
		void AddItem(const CSharedRwNode& item)
		{
			m_vecItem.push_back(item);
		}
		CRwNode* AddItemNode()
		{
			return InternalAddItemNode(this);
		}
		CRwValue* AddItemValue()
		{
			return InternalAddItemValue(this);
		}
		CRwArray* AddItemArray()
		{
			return InternalAddItemArray(this);
		}
		void AddFloat(float val)
		{
			auto rwValue = this->AddItemValue();
			rwValue->SetFloat(val);
		}
		void AddItemBool(bool value)
		{
			auto rwValue = this->AddItemValue();
			rwValue->SetBool(value);
		}
		void AddItemInt32(int32 value)
		{
			auto rwValue = this->AddItemValue();
			rwValue->SetInt32(value);
		}
		void AddItemFloat(float value)
		{
			auto rwValue = this->AddItemValue();
			rwValue->SetFloat(value);
		}
		void AddItemString(const CString& value)
		{
			auto rwValue = this->AddItemValue();
			rwValue->SetString(value);
		}
		void SetItem(const CSharedRwNode& item, uint32 idx)
		{
			m_vecItem[idx] = item;
		}
		CRwNode* GetItem(uint32 idx) const
		{
			return m_vecItem[idx].Get();
		}
		uint32 GetItemsCount() const
		{
			return static_cast<uint32>(m_vecItem.size());
		}
		void Resize(uint32 cnt)
		{
			m_vecItem.resize(cnt);
		}

	private:
		static CRwNode* InternalAddItemNode(CRwArray* rwArray);
		static CRwValue* InternalAddItemValue(CRwArray* rwArray);
		static CRwArray* InternalAddItemArray(CRwArray* rwArray);

	private:
		CInternalRwBuffer& m_data;
		Niflect::TArrayNif<CSharedRwNode>& m_vecItem;
	};
	using CSharedRwArray = Niflect::TSharedPtr<CRwArray>;

	class CRwNode
	{
	public:
		CRwNode()
			: m_valueType(ERwValueType::None)
		{
		}
		~CRwNode()
		{

		}
		void SetName(const Niflect::CString& name)
		{
			m_name = name;
		}
		const Niflect::CString& GetName() const
		{
			return m_name;
		}
		bool IsValue() const
		{
			return m_rwValue != NULL;
		}
		bool IsArray() const
		{
			return m_rwArray != NULL;
		}
		void AddNode(const CSharedRwNode& node)
		{
			this->InsertNode(node, this->GetNodesCount());
		}
		void InsertNode(const CSharedRwNode& node, uint32 idx)
		{
			m_vecNode.insert(m_vecNode.begin() + idx, node);
		}
		CRwNode* FindNode(const Niflect::CString& name) const
		{
			for (auto& it : m_vecNode)
			{
				if (it->GetName() == name)
					return it.Get();
			}
			return NULL;
		}
		void Resize(uint32 cnt)
		{
			m_vecNode.resize(cnt);
		}
		void Delete(uint32 idx)
		{
			m_vecNode.erase(m_vecNode.begin() + idx);
		}
		void ResetType()
		{
			m_rwValue = NULL;
			m_rwArray = NULL;
		}
		void ClearNodes()
		{
			m_vecNode.clear();
		}
		void SetNode(const CSharedRwNode& rwNode, uint32 idx)
		{
			m_vecNode[idx] = rwNode;
		}
		CRwNode* GetNode(uint32 idx) const
		{
			return m_vecNode[idx].Get();
		}
		CSharedRwNode GetSharedNode(uint32 idx) const
		{
			return m_vecNode[idx];
		}
		uint32 GetNodesCount() const
		{
			return static_cast<uint32>(m_vecNode.size());
		}
		CRwValue* ToValue()
		{
			if (m_rwValue == NULL)
			{
				ASSERT(m_rwArray == NULL);
				m_rwArray = NULL;
				m_rwValue = Niflect::MakeShared<CRwValue>(m_data, m_valueType);
			}
			return m_rwValue.Get();
		}
		CRwValue* GetValue() const
		{
			return m_rwValue.Get();
		}
		CRwArray* ToArray()
		{
			if (m_rwArray == NULL)
			{
				ASSERT(m_rwValue == NULL);
				m_rwValue = NULL;
				m_rwArray = Niflect::MakeShared<CRwArray>(m_data, m_vecNode);
			}
			return m_rwArray.Get();
		}
		CRwArray* GetArray() const
		{
			return m_rwArray.Get();
		}
		const CInternalRwBuffer& GetData() const
		{
			return m_data;
		}

	private:
		Niflect::CString m_name;
		ERwValueType m_valueType;
		Niflect::TArrayNif<CSharedRwNode> m_vecNode;
		CInternalRwBuffer m_data;
		CSharedRwValue m_rwValue;
		CSharedRwArray m_rwArray;
	};
	static CSharedRwNode CreateRwNode()
	{
		return Niflect::MakeShared<CRwNode>();
	}
	inline CRwNode* CRwArray::InternalAddItemNode(CRwArray* rwArray)
	{
		auto rwNode = CreateRwNode();
		rwArray->AddItem(rwNode);
		return rwNode.Get();
	}
	inline CRwValue* CRwArray::InternalAddItemValue(CRwArray* rwArray)
	{
		auto rwNode = CreateRwNode();
		rwArray->AddItem(rwNode);
		return rwNode->ToValue();
	}
	inline CRwArray* CRwArray::InternalAddItemArray(CRwArray* rwArray)
	{
		auto rwNode = CreateRwNode();
		rwArray->AddItem(rwNode);
		return rwNode->ToArray();
	}

	static CRwNode* FindRwNode(const CRwNode* rwParent, const Niflect::CString& name)
	{
		if (rwParent != NULL)
			return rwParent->FindNode(name);
		return NULL;
	}
	static CRwArray* FindRwArray(const CRwNode* rwParent, const Niflect::CString& name)
	{
		if (auto rwNode = FindRwNode(rwParent, name))
			return rwNode->ToArray();
		return NULL;
	}
	static CRwValue* FindRwValue(const CRwNode* rwParent, const Niflect::CString& name)
	{
		if (auto rwNode = FindRwNode(rwParent, name))
			return rwNode->ToValue();
		return NULL;
	}
	static bool FindRwBool(const CRwNode* rwParent, const Niflect::CString& name, bool defaultValue = false)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetBool();
		return value;
	}
	static int32 FindRwInt32(const CRwNode* rwParent, const Niflect::CString& name, int32 defaultValue = 0)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetInt32();
		return value;
	}
	//static uint32 FindRwUint32(const CRwNode& rwParent, const Niflect::CString& name, uint32 defaultValue = 0u)
	//{
	//	auto value = defaultValue;
	//	if (auto rwValue = FindRwValue(rwParent, name))
	//		value = rwValue->GetUint32();
	//	return value;
	//}
	static float FindRwFloat(const CRwNode* rwParent, const Niflect::CString& name, float defaultValue = 0.0f)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetFloat();
		return value;
	}
	static Niflect::CString FindRwString(const CRwNode* rwParent, const Niflect::CString& name, const Niflect::CString& defaultValue = Niflect::CString())
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetString();
		return value;
	}
	//static CRwRawData FindRwRawData(const CRwNode& rwParent, const Niflect::CString& name)
	//{
	//	CRwRawData rawData;
	//	if (auto rwValue = FindRwValue(rwParent, name))
	//		rwValue->GetRawData(rawData);
	//	return rawData;
	//}
	static uint32 GetRwNodesCount(const CRwNode* rwParent)
	{
		uint32 count = 0;
		if (rwParent != NULL)
			count = rwParent->GetNodesCount();
		return count;
	}
	static CRwNode* GetRwNode(const CRwNode* rwParent, uint32 idx)
	{
		CRwNode* node = NULL;
		if (rwParent != NULL)
			node = rwParent->GetNode(idx);
		return node;
	}
	static CRwArray* ToRwArray(CRwNode* rwNode)
	{
		if (rwNode != NULL)
			return rwNode->ToArray();
		return NULL;
	}
	static CRwValue* ToRwValue(CRwNode* rwNode)
	{
		if (rwNode != NULL)
			return rwNode->ToValue();
		return NULL;
	}
	static uint32 GetRwItemsCount(const CRwArray* rwArray)
	{
		uint32 count = 0;
		if (rwArray != NULL)
			count = rwArray->GetItemsCount();
		return count;
	}
	static bool AddExistingRwNode(CRwNode* rwParent, const Niflect::CString& name, const CSharedRwNode& shared, uint32* insertedIndex = NULL)
	{
		//if (rwParent != NULL)
		//	return rwParent->AddNode(name, rwNode, insertedIndex);
		//return NULL;

		if (rwParent != NULL)
		{
			ASSERT(shared->GetName().empty());
			shared->SetName(name);
			if (insertedIndex != NULL)
				*insertedIndex = rwParent->GetNodesCount();
			rwParent->AddNode(shared);
			return true;
		}
		return false;
	}
	static CRwNode* AddRwNode(CRwNode* rwParent, const Niflect::CString& name, uint32* insertedIndex = NULL)
	{
		//if (rwParent != NULL)
		//	return rwParent->CreateAndAddNode(name, insertedIndex);
		//return NULL;

		auto shared = CreateRwNode();
		uint32 idx = INDEX_NONE;
		if (AddExistingRwNode(rwParent, name, shared, &idx))
		{
			if (insertedIndex != NULL)
				*insertedIndex = idx;
			return shared.Get();
		}
		return NULL;
	}
	static CRwArray* AddRwArray(CRwNode* rwParent, const Niflect::CString& name, uint32* insertedIndex = NULL)
	{
		return AddRwNode(rwParent, name, insertedIndex)->ToArray();
	}
	static CRwValue* AddRwValue(CRwNode* rwParent, const Niflect::CString& name, uint32* insertedIndex = NULL)
	{
		return AddRwNode(rwParent, name, insertedIndex)->ToValue();
	}
	static void AddRwBool(CRwNode* rwParent, const Niflect::CString& name, bool value)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetBool(value);
	}
	static void AddRwInt32(CRwNode* rwParent, const Niflect::CString& name, int32 value)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetInt32(value);
	}
	//static void AddRwUint32(CRwNode& rwParent, const Niflect::CString& name, uint32 value)
	//{
	//	if (auto rwValue = AddRwValue(rwParent, name))
	//		rwValue->SetUint32(value);
	//}
	static void AddRwFloat(CRwNode* rwParent, const Niflect::CString& name, float value)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetFloat(value);
	}
	static void AddRwDouble(CRwNode* rwParent, const Niflect::CString& name, double value)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetDouble(value);
	}
	static void AddRwString(CRwNode* rwParent, const Niflect::CString& name, const Niflect::CString& value)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetString(value);
	}
	//static void AddRwRawData(CRwNode& rwParent, const Niflect::CString& name, const void* data, const size_t size)
	//{
	//	if (auto rwValue = AddRwValue(rwParent, name))
	//		rwValue->SetRawData(data, size);
	//}







	//static CRwNode FindRwNode(const CRwNode& rwParent, const Niflect::CString& name)
	//{
	//	if (rwParent != NULL)
	//		return rwParent->FindNode(name);
	//	return NULL;
	//}
	//static CRwArray FindRwArray(const CRwNode& rwParent, const Niflect::CString& name)
	//{
	//	if (auto rwNode = FindRwNode(rwParent, name))
	//		return rwNode->ToArray();
	//	return NULL;
	//}
	//static CRwValue FindRwValue(const CRwNode& rwParent, const Niflect::CString& name)
	//{
	//	if (auto rwNode = FindRwNode(rwParent, name))
	//		return rwNode->ToValue();
	//	return NULL;
	//}
	//static bool FindRwBool(const CRwNode& rwParent, const Niflect::CString& name, bool defaultValue = false)
	//{
	//	auto value = defaultValue;
	//	if (auto rwValue = FindRwValue(rwParent, name))
	//		value = rwValue->GetBool();
	//	return value;
	//}
	//static int32 FindRwInt32(const CRwNode& rwParent, const Niflect::CString& name, int32 defaultValue = 0)
	//{
	//	auto value = defaultValue;
	//	if (auto rwValue = FindRwValue(rwParent, name))
	//		value = rwValue->GetInt32();
	//	return value;
	//}
	////static uint32 FindRwUint32(const CRwNode& rwParent, const Niflect::CString& name, uint32 defaultValue = 0u)
	////{
	////	auto value = defaultValue;
	////	if (auto rwValue = FindRwValue(rwParent, name))
	////		value = rwValue->GetUint32();
	////	return value;
	////}
	//static float FindRwFloat(const CRwNode& rwParent, const Niflect::CString& name, float defaultValue = 0.0f)
	//{
	//	auto value = defaultValue;
	//	if (auto rwValue = FindRwValue(rwParent, name))
	//		value = rwValue->GetFloat();
	//	return value;
	//}
	//static Niflect::CString FindRwString(const CRwNode& rwParent, const Niflect::CString& name, const Niflect::CString& defaultValue = Niflect::CString())
	//{
	//	auto value = defaultValue;
	//	if (auto rwValue = FindRwValue(rwParent, name))
	//		value = rwValue->GetString();
	//	return value;
	//}
	////static CRwRawData FindRwRawData(const CRwNode& rwParent, const Niflect::CString& name)
	////{
	////	CRwRawData rawData;
	////	if (auto rwValue = FindRwValue(rwParent, name))
	////		rwValue->GetRawData(rawData);
	////	return rawData;
	////}
	//static uint32 GetRwNodesCount(const CRwNode& rwParent)
	//{
	//	uint32 count = 0;
	//	if (rwParent != NULL)
	//		count = rwParent->GetNodesCount();
	//	return count;
	//}
	//static CRwNode GetRwNode(const CRwNode& rwParent, uint32 idx)
	//{
	//	CRwNode node = NULL;
	//	if (rwParent != NULL)
	//		node = rwParent->GetNode(idx);
	//	return node;
	//}
	//static CRwArray ToRwArray(const CRwNode& rwNode)
	//{
	//	if (rwNode != NULL)
	//		return rwNode->ToArray();
	//	return NULL;
	//}
	//static CRwValue ToRwValue(const CRwNode& rwNode)
	//{
	//	if (rwNode != NULL)
	//		return rwNode->ToValue();
	//	return NULL;
	//}
	//static uint32 GetRwItemsCount(const CRwArrayImpl* rwArray)
	//{
	//	uint32 count = 0;
	//	if (rwArray != NULL)
	//		count = rwArray->GetItemsCount();
	//	return count;
	//}
	//static CSharedRwNode CreateRwNode()
	//{
	//	return MakeShared<CRwNodeImpl>();
	//}
	//static void AddExistingRwNode(CRwNode& rwParent, const Niflect::CString& name, const CSharedRwNode& shared, uint32* insertedIndex = NULL)
	//{
	//	//if (rwParent != NULL)
	//	//	return rwParent->AddNode(name, rwNode, insertedIndex);
	//	//return NULL;

	//	if (rwParent != NULL)
	//	{
	//		ASSERT(shared->GetName().empty());
	//		shared->SetName(name);
	//		if (insertedIndex != NULL)
	//			*insertedIndex = rwParent->GetNodesCount();
	//		rwParent->AddNode(shared);
	//	}
	//}
	//static CRwNode AddRwNode(CRwNode& rwParent, const Niflect::CString& name, uint32* insertedIndex = NULL)
	//{
	//	//if (rwParent != NULL)
	//	//	return rwParent->CreateAndAddNode(name, insertedIndex);
	//	//return NULL;

	//	CRwNode node = NULL;
	//	if (rwParent != NULL)
	//	{
	//		auto shared = CreateRwNode();
	//		uint32 idx = INDEX_NONE;
	//		AddExistingRwNode(rwParent, name, shared, &idx);
	//		if (insertedIndex != NULL)
	//			*insertedIndex = idx;
	//		node = rwParent->GetNode(idx);
	//	}
	//	return node;
	//}
	//static CRwArray AddRwArray(CRwNode& rwParent, const Niflect::CString& name, uint32* insertedIndex = NULL)
	//{
	//	if (rwParent != NULL)
	//		return AddRwNode(rwParent, name, insertedIndex)->ToArray();
	//	return NULL;
	//}
	//static CRwValue AddRwValue(CRwNode& rwParent, const Niflect::CString& name, uint32* insertedIndex = NULL)
	//{
	//	if (rwParent != NULL)
	//		return AddRwNode(rwParent, name, insertedIndex)->ToValue();
	//	return NULL;
	//}
	//static void AddRwBool(CRwNode& rwParent, const Niflect::CString& name, bool value)
	//{
	//	if (auto rwValue = AddRwValue(rwParent, name))
	//		rwValue->SetBool(value);
	//}
	//static void AddRwInt32(CRwNode& rwParent, const Niflect::CString& name, int32 value)
	//{
	//	if (auto rwValue = AddRwValue(rwParent, name))
	//		rwValue->SetInt32(value);
	//}
	////static void AddRwUint32(CRwNode& rwParent, const Niflect::CString& name, uint32 value)
	////{
	////	if (auto rwValue = AddRwValue(rwParent, name))
	////		rwValue->SetUint32(value);
	////}
	//static void AddRwFloat(CRwNode& rwParent, const Niflect::CString& name, float value)
	//{
	//	if (auto rwValue = AddRwValue(rwParent, name))
	//		rwValue->SetFloat(value);
	//}
	//static void AddRwDouble(CRwNode& rwParent, const Niflect::CString& name, double value)
	//{
	//	if (auto rwValue = AddRwValue(rwParent, name))
	//		rwValue->SetDouble(value);
	//}
	//static void AddRwString(CRwNode& rwParent, const Niflect::CString& name, const Niflect::CString& value)
	//{
	//	if (auto rwValue = AddRwValue(rwParent, name))
	//		rwValue->SetString(value);
	//}
	////static void AddRwRawData(CRwNode& rwParent, const Niflect::CString& name, const void* data, const size_t size)
	////{
	////	if (auto rwValue = AddRwValue(rwParent, name))
	////		rwValue->SetRawData(data, size);
	////}


}

namespace Niflect
{
	static void DebugBuildSingleValue(CRwNode* root)
	{
		auto value = ToRwValue(root);
		value->SetFloat(1.23f);
	}
	static void DebugBuildSingleArray(CRwNode* root)
	{
		auto rwArray = ToRwArray(root);
		rwArray->AddFloat(1.23f);
		rwArray->AddFloat(4.56f);
	}
	static void DebugBuildStructure(CRwNode* root)
	{
		AddRwFloat(root, "Nihao", 1.23f);
		{
			auto node0 = AddRwNode(root, "Haike");
			AddRwFloat(node0, "Bucuo", 4.56f);
			AddRwFloat(node0, "Shima", 7.89f);
			AddRwString(node0, "Zhende", "Some Text");
		}
		{
			auto rwArray = AddRwArray(root, "Buxin");
			rwArray->AddFloat(2.34f);
			rwArray->AddFloat(2.56f);
		}
		{
			auto rwArray = AddRwArray(root, "Shide");
			{
				auto node1 = rwArray->AddItemNode();
				AddRwFloat(node1, "My Value 0", 3.12f);
			}
			{
				auto node1 = rwArray->AddItemNode();
				AddRwBool(node1, "My Value 1", false);
			}
			{
				auto node1 = rwArray->AddItemNode();
				AddRwBool(node1, "My Value 2", true);
			}
			{
				auto node1 = rwArray->AddItemNode();
				AddRwString(node1, "My Value 3", "My String Value");
			}
		}
	}

	//static void DebugPrintRecurs(const CRwNode& rwNode, uint32 arrayItemIdx = INDEX_NONE, uint32 level = 0)
	//{
	//	auto strLevel = NiflectUtil::DebugIndentToString(level);
	//	printf("%s", strLevel.c_str());
	//	if (arrayItemIdx == INDEX_NONE)
	//	{
	//		printf("%s", rwNode->GetName().c_str());
	//	}
	//	else
	//	{
	//		ASSERT(rwNode->GetName().empty());
	//		printf("[%u]", arrayItemIdx);
	//	}
	//	if (rwNode->IsValue())
	//	{
	//		if (arrayItemIdx == INDEX_NONE)
	//			printf(", ");

	//		Niflect::CString str;
	//		auto rwValue = rwNode->GetValue();
	//		switch (rwValue->GetType())
	//		{
	//		case ERwValueType::Bool:
	//			str = rwValue->GetBool() ? "true" : "false";
	//			break;
	//		case ERwValueType::Float:
	//			str = std::to_string(rwValue->GetFloat()).c_str();
	//			break;
	//		case ERwValueType::Double:
	//			str = std::to_string(rwValue->GetDouble()).c_str();
	//			break;
	//		case ERwValueType::Int32:
	//			str = std::to_string(rwValue->GetInt32()).c_str();
	//			break;
	//		case ERwValueType::String:
	//			str = rwValue->GetString().c_str();
	//			break;
	//		default:
	//			ASSERT(false);
	//			break;
	//		}
	//		printf("%s", str.c_str());
	//		printf("\n");
	//	}
	//	else if (rwNode->IsArray())
	//	{
	//		level++;
	//		printf("\n");
	//		auto rwArray = rwNode->GetArray();
	//		uint32 idxInc = 0;
	//		for (uint32 idx = 0; idx < rwArray->GetItemsCount(); ++idx)
	//			DebugPrintRecurs(rwArray->GetItem(idx), idxInc++, level);
	//	}
	//	else
	//	{
	//		level++;
	//		printf("\n");
	//		for (uint32 idx = 0; idx < rwNode->GetNodesCount(); ++idx)
	//			DebugPrintRecurs(rwNode->GetNode(idx), INDEX_NONE, level);
	//	}
	//}
	static void DebugPrintRecurs2(const CRwNode* rwNode, uint32 arrayItemIdx = INDEX_NONE, uint32 level = 0)
	{
		auto strLevel = NiflectUtil::DebugIndentToString(level);
		NiflectUtil::Printf("%s", strLevel.c_str());
		if (arrayItemIdx == INDEX_NONE)
		{
			NiflectUtil::Printf("%s", rwNode->GetName().c_str());
		}
		else
		{
			ASSERT(rwNode->GetName().empty());
			NiflectUtil::Printf("[%u]", arrayItemIdx);
		}
		if (rwNode->IsValue())
		{
			if (arrayItemIdx == INDEX_NONE)
				NiflectUtil::Printf(", ");

			Niflect::CString str;
			auto rwValue = rwNode->GetValue();
			switch (rwValue->GetType())
			{
			case ERwValueType::Bool:
				str = rwValue->GetBool() ? "true" : "false";
				break;
			case ERwValueType::Float:
				str = std::to_string(rwValue->GetFloat()).c_str();
				break;
			case ERwValueType::Double:
				str = std::to_string(rwValue->GetDouble()).c_str();
				break;
			case ERwValueType::Int32:
				str = std::to_string(rwValue->GetInt32()).c_str();
				break;
			case ERwValueType::String:
				str = rwValue->GetString().c_str();
				break;
			default:
				ASSERT(false);
				break;
			}
			NiflectUtil::Printf("%s", str.c_str());
			NiflectUtil::Printf("\n");
		}
		else
		{
			level++;
			NiflectUtil::Printf("\n");
			for (uint32 idx = 0; idx < rwNode->GetNodesCount(); ++idx)
				DebugPrintRecurs2(rwNode->GetNode(idx), rwNode->IsArray() ? idx : INDEX_NONE, level);
		}
	}
	static void DebugPrintTestTree()
	{
		CRwNode root;
		//DebugBuildSingleValue(&root);
		//DebugBuildSingleArray(&root);
		DebugBuildStructure(&root);
		DebugPrintRecurs2(&root);
	}
}