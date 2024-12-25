#include "CppProjectGen.h"
#include "CMakeTemplate.h"

namespace CppProjectGen
{
    using namespace NiflectGen;
    using namespace WishingProjectTool;

	void TestInvokation()
	{
        CCodeTemplate tpl1;
        ReadTemplateFromRawData(tpl1,
R"(#include <iostream>
int main()
{
    printf("@{nihao}, @{bucuo}\n");
    return 0;
})");
        Niflect::TSet<Niflect::CString> setReplacedLabel;
        CLabelToCodeMapping map;
        MapLabelToText(map, "nihao", "shima");
        MapLabelToText(map, "bucuo", "${bucuo}");
        CCodeLines lines;
        tpl1.ReplaceLabels(map, lines, &setReplacedLabel);
        ASSERT(setReplacedLabel.size() == map.size());
        DebugPrintCodeLines(lines);
	}
}