#pragma once
#include "Niflect/NiflectType.h"

namespace Wishing
{
	class CWishingObject
	{
	public:
		virtual Niflect::CNiflectType* GetType() const = 0;
	};

#define WISHINGOBJECT_DECLARE()\
	NIFGNSD()\
	public:\
		virtual Niflect::CNiflectType* GetType() const override\
		{\
			return Niflect::StaticGetType<CThis>();\
		}\
	private:
}