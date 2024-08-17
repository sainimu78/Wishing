#include "NiflectGen/TaggedType/TaggedClass.h"
#include "NiflectGen/Util/CursorUtil.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "NiflectGen/Log/Log.h"

namespace NiflectGen
{
	using namespace Niflect;

	CTaggedClass::CTaggedClass()
		: m_stage(EStage::None)
		, m_tagLocation{}
		, m_lastAccessSpecifier(CX_CXXPrivate)
	{
	}
	bool CTaggedClass::CollectSibling(const CXCursor& cursor, const STaggedNodeCollectingContext& context)
	{
		bool addedTaggedChild = false;
		if (m_stage == EStage::None)
		{
			auto kind = clang_getCursorKind(cursor);
			if (kind == CXCursor_TypedefDecl)
			{
				auto found = FindTagByDisplayName(cursor, NiflectGenDefinition::CodeTag::Field);
				if (!found)
					found = FindTagByDisplayName(cursor, NiflectGenDefinition::CodeTag::Method);
				if (found)
				{
					m_tagLocation = clang_getCursorLocation(cursor);
					m_stage = EStage::FoundMember;
				}
			}
			else if (kind == CXCursor_CXXAccessSpecifier)
			{
				m_lastAccessSpecifier = clang_getCXXAccessSpecifier(cursor);//可能不需要缓存, 直接通过cursor获取即可, 因为基类的AccessorSpecifier无cursor, 但可通过clang_getCXXAccessSpecifier获取到
			}
			else if (kind == CXCursor_CXXBaseSpecifier)
			{
				this->InitBaseTypeSpecifierCursor(cursor);
			}
		}
		else if (m_stage == EStage::FoundMember)
		{
			bool ok = false;
			auto kind = clang_getCursorKind(cursor);
			if (kind == CXCursor_FieldDecl)
				ok = true;
			else if (kind == CXCursor_CXXMethod)
				ok = true;
			if (ok)
			{
				CXCursor macroCursor;
				context.m_tagCollection.TakeByTagLocation(m_tagLocation, macroCursor);
				auto taggedChild = MakeShared<CTaggedInheritableTypeMember>();
				taggedChild->InitMember(m_lastAccessSpecifier);
				this->AddChildAndInitDefault(taggedChild, cursor, macroCursor);
				m_stage = EStage::None;
				addedTaggedChild = true;
			}
			else
			{
				GenLogError(context.m_log, "The member must be either a field or a method");
			}
		}
		return addedTaggedChild;
	}
}