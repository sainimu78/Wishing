#ifdef TEST_FOR_GCC
#include <iostream>
#include "E:/S3/S3ResourceEditor/engine_ref/SampleTest/SampleGamePrototyping/Cos/Client/Niflect/Base/NiflectBase.h"
#include "E:/S3/S3ResourceEditor/engine_ref/Tools/Niflect/NiflectGen/Writer/MustacheWrapper.h"

int main()
{
    using namespace Niflect;
	using namespace NiflectMustache;
    CString view{R"({{#names}}
    Hi {{name}} !
{{/names}})"};
    CData context;
    CData array(CData::type::list);
    CData item0("name", "Chris");
    CData item1("name", "Mark");
    CData item2("name", "Scott");
    array.push_back(item0);
    array.push_back(item1);
    array.push_back(item2);
    context.set("names", array);
    CMustache tmpl(view);
    std::cout << tmpl.render(context) << std::endl;
    printf("");
	return 0;
}
#endif