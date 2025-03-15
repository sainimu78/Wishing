#include "Wishing/Content/ContentSystem.h"

namespace Wishing
{
	CContentSystem::CContentSystem()
	{
	}
	bool CContentSystem::Initialize()
	{
		return true;
	}
	bool CContentSystem::Start()
	{
		return true;
	}
	bool CContentSystem::Stop()
	{
		return true;
	}
	void CContentSystem::Finalize()
	{

	}

	CContentGraphEditingScope::CContentGraphEditingScope()
	{

	}
	CContentGraphEditingScope::~CContentGraphEditingScope()
	{
	}

	CSharedContentSystem CreateContentSystem()
	{
		return Niflect::MakeShared<CContentSystem>();
	}
}