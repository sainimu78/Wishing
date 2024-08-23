#include "Niflect/NiflectBindingSetting.h"
#include "Engine/BuiltinAccessor.h"

namespace EngineTypeBindingSettingScope
{
	using namespace Niflect;
	using namespace Engine;

	NIF_BS() TBindingSetting<CFloatAccessor, float>;
	NIF_BS() TBindingSetting<CBoolAccessor, bool>;
}