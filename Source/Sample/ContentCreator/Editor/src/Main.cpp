#include "QApplication"
#include "UI/Qt/Creator/CreatorWindow.h"
#include "QDesktopWidget"
#include "Base/UuidGen.h"//测试用
#include "Creator/CreatorSystem.h"
#include "Niflect/Util/SystemUtil.h"
#include "Creator/CreatorOption.h"
#include "Creator/CreatorPipeline.h"
#include "WishingEngine/Content/ContentSystem.h"
#include "WishingEngine/WishingEngine.h"

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
	//ASSERT(argc > 1);
	for (int idx = 1; idx < argc; ++idx)
	{
		auto& pszV = argv[idx];
		if (strcmp(pszV, "-p") == 0)
		{
			opt.m_projectDirPath = GetNextArgPath(argv, idx);
		}
		else
		{
			printf("Unknown option: %s\n", pszV);
		}
	}
}

static int EditorMain(int argc, char** argv)
{
#ifdef WIN32
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
#endif

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
    if (!sys.Start())
        ASSERT(false);

    auto engine = CreateWishingEngine();
    engine->Initialize();

    auto sys2 = CreateContentSystem();
    sys2->Initialize();
    if (!sys2->Start())
        ASSERT(false);

    using namespace WishingQt;
    QCreatorWindow wnd;
    wnd.Init(&sys);
    wnd.Init2(sys2.Get());
    wnd.resize(width, height);
    wnd.show();
    auto ret = app.exec();
    sys.Stop();
    sys2->Stop();
    sys2->Finalize();

    return ret;
}

//#include <QPushButton>
//#include <QMainWindow>
//#include <QDebug>
//#include "qthread.h"
//#include "qtimer.h"
//#include <boost/thread.hpp>
//#include <QMutex>
//#include <QWaitCondition>
//#include "UI/Qt/Util/CoreUtil.h"
//
//class Worker : public QObject {
//    Q_OBJECT
//public:
//    explicit Worker(QMutex* mutex, QWaitCondition* condition)
//        : mutex_(mutex), condition_(condition) {
//    }
//
//public slots:
//    void doWork() {
//        qDebug() << WishingQt::CStringToQString("工作线程启动，线程ID：") << QThread::currentThreadId();
//        while (true) {
//            // 等待信号量
//            QMutexLocker lock(mutex_);
//            condition_->wait(mutex_);
//            qDebug() << WishingQt::CStringToQString("工作线程收到信号量，开始执行任务");
//
//            // 模拟耗时操作
//            QThread::sleep(2);
//
//            // 触发主线程回调（线程安全）
//            QTimer::singleShot(0, qApp, [] {
//                qDebug() << WishingQt::CStringToQString("主线程回调执行，线程ID：") << QThread::currentThreadId();
//                });
//        }
//    }
//
//private:
//    QMutex* mutex_;
//    QWaitCondition* condition_;
//};
//class MainWindow : public QMainWindow {
//    Q_OBJECT
//public:
//    explicit MainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
//        // 初始化 UI
//        button_ = new QPushButton(WishingQt::CStringToQString("点击启动线程任务"), this);
//        setCentralWidget(button_);
//
//        // 初始化同步工具
//        mutex_ = new QMutex;
//        condition_ = new QWaitCondition;
//
//        // 启动 Boost 线程
//        //worker_thread_ = new boost::thread([this] { workerThread(); });
//
//        {
//            QThread* workerThread = new QThread(this);
//            Worker* worker = new Worker(mutex_, condition_);
//            worker->moveToThread(workerThread);
//
//            connect(workerThread, &QThread::started, worker, &Worker::doWork);
//            connect(button_, &QPushButton::clicked, [this] {
//                condition_->wakeOne();
//                });
//
//            workerThread->start();
//        }
//
//        // 连接按钮点击信号
//        connect(button_, &QPushButton::clicked, [this] {
//            qDebug() << WishingQt::CStringToQString("按钮点击，唤醒工作线程");
//            condition_->wakeOne(); // 释放信号量
//            });
//    }
//
//    ~MainWindow() {
//        if (worker_thread_ != NULL)
//        {
//            worker_thread_->interrupt();
//            worker_thread_->join();
//            delete worker_thread_;
//        }
//        delete mutex_;
//        delete condition_;
//    }
//
//private slots:
//    void updateUI(const QString& message) {
//        button_->setText(message);
//        qDebug() << WishingQt::CStringToQString("UI更新完成，当前线程ID：") << QThread::currentThreadId();
//    }
//
//private:
//    // Boost 工作线程逻辑
//    void workerThread() {
//        qDebug() << WishingQt::CStringToQString("工作线程启动，线程ID：") << QThread::currentThreadId();
//        while (true) {
//            try {
//                // 等待信号量
//                QMutexLocker lock(mutex_);
//                condition_->wait(mutex_);
//                qDebug() << WishingQt::CStringToQString("工作线程收到信号量，开始执行任务");
//
//                // 模拟耗时操作
//                boost::this_thread::sleep_for(boost::chrono::seconds(2));
//
//                // 关键：通过 QTimer::singleShot 触发主线程回调
//                QTimer::singleShot(0, qApp, [this] {
//                    updateUI(WishingQt::CStringToQString("任务已完成"));
//                    });
//            }
//            catch (boost::thread_interrupted&) {
//                qDebug() << WishingQt::CStringToQString("工作线程被终止");
//                break;
//            }
//        }
//    }
//
//    QPushButton* button_;
//    QMutex* mutex_;
//    QWaitCondition* condition_;
//    boost::thread* worker_thread_ = NULL;
//};
//
//static int EditorMain(int argc, char** argv)
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}

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