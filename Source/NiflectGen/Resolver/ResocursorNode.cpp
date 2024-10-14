#include "NiflectGen/Resolver/ResocursorNode.h"
#include "Niflect/Util/DebugUtil.h"
#include "Niflect/Util/StringUtil.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"

namespace NiflectGen
{
	void CResolvedCursorNode::InitForAccessorBinding(uint32 foundIdx, const Niflect::CString& headerFilePath)
	{
		ASSERT(m_accessorBindingIndex == INDEX_NONE);
		m_accessorBindingIndex = foundIdx;
		if (!headerFilePath.empty())
		{
			ASSERT(m_vecRequiredHeaderFilePath.size() == 0);
			m_vecRequiredHeaderFilePath.push_back(headerFilePath);
		}
	}
	void CResolvedCursorNode::InitForTemplateBegin(const Niflect::CString& signature, uint32 foundIdx)
	{
		ASSERT(m_key.empty());
		m_key += '(';
		m_key += std::to_string(foundIdx).c_str();

		ASSERT(m_resocursorName.empty());
		m_resocursorName = signature;
	}
	//static void SADSAF(Niflect::TArrayNif<const CBindingAccessorIndexedNode*>& vec, Niflect::CString& str)
	//{
	//	if (vec.size() == 0)
	//	{
	//		return;
	//	}
	//	else
	//	{
	//		str += vec.back()->m_signature;
	//		vec.pop_back();
	//	}
	//	SADSAF(vec, str);
	//	str += '>';
	//}
	void CResolvedCursorNode::InitForTemplateArguments(const CResolvedCursorNode& childrenOwner, bool isTemplateFormat)
	{
		if (auto elem = childrenOwner.m_elem.Get())
		{
			m_key += elem->m_key;
			ASSERT(childrenOwner.m_vecChild.size() == 0);
		}
		else
		{
			for (auto& it : childrenOwner.m_vecChild)
				m_key += it.m_key;
		}
		if (isTemplateFormat)
		{
			NiflectGenDefinition::CodeStyle::TemplateAngleBracketL(m_resocursorName);
			if (auto elem = childrenOwner.m_elem.Get())
			{
				ASSERT(childrenOwner.m_vecChild.size() == 0);
				m_resocursorName += elem->m_resocursorName;
			}
			else
			{
				for (uint32 idx = 0; idx < childrenOwner.m_vecChild.size(); ++idx)
				{
					m_resocursorName += childrenOwner.m_vecChild[idx].m_resocursorName;
					if (idx != childrenOwner.m_vecChild.size() - 1)
						m_resocursorName += ", ";
				}
			}
			NiflectGenDefinition::CodeStyle::TemplateAngleBracketR(m_resocursorName);
		}
		if (auto elem = childrenOwner.m_elem.Get())
		{
			for (auto& it : elem->m_vecRequiredHeaderFilePath)
				m_vecRequiredHeaderFilePath.push_back(it);
		}
		else
		{
			for (auto& it0 : childrenOwner.m_vecChild)
			{
				for (auto& it1 : it0.m_vecRequiredHeaderFilePath)
					m_vecRequiredHeaderFilePath.push_back(it1);
			}
		}
	}
	void CResolvedCursorNode::InitForTemplateEnd()
	{
		m_key += ')';
	}
	void CResolvedCursorNode::InitForTemplate(const Niflect::CString& signature, uint32 foundIdx, const CResolvedCursorNode& childrenOwner, bool isTemplateFormat)
	{
		this->InitForTemplateBegin(signature, foundIdx);
		this->InitForTemplateArguments(childrenOwner, isTemplateFormat);
		this->InitForTemplateEnd();
	}
	void CResolvedCursorNode::InitForClassDecl(const Niflect::CString& signature, uint32 taggedTypeIdx, uint32 accessorBindingIdx, const Niflect::CString& headerFilePath)
	{
		ASSERT(m_key.empty());
		m_key += '[';
		m_key += std::to_string(taggedTypeIdx).c_str();
		m_key += ']';
		m_taggedTypeIndex = taggedTypeIdx;

		m_accessorBindingIndex = accessorBindingIdx;

		ASSERT(m_resocursorName.empty());
		m_resocursorName = signature;

		ASSERT(m_vecRequiredHeaderFilePath.size() == 0);
		m_vecRequiredHeaderFilePath.push_back(headerFilePath);
	}

	static void DebugGenSignature2222(const CResolvedCursorNode& indexedParent, uint32 lv, const char* pszLv, Niflect::TArrayNif<Niflect::CString>& vecSignature)
	{
		auto strLv = NiflectUtil::DebugIndentToString(lv, pszLv);
		auto result = NiflectUtil::FormatString("%s%s", strLv.c_str(), indexedParent.m_resocursorName.c_str());
		vecSignature.push_back(result);
	}
	static void DebugGenSignature(const CResolvedCursorNode& indexedParent, Niflect::TArrayNif<Niflect::CString>& vecSignature)
	{
		uint32 lv = 0;
		const char* pszLv = "-";
		DebugGenSignature2222(indexedParent, lv, pszLv, vecSignature);

		lv++;
		auto& childrenOwner = indexedParent;
		if (auto elem = indexedParent.m_elem.Get())
		{
			ASSERT(childrenOwner.m_vecChild.size() == 0);
			DebugGenSignature2222(*elem, lv, "+", vecSignature);
		}
		else
		{
			for (auto& it : childrenOwner.m_vecChild)
				DebugGenSignature2222(it, lv, pszLv, vecSignature);
		}
	}

	void CResolvedCursorRootsMapping::DebugGenSignatures(Niflect::TArrayNif<Niflect::CString>& vecSignature)
	{
		for (auto& it : m_vecItem)
			DebugGenSignature(it.m_resoRoot, vecSignature);
	}

	static void DebugPrintSSSSSSSSSSSSSSSSSSAAAAAAAAA(const CResolvedCursorNode& indexedParent, uint32 lv, const char* pszLv)
	{
		auto strLv = NiflectUtil::DebugIndentToString(lv, pszLv);
		printf("%s%s\n", strLv.c_str(), indexedParent.m_resocursorName.c_str());
	}
	static void DebugPrintRecursOk(const CResolvedCursorNode& indexedParent)
	{
		uint32 lv = 0;
		const char* pszLv = "-";
		DebugPrintSSSSSSSSSSSSSSSSSSAAAAAAAAA(indexedParent, lv, pszLv);

		lv++;
		auto& childrenOwner = indexedParent;
		if (auto elem = indexedParent.m_elem.Get())
		{
			ASSERT(childrenOwner.m_vecChild.size() == 0);
			DebugPrintSSSSSSSSSSSSSSSSSSAAAAAAAAA(*elem, lv, "+");
		}
		else
		{
			for (auto& it : childrenOwner.m_vecChild)
				DebugPrintSSSSSSSSSSSSSSSSSSAAAAAAAAA(it, lv, pszLv);
		}
	}
	static void DebugPrint(const CResolvedCursorNode& indexedParent)
	{
		DebugPrintRecursOk(indexedParent);
	}

	void CResolvedCursorRootsMapping::SSSSSSSS()
	{
		for (auto& it : m_vecItem)
		{
			Niflect::CString s = "#";
			//表明可以此区分是否需要在生成阶段遍历member以生成代码或其它处理
			if (it.m_resoRoot.m_taggedTypeIndex != INDEX_NONE)
				s = " Tagged Type ";
			printf("#######%s##########\n", s.c_str());
			DebugPrint(it.m_resoRoot);
		}
	}
}