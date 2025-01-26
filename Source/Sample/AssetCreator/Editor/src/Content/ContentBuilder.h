#pragma once

namespace Wishing
{
	class CContentManager;

	class CContentBuilder
	{
	public:
		CContentBuilder(CContentManager& mgr);

	private:
		CContentManager& m_mgr;
	};
}