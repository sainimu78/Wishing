#pragma once
#include "Asset/EdAsset_gen.h"

namespace Editor
{
#define AAAAAAAA()\
		GENERATED_BODY()\
	public:\
		virtual Niflect::CNiflectType* GetType() const\
		{\
			return Niflect::StaticGetType<CThis>();\
		}\
	private:

	NIF_T()
	class CEdAsset
	{
		AAAAAAAA()
	};
}