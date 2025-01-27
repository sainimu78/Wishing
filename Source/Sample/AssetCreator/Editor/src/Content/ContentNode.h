#pragma once
#include "Niflect/NiflectBase.h"
#include "Base/UuidGen.h"

namespace Wishing
{
	class CContentDirNode;

	class CContentNode
	{
	public:
		CContentNode();

	public:
		void Init(const Niflect::CString& name, CContentDirNode* parentNode, uint32 tableIdx);
		void InitGlobalId(const CUuid& globalId);

	public:
		const Niflect::CString& GetName() const { return m_name; }
		const uint32& GetTableIndex() const { return m_tableIdx; }

	private:
		virtual void _SupportCastChecking() const {}

	private:
		Niflect::CString m_name;
		CContentDirNode* m_parentNode;
		CUuid m_globalId;
		uint32 m_tableIdx;
	};
	using CSharedContentNode = Niflect::TSharedPtr<CContentNode>;
}