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

void test0() {
    //1、日志的布局
    PatternLayout *ppl1 = new PatternLayout();
    ppl1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ppl3 = new PatternLayout();
    ppl3->setConversionPattern("%d %c [%p] %m%n");
    
    //2、日志的目的地
    //注意：一个日志的目的地要对应一种日志的布局，不能共用
    //一旦共用就会发生错误
    //终端
    OstreamAppender *pos = new OstreamAppender("ostream", &cout);
    pos->setLayout(ppl1);

    //文件
    FileAppender *pfa = new FileAppender("FileAppender", "wd.txt");
    pfa->setLayout(ppl2);

    //回卷文件
    RollingFileAppender *prfa = new RollingFileAppender("RollingFileAppender",
                                                        "waodao.txt",
                                                        5 * 1024,
                                                        3);
    prfa->setLayout(ppl3);

    //3、Category的种类，日志记录器
    Category &root = Category::getRoot().getInstance("mycat");
    root.addAppender(pos);
    root.addAppender(pfa);
    root.addAppender(prfa);

    //4、只有大于等于设置的优先级，日志记录器才会将该条日志信息记录下来
    size_t idx = 300;
    while(idx > 0) {
        root.fatal("this is an fatal message");
        root.alert("this is an alert message");
        root.crit("this is an crit message");
        root.error("this is an error message");
        root.warn("this is an warn message");
        root.info("this is an info message");
        root.debug("this is an debug message");
        --idx;
    }

    //回收内存
    Category::shutdown();
}
int main() {
    test0();
    return 0;
}

