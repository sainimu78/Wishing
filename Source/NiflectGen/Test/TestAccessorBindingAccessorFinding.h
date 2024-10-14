#include "Niflect/NiflectBindingSetting.h"
#include "Niflect/NiflectAccessor.h"
#include "NiflectGen/Test/TestOriginalTypeAccessorFinding.h"

namespace MyAccessor
{
	class CMyClassAccessor : public Niflect::CAccessor
	{
	};

	class CMyFloatAccessor : public Niflect::CAccessor
	{
	};
}

namespace EngineTypeBindingSettingScope
{
	using namespace Niflect;
	using namespace TestMyFinding;
	using namespace MyAccessor;
	NIF_BS() TBindingSetting<CMyClassAccessor, CMyClass_0>;
	NIF_BS() TBindingSetting<CMyFloatAccessor, float>;
}