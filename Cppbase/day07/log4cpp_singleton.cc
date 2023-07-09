#include <string.h>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/StringQueueAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using namespace log4cpp;

//单例不能在类外创建，在类内创建对象

class Mylogger
{
public:
    static Mylogger* getInstance()
    {
        if(_pInstance == nullptr) {
            _pInstance = new Mylogger();
            cout << "once" << endl;
        }
        return _pInstance;
    }
    
    void init()
    {
        //日志布局
        PatternLayout *ppl1 = new PatternLayout();
        ppl1->setConversionPattern("%d %c [%p] %m%n");

        /* PatternLayout *ppl2 = new PatternLayout(); */
        /* ppl2->setConversionPattern("%d %c [%p] %m%n"); */
        //日至目的地
        OstreamAppender *pos = new OstreamAppender("ostream", &cout);
        pos->setLayout(ppl1);

        //目的地对应布局
        root.addAppender(pos);
        //过滤器
        root.setPriority(Priority::INFO);
    }

    //记录日志
    void warn(const char *msg)
    {
        cout << "why?" << endl;
        root.warn("this is an warn message");
    }
	void error(const char *msg)
    {
        root.error("this is an error message");
    }
	void debug(const char *msg)
    {
        root.debug("this is an debug message");
    }
	void info(const char *msg)
    {
        root.info("this is an info message");
    }
    void fatal(const char *msg)
    {
        root.fatal("this is an fatal message");
    }
    void crit(const char *msg)
    {
        root.fatal("this is an crit message");
    }
    void shutdown()
    {
        Category::shutdown();
    }

private:
    Mylogger() 
    {
        cout << "Mylogger()" << endl;
    }
    ~Mylogger() 
    {
        cout << "~Mylogger()" << endl;
    }
private:
    static Mylogger* _pInstance;
    static Category &root;
};
Mylogger* Mylogger::_pInstance = nullptr;
Category& Mylogger::root = Category::getRoot().getInstance("mycat");

void LogInfo(const char* msg)
{
    Mylogger* log = Mylogger::getInstance();
    log->init();
    cout << 1 << endl;

    log->info(msg);
}

void LogError(const char* msg)
{
    Mylogger* log = Mylogger::getInstance();
    log->init();
    cout << 2 << endl;

    log->error(msg);
}

void LogWarn(const char* msg)
{
    Mylogger* log = Mylogger::getInstance();
    log->init();
    cout << 3 << endl;

    log->warn(msg);
}

void LogDebug(const char* msg)
{
    Mylogger* log = Mylogger::getInstance();
    log->init();
    cout << 4 << endl;

    log->debug(msg);
}

void test0()
{
    Mylogger* log = Mylogger::getInstance();
    Mylogger* log2 = Mylogger::getInstance();
    /* cout << "plog " <<  log << endl; */
    /* cout << "plog2 " <<  log2 << endl; */
    log->init();

    log->info("The log is info message");
    log->error("The log is error message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");

    log->shutdown();
}

void test1()
{
    LogInfo("The log is info message");
    LogError("The log is error message");
    LogWarn("The log is warn message");
    LogDebug("The log is debug message");
}

int main()
{
    /* test0(); */
    test1();
    return 0;
}

