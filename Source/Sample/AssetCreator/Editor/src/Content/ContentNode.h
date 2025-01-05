#pragma once
#include "Niflect/NiflectBase.h"

namespace Wishing
{
	class CContentNode
	{
	public:
		CContentNode();

	public:
		void Init(const Niflect::CString& name, CContentNode* parentNode);
		void SetName(const Niflect::CString& name);
		void SetParentNode(CContentNode* parentNode);

	public:
		const Niflect::CString& GetName() const;
		CContentNode* GetParentNode() const;

	private:
		virtual bool _DebugFuncForDynamicCast() const { return true; }//��Ϊ��̬������ͱ������, ���Ѷ���ǵ����õ�virtual��������Ƴ�, ��ע: error C2683: 'dynamic_cast': 'XXX' is not a polymorphic type 

	private:
		Niflect::CString m_name;
		CContentNode* m_parentNode;
	};
	using CSharedContentNode = Niflect::TSharedPtr<CContentNode>;
}