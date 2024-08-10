#pragma once
#include "Niflect/NiflectBase.h"
#include "Niflect/Util/DebugUtil.h"

namespace RwTree
{
	enum class ERwValueType : uint8
	{
		None,
		Bool,
		Int8,
		Int16,
		Int32,
		Int64,
		Uint8,
		Uint16,
		Uint32,
		Uint64,
		Float,
		Double,
		String,
		RawData,
	};

	typedef Niflect::CString CRwRawData;//用字符串是为顺便避免String类型的转换

	class CRwValue
	{
	public:
		CRwValue(CRwRawData& data, ERwValueType& type)
			: m_data(data)
			, m_type(type)
		{
		}
		const ERwValueType& GetType() const
		{
			return m_type;
		}

	public:
		void SetBool(const bool& val)
		{
			this->SetBuiltInValue<ERwValueType::Bool>(val);
		}
		const bool& GetBool() const
		{
			return this->GetBuiltInValue<ERwValueType::Bool, bool>();
		}
		void SetInt8(const int8& val)
		{
			this->SetBuiltInValue<ERwValueType::Int8>(val);
		}
		const int8& GetInt8() const
		{
			return this->GetBuiltInValue<ERwValueType::Int8, int8>();
		}
		void SetInt16(const int16& val)
		{
			this->SetBuiltInValue<ERwValueType::Int16>(val);
		}
		const int16& GetInt16() const
		{
			return this->GetBuiltInValue<ERwValueType::Int16, int16>();
		}
		void SetInt32(const int32& val)
		{
			this->SetBuiltInValue<ERwValueType::Int32>(val);
		}
		const int32& GetInt32() const
		{
			return this->GetBuiltInValue<ERwValueType::Int32, int32>();
		}
		void SetInt64(const int64& val)
		{
			this->SetBuiltInValue<ERwValueType::Int64>(val);
		}
		const int64& GetInt64() const
		{
			return this->GetBuiltInValue<ERwValueType::Int64, int64>();
		}
		void SetUint8(const uint8& val)
		{
			this->SetBuiltInValue<ERwValueType::Uint8>(val);
		}
		const uint8& GetUint8() const
		{
			return this->GetBuiltInValue<ERwValueType::Uint8, uint8>();
		}
		void SetUint16(const uint16& val)
		{
			this->SetBuiltInValue<ERwValueType::Uint16>(val);
		}
		const uint16& GetUint16() const
		{
			return this->GetBuiltInValue<ERwValueType::Uint16, uint16>();
		}
		void SetUint32(const uint32& val)
		{
			this->SetBuiltInValue<ERwValueType::Uint32>(val);
		}
		const uint32& GetUint32() const
		{
			return this->GetBuiltInValue<ERwValueType::Uint32, uint32>();
		}
		void SetUint64(const uint64& val)
		{
			this->SetBuiltInValue<ERwValueType::Uint64>(val);
		}
		const uint64& GetUint64() const
		{
			return this->GetBuiltInValue<ERwValueType::Uint64, uint64>();
		}
		void SetFloat(const float& val)
		{
			this->SetBuiltInValue<ERwValueType::Float>(val);
		}
		const float& GetFloat() const
		{
			return this->GetBuiltInValue<ERwValueType::Float, float>();
		}
		void SetDouble(const double& val)
		{
			this->SetBuiltInValue<ERwValueType::Double>(val);
		}
		const double& GetDouble() const
		{
			return this->GetBuiltInValue<ERwValueType::Double, double>();
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

	public:
		void SetRawData(const CRwRawData& val)
		{
			m_type = ERwValueType::RawData;
			m_data = val;
		}
		void SetRawData(const void* src, uint32 size)
		{
			m_type = ERwValueType::RawData;
			m_data.resize(size);
			memcpy(&m_data[0], src, size);
		}
		const CRwRawData& GetRawData() const
		{
			ASSERT(m_type == ERwValueType::RawData);
			return m_data;
		}

	private:
		template <ERwValueType TEnumType, typename TValue>
		inline void SetBuiltInValue(const TValue& val)
		{
			m_type = TEnumType;
			auto cnt = sizeof(val);
			m_data.resize(cnt);
			memcpy(&m_data[0], &val, cnt);
		}
		template <ERwValueType TEnumType, typename TValue>
		inline const TValue& GetBuiltInValue() const
		{
			ASSERT(m_type == TEnumType);
			return *reinterpret_cast<TValue*>(&m_data[0]);
		}

	private:
		CRwRawData& m_data;
		ERwValueType& m_type;
	};
	using CSharedRwValue = Niflect::TSharedPtr<CRwValue>;

	class CRwNode;
	using CSharedRwNode = Niflect::TSharedPtr<CRwNode>;

	class CRwArray
	{
	public:
		CRwArray(CRwRawData& data, Niflect::TArrayNif<CSharedRwNode>& vecItem)
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
		void AddItemString(const Niflect::CString& value)
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
		CRwRawData& m_data;
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
		const CRwRawData& GetData() const
		{
			return m_data;
		}

	private:
		Niflect::CString m_name;
		ERwValueType m_valueType;
		Niflect::TArrayNif<CSharedRwNode> m_vecNode;
		CRwRawData m_data;
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
}

namespace RwTree
{
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
	template <typename TValue>
	static TValue GetRwTypedValue(const CRwValue* rwValue, TValue defaultValue = TValue())
	{
		ASSERT(false);
	}

#define SPECIALIZATION_IMPL_GetRwTypedValue(specType, getterFuncName)\
	template <>\
	inline specType GetRwTypedValue(const CRwValue* rwValue, specType defaultValue)\
	{\
		if (rwValue != NULL)\
			return rwValue->getterFuncName();\
		return defaultValue;\
	}

	SPECIALIZATION_IMPL_GetRwTypedValue(bool, GetBool)
	SPECIALIZATION_IMPL_GetRwTypedValue(int8, GetInt8)
	SPECIALIZATION_IMPL_GetRwTypedValue(int16, GetInt16)
	SPECIALIZATION_IMPL_GetRwTypedValue(int32, GetInt32)
	SPECIALIZATION_IMPL_GetRwTypedValue(int64, GetInt64)
	SPECIALIZATION_IMPL_GetRwTypedValue(uint8, GetUint8)
	SPECIALIZATION_IMPL_GetRwTypedValue(uint16, GetUint16)
	SPECIALIZATION_IMPL_GetRwTypedValue(uint32, GetUint32)
	SPECIALIZATION_IMPL_GetRwTypedValue(uint64, GetUint64)
	SPECIALIZATION_IMPL_GetRwTypedValue(float, GetFloat)
	SPECIALIZATION_IMPL_GetRwTypedValue(double, GetDouble)
	SPECIALIZATION_IMPL_GetRwTypedValue(Niflect::CString, GetString)

	template <typename TValue>
	static void SetRwTypedValue(CRwValue* rwValue, TValue value)
	{
		ASSERT(false);
	}

#define SPECIALIZATION_IMPL_SetRwTypedValue(specType, setterFuncName)\
	template <>\
	inline void SetRwTypedValue(CRwValue* rwValue, specType value)\
	{\
		if (rwValue != NULL)\
			rwValue->setterFuncName(value);\
	}

	SPECIALIZATION_IMPL_SetRwTypedValue(bool, SetBool)
	SPECIALIZATION_IMPL_SetRwTypedValue(int8, SetInt8)
	SPECIALIZATION_IMPL_SetRwTypedValue(int16, SetInt16)
	SPECIALIZATION_IMPL_SetRwTypedValue(int32, SetInt32)
	SPECIALIZATION_IMPL_SetRwTypedValue(int64, SetInt64)
	SPECIALIZATION_IMPL_SetRwTypedValue(uint8, SetUint8)
	SPECIALIZATION_IMPL_SetRwTypedValue(uint16, SetUint16)
	SPECIALIZATION_IMPL_SetRwTypedValue(uint32, SetUint32)
	SPECIALIZATION_IMPL_SetRwTypedValue(uint64, SetUint64)
	SPECIALIZATION_IMPL_SetRwTypedValue(float, SetFloat)
	SPECIALIZATION_IMPL_SetRwTypedValue(double, SetDouble)
	SPECIALIZATION_IMPL_SetRwTypedValue(Niflect::CString, SetString)

	static bool FindRwBool(const CRwNode* rwParent, const Niflect::CString& name, bool defaultValue = false)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetBool();
		return value;
	}
	static int8 FindRwInt8(const CRwNode* rwParent, const Niflect::CString& name, int8 defaultValue = 0)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetInt8();
		return value;
	}
	static int16 FindRwInt16(const CRwNode* rwParent, const Niflect::CString& name, int16 defaultValue = 0)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetInt16();
		return value;
	}
	static int32 FindRwInt32(const CRwNode* rwParent, const Niflect::CString& name, int32 defaultValue = 0)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetInt32();
		return value;
	}
	static int64 FindRwInt64(const CRwNode* rwParent, const Niflect::CString& name, int64 defaultValue = 0)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetInt64();
		return value;
	}
	static uint8 FindRwUint8(const CRwNode* rwParent, const Niflect::CString& name, uint8 defaultValue = 0u)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetUint8();
		return value;
	}
	static uint16 FindRwUint16(const CRwNode* rwParent, const Niflect::CString& name, uint16 defaultValue = 0u)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetUint16();
		return value;
	}
	static uint32 FindRwUint32(const CRwNode* rwParent, const Niflect::CString& name, uint32 defaultValue = 0u)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetUint32();
		return value;
	}
	static uint64 FindRwUint64(const CRwNode* rwParent, const Niflect::CString& name, uint64 defaultValue = 0u)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetUint64();
		return value;
	}
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
	static CRwRawData FindRwRawData(const CRwNode* rwParent, const Niflect::CString& name)
	{
		if (auto rwValue = FindRwValue(rwParent, name))
			return rwValue->GetRawData();
		return CRwRawData();
	}
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
	static void AddRwInt8(CRwNode* rwParent, const Niflect::CString& name, int8 value)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetInt8(value);
	}
	static void AddRwInt16(CRwNode* rwParent, const Niflect::CString& name, int16 value)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetInt16(value);
	}
	static void AddRwInt32(CRwNode* rwParent, const Niflect::CString& name, int32 value)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetInt32(value);
	}
	static void AddRwInt64(CRwNode* rwParent, const Niflect::CString& name, int64 value)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetInt64(value);
	}
	static void AddRwUint8(CRwNode* rwParent, const Niflect::CString& name, uint8 value)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetUint8(value);
	}
	static void AddRwUint16(CRwNode* rwParent, const Niflect::CString& name, uint16 value)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetUint16(value);
	}
	static void AddRwUint32(CRwNode* rwParent, const Niflect::CString& name, uint32 value)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetUint32(value);
	}
	static void AddRwUint64(CRwNode* rwParent, const Niflect::CString& name, uint64 value)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetUint64(value);
	}
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
	static void AddRwRawData(CRwNode* rwParent, const Niflect::CString& name, const void* data, uint32 size)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetRawData(data, size);
	}
}

namespace RwTree
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
			case ERwValueType::Int8:
				str = std::to_string(rwValue->GetInt8()).c_str();
				break;
			case ERwValueType::Int16:
				str = std::to_string(rwValue->GetInt16()).c_str();
				break;
			case ERwValueType::Int32:
				str = std::to_string(rwValue->GetInt32()).c_str();
				break;
			case ERwValueType::Int64:
				str = std::to_string(rwValue->GetInt64()).c_str();
				break;
			case ERwValueType::Uint8:
				str = std::to_string(rwValue->GetUint8()).c_str();
				break;
			case ERwValueType::Uint16:
				str = std::to_string(rwValue->GetUint16()).c_str();
				break;
			case ERwValueType::Uint32:
				str = std::to_string(rwValue->GetUint32()).c_str();
				break;
			case ERwValueType::Uint64:
				str = std::to_string(rwValue->GetUint64()).c_str();
				break;
			case ERwValueType::Float:
				str = std::to_string(rwValue->GetFloat()).c_str();
				break;
			case ERwValueType::Double:
				str = std::to_string(rwValue->GetDouble()).c_str();
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