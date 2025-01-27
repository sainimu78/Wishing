#pragma once
#include "Niflect/NiflectBase.h"
#include "Base/UuidGen.h"
#include "Niflect/Util/DebugUtil.h"

namespace Wishing
{
	class CContentNode
	{
	public:
		CContentNode();

	public:
		void Init(const Niflect::CString& name, uint32 tableIdx);
		void InitGlobalId(const CUuid& globalId);

	public:
		const Niflect::CString& GetName() const { return m_name; }
		const uint32& GetTableIndex() const { return m_tableIdx; }
	//	void SetName(const Niflect::CString& name);
	//	CContentNode* GetParentNode() const;
	//	void SetParentNode(CContentNode* parentNode);

	public:
		void AddNode(CContentNode* node);
		void DeleteNode(CContentNode* node);
		CContentNode* FindNode(const Niflect::CString& name) const;

	public:
		void DebugPrint(int depth = 0) const
		{
			auto strLv = NiflectUtil::DebugIndentToString(depth);
			printf("%s%s\n", strLv.c_str(), this->GetName().c_str());
			depth++;
			for (auto& it : m_vecNode)
				it->DebugPrint(depth);
		}

	private:
		virtual bool _DebugFuncForDynamicCast() const { return true; }//仅为动态检查类型避免错误, 如已定义非调试用的virtual函数则可移除, 备注: error C2683: 'dynamic_cast': 'XXX' is not a polymorphic type 

	private:
		Niflect::CString m_name;
		CContentNode* m_parentNode;
		CUuid m_globalId;
		uint32 m_tableIdx;
		Niflect::TArray<CContentNode*> m_vecNode;
	};
	using CSharedContentNode = Niflect::TSharedPtr<CContentNode>;
}