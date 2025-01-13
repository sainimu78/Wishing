#pragma once
#include "Niflect/NiflectBase.h"
#include "Base/UuidGen.h"

namespace Wishing
{
	class CContentNode
	{
	public:
		CContentNode();

	public:
		void Init(const CUuid& globalId);

	//public:
	//	const Niflect::CString& GetName() const;
	//	void SetName(const Niflect::CString& name);
	//	CContentNode* GetParentNode() const;
	//	void SetParentNode(CContentNode* parentNode);

	private:
		virtual bool _DebugFuncForDynamicCast() const { return true; }//仅为动态检查类型避免错误, 如已定义非调试用的virtual函数则可移除, 备注: error C2683: 'dynamic_cast': 'XXX' is not a polymorphic type 

	private:
		Niflect::CString m_name;
		CContentNode* m_parentNode;
		CUuid m_globalId;
	};
	using CSharedContentNode = Niflect::TSharedPtr<CContentNode>;
}