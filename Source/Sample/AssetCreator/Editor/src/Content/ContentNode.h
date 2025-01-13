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
		virtual bool _DebugFuncForDynamicCast() const { return true; }//��Ϊ��̬������ͱ������, ���Ѷ���ǵ����õ�virtual��������Ƴ�, ��ע: error C2683: 'dynamic_cast': 'XXX' is not a polymorphic type 

	private:
		Niflect::CString m_name;
		CContentNode* m_parentNode;
		CUuid m_globalId;
	};
	using CSharedContentNode = Niflect::TSharedPtr<CContentNode>;
}