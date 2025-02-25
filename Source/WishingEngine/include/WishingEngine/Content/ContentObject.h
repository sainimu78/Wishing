#pragma once
#include "Niflect/NiflectType.h"

namespace Wishing
{
	class CContentObject
	{
	public:
		virtual Niflect::CNiflectType* GetType() const = 0;
	};

#define CONTENT_OBJECT_DECLARE()\
	GENERATED_BODY()\
	public:\
		virtual Niflect::CNiflectType* GetType() const override\
		{\
			return Niflect::StaticGetType<CThis>();\
		}\
	private:
}