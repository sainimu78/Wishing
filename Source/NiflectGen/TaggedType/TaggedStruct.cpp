#include "NiflectGen/TaggedType/TaggedStruct.h"
#include "NiflectGen/Log/Log.h"
#include "NiflectGen/Util/CursorUtil.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"

namespace NiflectGen
{
	using namespace Niflect;

	CTaggedStruct::CTaggedStruct()
		: m_stage(EStage::None)
		, m_tagLocation{}
	{
	}
	bool CTaggedStruct::CollectSibling(const CXCursor& cursor, const STaggedNodeCollectingContext& context)
	{
		bool addedTaggedChild = false;
		if (m_stage == EStage::None)
		{
			auto kind = clang_getCursorKind(cursor);
			if (kind == CXCursor_TypedefDecl)
			{
				if (this->CollectGeneratedBodyTag(cursor, kind))
				{

				}
				else
				{
					auto found = FindTagByDisplayName(cursor, NiflectGenDefinition::CodeTag::Field);
					if (found)
					{
						m_tagLocation = clang_getCursorLocation(cursor);
						m_stage = EStage::FoundMember;
					}
				}
			}
			else if (kind == CXCursor_CXXBaseSpecifier)
			{
				this->InitBaseTypeSpecifierCursor(cursor);
			}
		}
		else if (m_stage == EStage::FoundMember)
		{
			this->ErrorIfNoGeneratedBodyTag(cursor);

			bool ok = false;
			auto kind = clang_getCursorKind(cursor);
			if (kind == CXCursor_FieldDecl)
				ok = true;
			if (ok)
			{
				CXCursor macroCursor;
				context.m_tagCollection.TakeByTagLocation(m_tagLocation, macroCursor);
				auto taggedChild = MakeShared<CTaggedInheritableTypeMember>();
				this->AddChildAndInitDefault(taggedChild, cursor, macroCursor);
				m_stage = EStage::None;
				addedTaggedChild = true;
			}
			else
			{
				GenLogError(context.m_log, "The member must be a field");
			}
		}
		return addedTaggedChild;
	}
}