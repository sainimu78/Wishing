#include "SampleAPI.h"
#include "SampleObject.h"
#include "Niflect/Serialization/JsonFormat.h"

int main()
{
	using namespace Niflect;
	CNiflectTable table;
	InitSampleAPI(table);

	auto type = StaticGetType<CSampleObject>();
	auto src = type->MakeSharedInstance<CSampleObject>();
	src->InitForTest();
	CRwNode rw;
	type->SaveInstanceToRwNode(src.Get(), &rw);
	Niflect::CStringStream ss;
	CJsonFormat::Write(&rw, ss);
	auto dst = type->MakeSharedInstance<CSampleObject>();
	type->LoadInstanceFromRwNode(dst.Get(), &rw);
	ASSERT(*src == *dst);
	printf("%s\n", ss.str().c_str());
	return 0;
}