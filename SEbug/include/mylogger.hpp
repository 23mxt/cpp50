#ifndef __MYLOGGER_HPP__
#define __MYLOGGER_HPP__
#include "log4cpp/Category.hh"
namespace mylog{
class Mylogger{
public:
    static Mylogger& getInstance();
    static void destroyInstance();
    void error(const char*);
    void info(const char*);
    void warn(const char*);
    void debug(const char*);

    template <class... Args>
    void error(const char *,const Args&...);
        // _cat.error(fmt, args...);
    template<class...Args>
    void info(const char*,const Args&...);
    template<class...Args>
    void warn(const char*,const Args&...);
    template<class...Args>
    void debug(const char*,const Args&...);
private:
    static void init();
    Mylogger();
    ~Mylogger();
    static Mylogger* _mylogger;
    static pthread_once_t _once_ctl;
    log4cpp::Category& _cat;
};
#define addPrefix(msg) std::string("[").append(__FILE__).append("] ")\
                        .append("[").append(__func__).append("] ")\
                        .append("[").append(std::to_string(__LINE__)).append("] ")\
                        .append(msg).c_str()
#define LogError(msg,...) mylog::Mylogger::getInstance().error(addPrefix(msg),##__VA_ARGS__)
#define LogInfo(msg,...) mylog::Mylogger::getInstance().info(addPrefix(msg),##__VA_ARGS__)
#define LogWarn(msg,...) mylog::Mylogger::getInstance().warn(addPrefix(msg),##__VA_ARGS__)
#define LogDebug(msg,...) mylog::Mylogger::getInstance().debug(addPrefix(msg),##__VA_ARGS__)
}//end of mylog 
#include "mylogger.tcc"

#endif