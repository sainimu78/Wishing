#pragma once
#include "Niflect/NiflectBase.h"
#include "QtCore/qstring.h"

namespace WishingQt
{
	QString CStringToQString(const Niflect::CString& str);
	Niflect::CString QStringToCString(const QString& qstr);
}