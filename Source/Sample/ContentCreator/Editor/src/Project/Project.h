#pragma once
#include "Niflect/NiflectBase.h"

namespace Wishing
{
	class CProject
	{
	public:
		bool Open(const Niflect::CString& filePath);

	private:
	};
	using CSharedProject = Niflect::TSharedPtr<CProject>;

	bool CreateProject(const Niflect::CString& filePath);
}