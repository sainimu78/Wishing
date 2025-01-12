#include "QApplication"
#include "Widget/Creator/CreatorWindow.h"
#include "QDesktopWidget"
#include "Base/UuidGen.h"
#ifdef WIN32
#include <Windows.h>
#endif

static int EditorMain(int argc, char** argv)
{
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

    using namespace WishingQt;
    QCreatorWindow wnd;
    wnd.resize(width, height);
    wnd.show();
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


#include <iostream>

class CMy
{
public:
    CMy()
    {
#ifdef WIN32
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
#endif
        Wishing::_Test_CUuid();

        this->Test0();
        this->Test1();
    }
    int Test0();
    int Test1();
};

//#include "boost/filesystem.hpp"
int CMy::Test0()
{
    //// Ҫ����Ŀ¼·��
    //boost::filesystem::path dir("../");

    //// ���Ŀ¼�Ƿ����
    //if (boost::filesystem::exists(dir)) {
    //    std::cout << "Ŀ¼���ڣ�" << std::endl;
    //}
    //else {
    //    std::cout << "Ŀ¼�����ڣ�" << std::endl;
    //}

    return 0;
}

#include "boost/chrono.hpp"
int CMy::Test1()
{
    // ��ʼ��ʱ
    auto start = boost::chrono::high_resolution_clock::now();

    // ģ��һЩ���㹤��
    for (volatile int i = 0; i < 100000000; ++i) {
        // ����ʲôҲ������ֻ�Ǻ�ʱ
    }

    // ������ʱ
    auto end = boost::chrono::high_resolution_clock::now();

    // ���������ѵ�ʱ��
    boost::chrono::duration<double> elapsed = end - start;
    std::cout << "Operation took: " << elapsed.count() << " seconds." << std::endl;

    return 0;
}
static CMy g_a;