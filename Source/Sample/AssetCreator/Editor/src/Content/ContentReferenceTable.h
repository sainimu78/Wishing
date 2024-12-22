#pragma once
#include "Content/ContentReferenceNode.h"
#include "Niflect/NiflectBase.h"

namespace Wishing
{
	class CContentReferenceTable
	{
	public:
		CContentReferenceNode* AddNode(const Niflect::CString& name);
		void DeleteNode(CContentReferenceNode* node);
	};
}