#include "SampleAPI.h"
#include "SampleAPI_private.h"

void InitSampleAPI(Niflect::CNiflectTable& table)
{
	using namespace Niflect;
	GeneratedRegisterTypes(&table);
	GeneratedInitTypes();
	table.InitTypesLayout();
}