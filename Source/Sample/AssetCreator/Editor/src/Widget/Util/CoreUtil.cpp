#include "Widget/Util/CoreUtil.h"

namespace WishingQt
{
	QString CStringToQString(const Niflect::CString& wstr)
	{
		return QString::fromLocal8Bit(wstr.c_str());
	}
}