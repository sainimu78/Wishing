#include "SampleAPI.h"
#include "SampleAPI_private.h"

void InitSampleAPI(Niflect::CNiflectTable& table)
{
	using namespace Niflect;
	GeneratedInitialReg(&table);
	GeneratedInitTypes();
	table.InitTypesLayout();
}