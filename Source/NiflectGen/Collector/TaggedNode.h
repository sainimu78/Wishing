#pragma once
#include "Niflect/NiflectBase.h"
#include "clang-c/Index.h"

namespace NiflectGen
{
	class CGenLog;
	class CTaggedNode2;

	using CSharedTaggedNode = Niflect::TSharedPtr<CTaggedNode2>;

	struct CXSourceLocationComp
	{
		bool operator()(const CXSourceLocation& lhs, const CXSourceLocation& rhs) const;
	};

	class CMacroTagCollection2
	{
	public:
		CMacroTagCollection2();
		~CMacroTagCollection2();
		bool CollectMacroExpansion(const CXCursor& cursor);
		//void TakeByTagLocation(const CXSourceLocation& tagLocation, const CXCursor& typeCursor, CTaggedNode& taggedParent);
		void TakeByTagLocation(const CXSourceLocation& tagLocation, CXCursor& macroCursor);

	private:
		Niflect::TMap<CXSourceLocation, CXCursor, CXSourceLocationComp> m_mapLocationToMacroCursor;
	};

	struct STaggedNodeCollectingContext
	{
		CMacroTagCollection2& m_tagCollection;
		CGenLog*& m_log;
	};

	class CTaggedNode2
	{
	public:
		CTaggedNode2();
		void Init(const CXCursor& cursor);
		void SetMacroCursor(const CXCursor& macroCursor)
		{
			m_macroCursor = macroCursor;
		}
		void AddChildAndInitDefault(const CSharedTaggedNode& taggedNode, const CXCursor& cursor, const CXCursor& macroCursor);
		uint32 GetChildrenCount() const
		{
			return static_cast<uint32>(m_vecChild.size());
		}
		CTaggedNode2* GetChild(uint32 idx) const
		{
			return m_vecChild[idx].Get();
		}
		const CXCursor& GetCursor() const
		{
			return m_cursor;
		}

	public:
		virtual bool CollectSibling(const CXCursor& cursor, const STaggedNodeCollectingContext& context)
		{
			return false;
		}

	public:
		const CXCursor& DebugGetMacroCursor() const
		{
			return m_macroCursor;
		}
		const Niflect::TArrayNif<CSharedTaggedNode>& DebugGetChildren() const
		{
			return m_vecChild;
		}
		void DebugPrint(FILE* fp, uint32 level) const;

	protected:
		virtual void DebugDerivedPrint(FILE* fp) const {}

	protected:
		CXCursor m_macroCursor;
		Niflect::TArrayNif<CSharedTaggedNode> m_vecChild;

	private:
		CXCursor m_cursor;
	};
}