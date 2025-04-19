#include "QApplication"
#include "Widget/ExampleWindow.h"
#include "QDesktopWidget"
#ifdef WIN32
#include <Windows.h>
#endif
#include "qtimer.h"
#include "PropertyEditorSystem.h"

#include "Accessor/CompoundAccessor.h"
#include "Accessor/ValueTypeAccessor.h"
#include "Property/PropertyNode.h"

//�ɸ�Ϊ���� Nata �Զ���
static void InitBindings(CPropertyEditorSystem& sys)
{
    using namespace Niflect;
    sys.RegisterBinding(StaticGetType<CCompoundAccessor>(), StaticGetType<CPropertyGroup>());
    sys.RegisterBinding(StaticGetType<CFloatAccessor>(), StaticGetType<CFloatProperty>());
}

static int EditorMain(int argc, char** argv)
{
#ifdef WIN32
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
#endif

    CPropertyEditorSystem sys;
    sys.Init();

    InitBindings(sys);

    QApplication app(argc, argv);
    QDesktopWidget desktop;
    QRect screenRect = desktop.screenGeometry();
    int width = static_cast<int>(screenRect.width() * 0.8);
    int height = static_cast<int>(screenRect.height() * 0.8);
#ifdef WIN32
#undef min
#endif
    width = std::min(width, 800);
    height = std::min(height, 600);

    QExampleWindow wnd;
    wnd.Init(&sys);
    wnd.resize(width, height);
    wnd.show();
    QTimer::singleShot(1000, [&wnd, &sys]()
        {
            wnd.BuildUi(sys.GetTable());
        });
    return app.exec();
}

#ifdef WIN32
static char* CreateCharsFromWChars(int codePage, const wchar_t* aw)
{
    const int required = WideCharToMultiByte(codePage, 0, aw, -1, NULL, 0, NULL, NULL);
    char* result = new char[required];
    WideCharToMultiByte(codePage, 0, aw, -1, result, required, NULL, NULL);
    return result;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    int argc;
    wchar_t** argvW = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argvW == NULL)
        return -1;
    char** argv = new char*[argc + 1];
    for (int idx = 0; idx < argc; ++idx)
        argv[idx] = CreateCharsFromWChars(CP_ACP, argvW[idx]);
    argv[argc] = 0;
    auto ret = EditorMain(argc, argv);
    for (int idx = 0; idx < argc; ++idx)
        delete[] argv[idx];
    delete[] argv;
    return ret;
}
#else
int main(int argc, char** argv)
{
    return EditorMain(argc, argv);
}
#endif