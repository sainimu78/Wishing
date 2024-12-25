#include "Project/Project.h"
#include "Niflect/Serialization/JsonFormat.h"
#include "Niflect/Util/FileStreamUtil.h"

namespace Wishing
{
	bool CProject::Open(const Niflect::CString& filePath)
	{
		return false;
	}
	bool CreateProject(const Niflect::CString& filePath)
	{
		RwTree::CRwNode rw;
		std::ofstream ofs;
		if (NiflectUtil::OpenFileStream(ofs, filePath))
		{
			RwTree::CJsonFormat::Write(&rw, ofs);
			return ofs.good();
		}
		return false;
	}
}