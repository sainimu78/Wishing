#pragma once
#include "Engine/Test/Asset/TestAsset.h"
#include "Engine/Test/Mesh/TestMesh_gen.h"

namespace TestEngineEditMode
{
	NIF_T()
	class CTestMesh : public CTestAsset
	{
		GENERATED_BODY()
	private:
		NIF_F()
		Niflect::CString m_debugName;
	};
}