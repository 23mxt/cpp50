#ifndef __MYLOGGER_H__
#define __MYLOGGER_H__

#include <log4cpp/Category.hh>


using namespace log4cpp;

class Mylogger
{
public:
    static Mylogger *getInstance();
    static void destroy();

    /* template<typename ...Args> */    
    /* void warn(const char * msg, Args... args); */
    /* template<typename ...Args> */    
    /* void error(const char * msg); */
    /* void debug(const char * msg); */
    /* void info(const char * msg); */

template<typename ...Args>
void warn(const char * msg,Args... args)
{
    _mycat.warn(msg, args...);
}

template<typename ...Args>
void error(const char * msg,Args... args)
{
    _mycat.error(msg, args...);
}

template<typename ...Args>
void debug(const char * msg,Args... args)
{
    _mycat.debug(msg, args...);
}

template<typename ...Args>
void info(const char * msg,Args... args)
{
    _mycat.info(msg, args...);
}
private:
    Mylogger();
    ~Mylogger();
private:
    static Mylogger *_pInstance;
    Category &_mycat;
};


#define prefix(msg) (string(__FILE__) + string(":") \
                    + string(__FUNCTION__) + string(":") \
                    + string(std::to_string(__LINE__)) \
                    + string(":") + msg).c_str()

/* template<typename ...Args> */
/* #define logError(msg,Args... ) Mylogger::getInstance()->error(prefix(msg), Args... args) */
/* #define logError(msg, args...) Mylogger::getInstance()->error(prefix(msg)) */
/* #define logInfo(msg, args...) Mylogger::getInstance()->info(prefix(msg)) */
/* #define logDebug(msg, args...) Mylogger::getInstance()->debug(prefix(msg)) */
/* #define logWarn(msg, args...) Mylogger::getInstance()->warn(prefix(msg)) */

#endif

