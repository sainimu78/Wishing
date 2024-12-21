#pragma once
#include "Niflect/NiflectBase.h"
#include "QString"

namespace WishingQt
{
	QString CStringToQString(const Niflect::CString& str);
	Niflect::CString QStringToCString(const QString& qstr);
}