#pragma once
#include "Niflect/NiflectBase.h"
#include "Content/ContentReferenceTable.h"

namespace Wishing
{
	class CProject
	{
	public:
		bool Open(const Niflect::CString& filePath);

	private:
		CContentReferenceTable m_contentTable;
	};
	using CSharedProject = Niflect::TSharedPtr<CProject>;

	bool CreateProject(const Niflect::CString& filePath);
}