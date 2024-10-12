#pragma once
#include "Niflect/NiflectBase.h"

namespace NiflectGen
{
	class CResolvedCursorNode;
	using CSharedResolvedCursorNode = Niflect::TSharedPtr<CResolvedCursorNode>;

	class CResolvedCursorNode
	{
	public:
		CResolvedCursorNode()
			: m_accessorBindingIndex(INDEX_NONE)
			, m_taggedTypeIndex(INDEX_NONE)
			, m_isTemplateFormat(false)
		{
		}
		void InitForAccessorBinding(uint32 foundIdx, const Niflect::CString& headerFilePath);
		void InitForTemplateBegin(const Niflect::CString& signature, uint32 foundIdx);
		void InitForTemplateArguments(const CResolvedCursorNode& childrenOwner);
		void InitForTemplateEnd();
		void InitForTemplate(const Niflect::CString& signature, uint32 foundIdx, const CResolvedCursorNode& childrenOwner);
		void InitForClassDecl(const Niflect::CString& signature, uint32 foundIdx, const Niflect::CString& headerFilePath);
		bool IsTemplateFormat() const
		{
			return m_isTemplateFormat;
		}
		bool IsValid() const
		{
			return m_accessorBindingIndex != INDEX_NONE || m_taggedTypeIndex != INDEX_NONE;
		}
		bool m_isTemplateFormat;
		uint32 m_accessorBindingIndex;
		uint32 m_taggedTypeIndex;//该索引对应的类型一定不是模板, 现可为 class, struct, enum
		Niflect::TArrayNif<CResolvedCursorNode> m_vecChild;
		Niflect::CString m_key;
		Niflect::CString m_resoCursorName;
		//要求与 m_vecChild 互斥, 即无法支持容器模板含成员变量, 而结构模板可含成员变量
		CSharedResolvedCursorNode m_elem;
		Niflect::TArrayNif<Niflect::CString> m_vecRequiredHeaderFilePath;
	};

	class CResolvedCursorRoots
	{
	public:
		CResolvedCursorRoots()
		{
		}
		CResolvedCursorRoots(const Niflect::CString& signatureStr, const CResolvedCursorNode& resoRoot)
			: m_resoRoot(resoRoot)
		{
		}
		Niflect::CString deprecated_m_signatureStr;
		CResolvedCursorNode m_resoRoot;
	};

	class CResolvedCursorRootsMapping
	{
	public:
		void SSSSSSSS();
		void DebugGenSignatures(Niflect::TArrayNif<Niflect::CString>& vecSignature);
		Niflect::TArrayNif<CResolvedCursorRoots> m_vecItem;
		Niflect::TMap<Niflect::CString, uint32> m_mapKeyToIndex;
	};
}