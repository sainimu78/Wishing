#include "QApplication"
#include "Widget/Creator/CreatorWindow.h"
#include "QDesktopWidget"
#include "Base/UuidGen.h"//测试用
#include "Creator/CreatorSystem.h"
#include "Niflect/Util/SystemUtil.h"
#include "Creator/CreatorOption.h"

#ifdef WIN32
#include <Windows.h>
#endif

static Niflect::CString GetNextArgValue(const char* const* argv, int& idx)
{
	idx += 1;
	Niflect::CString str;
	auto& psz = argv[idx];
	if (psz[0] == '\"')
	{
		str = &psz[1];
		ASSERT(str.length() >= 2);
		if (str.back() == '\"')
			str.erase(str.begin() + str.length() - 1);
		else
			ASSERT(false);
	}
	else
	{
		str = psz;
	}
	return str;
}
static Niflect::CString GetNextArgPath(const char* const* argv, int& idx)
{
	auto path = GetNextArgValue(argv, idx);
    std::replace(path.begin(), path.end(), '\\', '/');
	return NiflectUtil::ResolvePath(path);
}

static void ParseOptions(int argc, const char* const* argv, Wishing::CCreatorOption& opt)
{
	ASSERT(argc > 1);
	for (int idx = 1; idx < argc; ++idx)
	{
		auto& pszV = argv[idx];
		if (strcmp(pszV, "-p") == 0)
		{
			opt.m_projectDirPath = GetNextArgPath(argv, idx);
		}
		else
		{
			LogInfo("Unknown option: %s\n", pszV);
		}
	}
}

static int EditorMain(int argc, char** argv)
{
    Wishing::CCreatorOption opt;
    ParseOptions(argc, argv, opt);

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

    using namespace Wishing;
    CCreatorSystem sys;
    sys.Initialize(opt);
    sys.Start();

    using namespace WishingQt;
    QCreatorWindow wnd;
    wnd.Init(&sys);
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
    //// 要检查的目录路径
    //boost::filesystem::path dir("../");

    //// 检查目录是否存在
    //if (boost::filesystem::exists(dir)) {
    //    std::cout << "目录存在！" << std::endl;
    //}
    //else {
    //    std::cout << "目录不存在！" << std::endl;
    //}

    return 0;
}

#include "boost/chrono.hpp"
int CMy::Test1()
{
    // 开始计时
    auto start = boost::chrono::high_resolution_clock::now();

    // 模拟一些计算工作
    for (volatile int i = 0; i < 100000000; ++i) {
        // 这里什么也不做，只是耗时
    }

    // 结束计时
    auto end = boost::chrono::high_resolution_clock::now();

    // 计算所花费的时间
    boost::chrono::duration<double> elapsed = end - start;
    std::cout << "Operation took: " << elapsed.count() << " seconds." << std::endl;

    return 0;
}
static CMy g_a;