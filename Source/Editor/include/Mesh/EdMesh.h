#pragma once
#include "Asset/EdAsset.h"
#include "Mesh/EdMesh_gen.h"

namespace Editor
{
#define AAAAAAAA()\
	GENERATED_BODY()\
	public:\
	Niflect::CNiflectType* GetType() const\
	{\
		return Niflect::StaticGetType<CThis>();\
	}\
	private:

	NIF_T()
	class CEdMesh : public CEdAsset
	{
		AAAAAAAA()
	public:
		NIF_F()
		Niflect::CString m_debugName;
	};
}