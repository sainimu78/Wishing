#pragma once
#include "Niflect/Base/NiflectBase.h"

//todo: 旧代码中有同名类, 为避免错误链接类加后缀2, 未来将删除旧代码并移除后缀2
namespace TreeReadWrite2
{
	//本系列类称为读写对象, 包括RwNode, RwArray, RwValue, 结构上以树型组织, 基本与json格式对应
	//本系列类的目的是封装树型结构读写对象, 如json, xml或是自定义的树型格式
	//使用读写对象接口而不直接使用如json这种库接口的理由是:
	//1. 读写对象可兼容典型树型结构, 与具体格式库无关
	//2. 使用读写对象作为接口参数可使接口通用性更强, 如可兼容多种格式读写
	//
	//通常地, 运行时序列化格式可用更精简的格式, 本计划实现一种自定义的二进制树型格式, 用于运行时序列化树型结构
	//但目前使用的json库支持紧凑格式, 可以更小的空间占用序列化
	//且已实现读写对象, 可用于定义序列化接口, 之后实现自定义树型格式也能够方便地兼容
	//
	//计划
	//1. 二进制格式, BinaryTreeReadWrite
	//2. 接入Stream, 实现如写文件不需要经过内存流, 直接写入文件流
	//3. 树型合并, 可用于复用配置, 如一些节点无配置, 从其它节点获取配置

	class CRawRwNode;
	class CRawRwArray;
	class CRawRwValue;
	
	//定义接口使用SharedPtr是为了方便子类对象释放
	typedef Niflect::TSharedPtr<CRawRwNode> CRwNode;
	typedef Niflect::TSharedPtr<CRawRwArray> CRwArray;
	typedef Niflect::TSharedPtr<CRawRwValue> CRwValue;
	
	class CRwDocument
	{
	public:
		CRwDocument(const CRwNode& rwRoot)
			: m_rwRoot(rwRoot)
		{
		}

	public:
		CRwNode& GetRootNode()
		{
			return m_rwRoot;
		}
		const CRwNode& GetRootNode() const
		{
			return m_rwRoot;
		}
		virtual CRwNode CreateNode() = 0;

	private:
		CRwNode m_rwRoot;
	};

	class CRwRawData
	{
	public:
		CRwRawData()
			: m_data(NULL)
			, m_size(0)
		{

		}

	public:
		const void* m_data;
		size_t m_size;
	};

	class CRawRwValue
	{
		typedef Niflect::CString CString;
	public:
		CRawRwValue(CRwDocument* rwDoc)
			: m_rwDoc(rwDoc)
		{
		}

	public:
		virtual bool GetBool(bool defaultValue = false) const = 0;
		virtual int32 GetInt32(int32 defaultValue = 0) const = 0;
		virtual uint32 GetUint32(uint32 defaultValue = 0u) const = 0;
		virtual float GetFloat(float defaultValue = 0.0f) const = 0;
		virtual double GetDouble(double defaultValue = 0.0) const = 0;
		virtual CString GetString(const CString& defaultValue = CString()) const = 0;
		virtual bool GetRawData(CRwRawData& rawData) const = 0;

	public:
		virtual void SetBool(bool value) = 0;
		virtual void SetInt32(int32 value) = 0;
		virtual void SetUint32(uint32 value) = 0;
		virtual void SetFloat(float value) = 0;
		virtual void SetDouble(double value) = 0;
		virtual void SetString(const CString& value) = 0;
		virtual void SetRawData(const void* data, size_t size) = 0;

	protected:
		CRwDocument* m_rwDoc;
	};

	class CNamedRwNode
	{
		typedef Niflect::CString CString;
	public:
		CString m_name;
		CRwNode m_node;
	};

	//返回的对象原始指针不为const是为了支持同时读写的操作, 如避免查找到的对象为const无法修改
	//另一方面考虑是, 作为基础读写对象, 类似于stream, 都是应该支持同时读写的
	class CRawRwNode
	{
		typedef Niflect::CString CString;
	public:
		CRawRwNode(CRwDocument* rwDoc)
			: m_rwDoc(rwDoc)
		{
		}

	public:
		virtual CRwNode FindNode(const CString& name) const = 0;
		virtual CRwNode& AddNode(const CString& name, const CRwNode& rwNode, uint32* insertedIndex) = 0;
		CRwNode CreateNode() const
		{
			return m_rwDoc->CreateNode();
		}
		CRwNode& CreateAndAddNode(const CString& name, uint32* insertedIndex)
		{
			auto rwNode = this->CreateNode();
			return this->AddNode(name, rwNode, insertedIndex);
		}
		CRwArray& AddArray(const CString& name, uint32* insertedIndex)
		{
			auto& rwNode = this->CreateAndAddNode(name, insertedIndex);
			return rwNode->ToArray();
		}
		CRwValue& AddValue(const CString& name, uint32* insertedIndex)
		{
			auto& rwNode = this->CreateAndAddNode(name, insertedIndex);
			return rwNode->ToValue();
		}
		//virtual void DeleteNode(uint32 index) = 0;
		//virtual CRwNode CreateNode() const = 0;
		//virtual void AddNodeWithName(const CString& name, const CRwNode& rwNode, uint32* insertedIndex) = 0;

	protected:
		virtual CNamedRwNode& GetNodeImpl(uint32 idx) const = 0;

	public:
		virtual uint32 GetNodesCount() const = 0;
		CNamedRwNode& GetNode(uint32 idx)
		{
			return this->GetNodeImpl(idx);
		}
		const CNamedRwNode& GetNode(uint32 idx) const
		{
			auto thisMutable = const_cast<CRawRwNode*>(this);
			return thisMutable->GetNodeImpl(idx);
		}

	protected:
		virtual CRwValue& ToValueImpl() = 0;
		virtual CRwArray& ToArrayImpl() = 0;

	public:
		CRwValue& ToValue()
		{
			return this->ToValueImpl();
		}
		const CRwValue& ToValue() const 
		{
			auto thisMutable = const_cast<CRawRwNode*>(this);
			return thisMutable->ToValueImpl();
		}
		CRwArray& ToArray()
		{
			return this->ToArrayImpl();
		}
		const CRwArray& ToArray() const
		{
			auto thisMutable = const_cast<CRawRwNode*>(this);
			return thisMutable->ToArrayImpl();
		}

	protected:
		CRwDocument* m_rwDoc;
	};

	class CRawRwArray
	{
		typedef Niflect::CString CString;
	public:
		CRawRwArray(CRwDocument* rwDoc)
			: m_rwDoc(rwDoc)
		{
		}

	public:
		virtual uint32 GetItemsCount() const = 0;

	protected:
		virtual CRwNode& GetItemNodeImpl(uint32 idx) = 0;

	public:
		CRwNode& GetItemNode(uint32 idx)
		{
			return this->GetItemNodeImpl(idx);
		}
		const CRwNode& GetItemNode(uint32 idx) const
		{
			auto thisMutable = const_cast<CRawRwArray*>(this);
			return thisMutable->GetItemNodeImpl(idx);
		}
		CRwValue& GetItemValue(uint32 idx)
		{
			auto rwNode = this->GetItemNode(idx);
			return rwNode->ToValue();
		}
		const CRwValue& GetItemValue(uint32 idx) const
		{
			auto rwNode = this->GetItemNode(idx);
			return rwNode->ToValue();
		}
		CRwArray& GetItemArray(uint32 idx)
		{
			auto rwNode = this->GetItemNode(idx);
			return rwNode->ToArray();
		}
		const CRwArray& GetItemArray(uint32 idx) const
		{
			auto rwNode = this->GetItemNode(idx);
			return rwNode->ToArray();
		}
		bool GetItemBool(uint32 idx) const
		{
			auto rwValue = this->GetItemValue(idx);
			return rwValue->GetBool();
		}
		int32 GetItemInt32(uint32 idx) const
		{
			auto rwValue = this->GetItemValue(idx);
			return rwValue->GetInt32();
		}
		float GetItemFloat(uint32 idx) const
		{
			auto rwValue = this->GetItemValue(idx);
			return rwValue->GetFloat();
		}
		CString GetItemString(uint32 idx) const
		{
			auto rwValue = this->GetItemValue(idx);
			return rwValue->GetString();
		}

	protected:
		virtual void AddItemNodeImpl(const CRwNode& rwItem) = 0;

	public:
		uint32 AddItem(const CRwNode& rwItem)
		{
			auto idx = this->GetItemsCount();
			this->AddItemNodeImpl(rwItem);
			return idx;
		}
		CRwNode& AddItemNode()
		{
			auto rwNode = m_rwDoc->CreateNode();
			return this->GetItemNode(this->AddItem(rwNode));
		}
		CRwValue& AddItemValue()
		{
			auto rwNode = m_rwDoc->CreateNode();
			return this->GetItemNode(this->AddItem(rwNode))->ToValue();
		}
		CRwArray& AddItemArray()
		{
			auto rwNode = m_rwDoc->CreateNode();
			return this->GetItemNode(this->AddItem(rwNode))->ToArray();
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

	protected:
		CRwDocument* m_rwDoc;
	};

	static CRwNode FindRwNode(const CRwNode& rwParent, const Niflect::CString& name)
	{
		if (rwParent != NULL)
			return rwParent->FindNode(name);
		return NULL;
	}
	static CRwArray FindRwArray(const CRwNode& rwParent, const Niflect::CString& name)
	{
		if (auto rwNode = FindRwNode(rwParent, name))
			return rwNode->ToArray();
		return NULL;
	}
	static CRwValue FindRwValue(const CRwNode& rwParent, const Niflect::CString& name)
	{
		if (auto rwNode = FindRwNode(rwParent, name))
			return rwNode->ToValue();
		return NULL;
	}
	static bool FindRwBool(const CRwNode& rwParent, const Niflect::CString& name, bool defaultValue = false)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetBool(defaultValue);
		return value;
	}
	static int32 FindRwInt32(const CRwNode& rwParent, const Niflect::CString& name, int32 defaultValue = 0)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetInt32(defaultValue);
		return value;
	}
	static uint32 FindRwUint32(const CRwNode& rwParent, const Niflect::CString& name, uint32 defaultValue = 0u)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetUint32(defaultValue);
		return value;
	}
	static float FindRwFloat(const CRwNode& rwParent, const Niflect::CString& name, float defaultValue = 0.0f)
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetFloat(defaultValue);
		return value;
	}
	static Niflect::CString FindRwString(const CRwNode& rwParent, const Niflect::CString& name, const Niflect::CString& defaultValue = Niflect::CString())
	{
		auto value = defaultValue;
		if (auto rwValue = FindRwValue(rwParent, name))
			value = rwValue->GetString(defaultValue);
		return value;
	}
	static CRwRawData FindRwRawData(const CRwNode& rwParent, const Niflect::CString& name)
	{
		CRwRawData rawData;
		if (auto rwValue = FindRwValue(rwParent, name))
			rwValue->GetRawData(rawData);
		return rawData;
	}
	static uint32 GetRwNodesCount(const CRwNode& rwParent)
	{
		uint32 count = 0;
		if (rwParent != NULL)
			count = rwParent->GetNodesCount();
		return count;
	}
	static CNamedRwNode GetRwNode(const CRwNode& rwParent, uint32 idx)
	{
		CNamedRwNode result;
		if (rwParent != NULL)
			result = rwParent->GetNode(idx);
		return result;
	}
	static CRwArray ToRwArray(const CRwNode& rwNode)
	{
		if (rwNode != NULL)
			return rwNode->ToArray();
		return NULL;
	}
	static CRwValue ToRwValue(const CRwNode& rwNode)
	{
		if (rwNode != NULL)
			return rwNode->ToValue();
		return NULL;
	}
	static uint32 GetRwItemsCount(const CRwArray& rwArray)
	{
		uint32 count = 0;
		if (rwArray != NULL)
			count = rwArray->GetItemsCount();
		return count;
	}

	static CRwNode AddRwNode(CRwNode& rwParent, const Niflect::CString& name, uint32* insertedIndex = NULL)
	{
		if(rwParent != NULL)
			return rwParent->CreateAndAddNode(name, insertedIndex);
		return NULL;
	}
	static CRwNode AddExistingRwNode(CRwNode& rwParent, const Niflect::CString& name, const CRwNode& rwNode, uint32* insertedIndex = NULL)
	{
		if(rwParent != NULL)
			return rwParent->AddNode(name, rwNode, insertedIndex);
		return NULL;
	}
	//static void DeleteRwNode(CRwNode& rwParent, uint32 index)
	//{
	//	if(rwParent != NULL)
	//		rwParent->DeleteNode(index);
	//}
	//static CRwNode CreateRwNode(const CRwNode& rwParent)
	//{
	//	if (rwParent != NULL)
	//		return rwParent->CreateNode();
	//	return NULL;
	//}
	////与更便利的AddRwNode相比, CreateRwNode与AddRwNodeWithName结合使用可避免创建冗余节点
	//static void AddRwNodeWithName(CRwNode& rwParent, const CString& name, const CRwNode& rwNode, uint32* insertedIndex = NULL)
	//{
	//	if(rwParent != NULL)
	//		rwParent->AddNodeWithName(name, rwNode, insertedIndex);
	//}
	static CRwArray AddRwArray(CRwNode& rwParent, const Niflect::CString& name, uint32* insertedIndex = NULL)
	{
		if (rwParent != NULL)
			return rwParent->AddArray(name, insertedIndex);
		return NULL;
	}
	static CRwValue AddRwValue(CRwNode& rwParent, const Niflect::CString& name, uint32* insertedIndex = NULL)
	{
		if (rwParent != NULL)
			return rwParent->AddValue(name, insertedIndex);
		return NULL;
	}
	static void AddRwBool(CRwNode& rwParent, const Niflect::CString& name, bool value)
	{
		if(auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetBool(value);
	}
	static void AddRwInt32(CRwNode& rwParent, const Niflect::CString& name, int32 value)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetInt32(value);
	}
	static void AddRwUint32(CRwNode& rwParent, const Niflect::CString& name, uint32 value)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetUint32(value);
	}
	static void AddRwFloat(CRwNode& rwParent, const Niflect::CString& name, float value)
	{
		if(auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetFloat(value);
	}
	static void AddRwDouble(CRwNode& rwParent, const Niflect::CString& name, double value)
	{
		if(auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetDouble(value);
	}
	static void AddRwString(CRwNode& rwParent, const Niflect::CString& name, const Niflect::CString& value)
	{
		if(auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetString(value);
	}
	static void AddRwRawData(CRwNode& rwParent, const Niflect::CString& name, const void* data, const size_t size)
	{
		if (auto rwValue = AddRwValue(rwParent, name))
			rwValue->SetRawData(data, size);
	}

	namespace ValueReadWrite
	{
		static bool Load(const CRwValue& rwValue, float& value)
		{
			if (rwValue != NULL)
			{
				value = rwValue->GetFloat();
				return true;
			}
			return false;
		}
		static bool Save(CRwValue& rwValue, const float& value)
		{
			if (rwValue != NULL)
			{
				rwValue->SetFloat(value);
				return true;
			}
			return false;
		}
		static bool Load(const CRwValue& rwValue, double& value)
		{
			if (rwValue != NULL)
			{
				value = rwValue->GetDouble();
				return true;
			}
			return false;
		}
		static bool Save(CRwValue& rwValue, const double& value)
		{
			if (rwValue != NULL)
			{
				rwValue->SetDouble(value);
				return true;
			}
			return false;
		}
		static bool Load(const CRwValue& rwValue, Niflect::CString& value)
		{
			if (rwValue != NULL)
			{
				value = rwValue->GetString();
				return true;
			}
			return false;
		}
		static bool Save(CRwValue& rwValue, const Niflect::CString& value)
		{
			if (rwValue != NULL)
			{
				rwValue->SetString(value);
				return true;
			}
			return false;
		}
		static bool Load(const CRwValue& rwValue, bool& value)
		{
			if (rwValue != NULL)
			{
				value = rwValue->GetBool();
				return true;
			}
			return false;
		}
		static bool Save(CRwValue& rwValue, const bool& value)
		{
			if (rwValue != NULL)
			{
				rwValue->SetBool(value);
				return true;
			}
			return false;
		}
	}
}

#include "Niflect/Util/DebugUtil.h"

namespace aaaaaaa
{
	enum class ERwValueType
	{
		None,
		Bool,
		Int32,
		Float,
		Double,
		String,
	};

	class CInternalRwNode;
	using CRwNode2 = Niflect::TSharedPtr<CInternalRwNode>;
	using CInternalRwBuffer = Niflect::TArrayNif<uint8>;

	class CInternalRwValue
	{
	public:
		CInternalRwValue(CInternalRwBuffer& data, ERwValueType& type)
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
			memcpy(m_data.data(), &val, cnt);
		}
		bool GetBool() const
		{
			ASSERT(m_type == ERwValueType::Bool);
			return *reinterpret_cast<bool*>(m_data.data());
		}
		void SetFloat(float val)
		{
			m_type = ERwValueType::Float;
			auto cnt = sizeof(val);
			m_data.resize(cnt);
			memcpy(m_data.data(), &val, cnt);
		}
		float GetFloat() const
		{
			ASSERT(m_type == ERwValueType::Float);
			return *reinterpret_cast<float*>(m_data.data());
		}
		void SetString(const Niflect::CString& val)
		{
			m_type = ERwValueType::String;
			auto cnt = val.length();
			m_data.resize(cnt);
			memcpy(m_data.data(), val.data(), cnt);
		}
		Niflect::CString GetString() const
		{
			ASSERT(m_type == ERwValueType::String);
			Niflect::CString val;
			auto cnt = m_data.size();
			val.resize(cnt);
			memcpy(&val[0], m_data.data(), cnt);
			return val;
		}

	private:
		CInternalRwBuffer& m_data;
		ERwValueType& m_type;
	};
	using CRwValue2 = Niflect::TSharedPtr<CInternalRwValue>;

	class CInternalRwArray
	{
	public:
		CInternalRwArray(CInternalRwBuffer& data, Niflect::TArrayNif<CRwNode2>& vecItem)
			: m_data(data)
			, m_vecItem(vecItem)
		{
		}
		void AddItem(const CRwNode2& item)
		{
			m_vecItem.push_back(item);
		}
		const Niflect::TArrayNif<CRwNode2>& GetItems() const
		{
			return m_vecItem;
		}

	private:
		CInternalRwBuffer& m_data;
		Niflect::TArrayNif<CRwNode2>& m_vecItem;
	};
	using CRwArray2 = Niflect::TSharedPtr<CInternalRwArray>;

	class CInternalRwNode
	{
	public:
		CInternalRwNode()
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
		void AddChild(const CRwNode2& node)
		{
			m_vecChild.push_back(node);
		}
		const Niflect::TArrayNif<CRwNode2>& GetChildren() const
		{
			return m_vecChild;
		}
		const CRwValue2& ToValue()
		{
			if (m_rwValue == NULL)
			{
				ASSERT(m_rwArray == NULL);
				m_rwArray = NULL;
				m_rwValue = Niflect::MakeShared<CInternalRwValue>(m_data, m_valueType);
			}
			return m_rwValue;
		}
		const CRwArray2& ToArray()
		{
			if (m_rwArray == NULL)
			{
				ASSERT(m_rwValue == NULL);
				m_rwValue = NULL;
				m_rwArray = Niflect::MakeShared<CInternalRwArray>(m_data, m_vecChild);
			}
			return m_rwArray;
		}

	private:
		Niflect::CString m_name;
		ERwValueType m_valueType;
		Niflect::TArrayNif<CRwNode2> m_vecChild;
		CInternalRwBuffer m_data;
		CRwValue2 m_rwValue;
		CRwArray2 m_rwArray;
	};

	static Niflect::CString DebugValueToString(const CRwValue2& rwValue)
	{
		Niflect::CString str;
		switch (rwValue->GetType())
		{
		case ERwValueType::Bool:
			str = rwValue->GetBool() ? "true" : "false";
			break;
		case ERwValueType::Float:
		{
			str = std::to_string(rwValue->GetFloat()).c_str();
			break;
		}
		case ERwValueType::String:
			str = rwValue->GetString().c_str();
			break;
		default:
			ASSERT(false);
			break;
		}
		return str;
	}
	static void DebugPrint(const CRwNode2& rwNode, uint32 arrayItemIdx = INDEX_NONE, uint32 level = 0)
	{
		auto strLevel = NiflectUtil::DebugIndentToString(level);
		printf("%s", strLevel.c_str());
		if (arrayItemIdx == INDEX_NONE)
		{
			printf("%s", rwNode->GetName().c_str());
		}
		else
		{
			ASSERT(rwNode->GetName().empty());
			printf("[%u]", arrayItemIdx);
		}
		if (rwNode->IsValue())
		{
			if (arrayItemIdx == INDEX_NONE)
				printf(", ");
			printf("%s", DebugValueToString(rwNode->ToValue()).c_str());
			printf("\n");
		}
		else if (rwNode->IsArray())
		{
			level++;
			printf("\n");
			auto& rwArray = rwNode->ToArray();
			uint32 idx = 0;
			for (auto& it : rwArray->GetItems())
				DebugPrint(it, idx++, level);
		}
		else
		{
			level++;
			printf("\n");
			for (auto& it : rwNode->GetChildren())
				DebugPrint(it, INDEX_NONE, level);
		}
	}
}