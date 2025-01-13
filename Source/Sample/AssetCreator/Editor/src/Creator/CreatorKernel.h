#pragma once

namespace Wishing
{
	class CCreatorKernel
	{
	public:
		bool Initialize() { return false; }
		bool Start() { return false; }
		bool Stop() { return false; }
		bool Finalize() { return false; }
	};
}