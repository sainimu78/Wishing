#pragma once
#include "Niflect/NiflectBase.h"
#include "NiflectGen/Collector/CollectionData.h"
#include "clang-c/CXSourceLocation.h"
#include "NiflectGen/Log/Log.h"
#include "NiflectGen/Collector/TaggedNode.h"
#include "NiflectGen/Util/CursorMap.h"

namespace NiflectGen
{
	class CVisitingDebugData
	{
	public:
		CVisitingDebugData();
		void Init(const CXCursor& cursor, FILE* fp);
		bool Check() const;

	public:
		uint32 m_allCursorsCountForChecking;
		FILE* m_fp;
		int m_level;
		uint32 m_allCursorsCount;
	};

	class CCollectingContext
	{
	public:
		CCollectingContext(CGenLog* log)
			: m_log(log)
			, m_debugData(NULL)
		{

		}

	public:
		CGenLog* m_log;
		CVisitingDebugData* m_debugData;
	};

	class CTaggedTypeCollector
	{
	public:
		CTaggedTypeCollector(CMacroTagCollection2& tagCollection);
		bool Collect(const CXCursor& cursor, CTaggedNode2* taggedParent, CGenLog* log);

	private:
		enum class EStage
		{
			None,
			Found,
		};
		EStage m_stage;
		CXSourceLocation m_tagLocation;
		CMacroTagCollection2& m_tagCollection;
	};

	class CTemplateCollector
	{
	public:
		CTemplateCollector();
		bool Collect(const CXCursor& cursor, CTaggedNode2* taggedParent, CGenLog* log);
	};

	class CTaggedTypeCollector;
	class CTemplateCollector;

	struct SVisitingData
	{
		Niflect::TArrayNif<uint32> m_vecTaggedChildIndex;
	};

	class CDataCollector
	{
		friend class CScopeNamespace;
		friend class CScopeBindingSetting;
		friend class CScopeAccessorBaseCursorDecl;
		friend class CScopeTemplateDecl;
		friend CXChildVisitResult VisitorCallback(CXCursor cursor, CXCursor parent, CXClientData data);
	public:
		CDataCollector();

	public:
		void Collect(const CXCursor& cursor, CTaggedNode2* taggedParent, CCollectingContext& context, CCollectionData& collectionData);
		void DebugFinish2(CTaggedNode2* taggedParent, const CCollectionData& collectionData) const;

	private:
		void CollectDataRecurs2(const CXCursor& cursor, const CXCursor& parentCursor, CTaggedNode2* taggedParent, CCollectingContext& context, CCollectionData& collectionData);
		void Visit(const CXCursor& cursor, CTaggedNode2* taggedParent, CCollectingContext& context, SVisitingData& data);

	private:
		bool CheckDeclDerivedFromFieldBaseClass(CXCursor p) const;
		CXCursor FindAliasDecl(CXCursor decl) const;

	private:
		uint32 GetNamespaceDepth() const;
		const CXCursor& GetVisitingNamespaceReserved() const;//����

	private:
		Niflect::TArrayNif<CXCursor> m_stkNamespaceCursor;//����
		CMacroTagCollection2 m_macroTagCollection;
		CTaggedTypeCollector m_taggedTypeCollector;
		CTemplateCollector m_templateCollector;
		TCursorMap<CXCursor> m_mapCursorDeclToBaseCursorDecl;
		TCursorMap<CXCursor> m_mapCursorDeclToAliasDecl;
		//CCursorSet m_setAliasTemplateOrClassTemplateDecl;
		bool m_collectingClassBaseCursorDecl;
	};

	//void PrintTemplateSubcursor333333333(const CTemplateSubcursor& parentSubcursor, int level);
}