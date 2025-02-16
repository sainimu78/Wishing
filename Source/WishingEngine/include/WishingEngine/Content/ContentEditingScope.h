#pragma once
#include "WishingEngineCommon.h"
#include "Niflect/Base/String.h"

namespace Wishing
{
	class CContentSystem;
	class CContentDirNode2;

	class CContentAddingOption
	{
		typedef CContentAddingOption CThis;
	public:
		CThis& SetParentNode(CContentDirNode2* parent)
		{
			m_parent = parent;
			return *this;
		}

		CContentDirNode2* m_parent;
	};

	class CContentEditingScope
	{
	public:
		CContentEditingScope(CContentSystem* sys)
			: m_sys(sys)
			, m_changed(false)
		{

		}
		~CContentEditingScope()
		{
			if (m_changed)
			{
				//m_sys->
			}
		}

	public:
		WISHINGENGINE_API void AddFileNode(const Niflect::CString& name, const CContentAddingOption& opt = CContentAddingOption());

	private:
		CContentSystem* m_sys;
		bool m_changed;
	};
}