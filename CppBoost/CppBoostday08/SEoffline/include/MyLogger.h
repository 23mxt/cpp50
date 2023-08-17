#ifndef __MYLOGGER_H__
#define __MYLOGGER_H__

#include <log4cpp/Category.hh>
#include <string>

using std::string;

class Mylogger
{
public:
	enum Priority
    {
		ERROR = 300,
		WARN,   //301
		INFO,   //值越大，优先级越低
		DEBUG
	};

	static Mylogger * getInstance();
	static void destroy();

	template <class... Args>
	void warn(const char * msg, Args... args)
	{
		_mySElog.warn(msg, args...);
	}

	template <class... Args>
	void error(const char * msg, Args... args)
	{
		_mySElog.error(msg, args...);
	}

	template <class... Args>
	void info(const char * msg, Args... args)
	{
		_mySElog.info(msg, args...);
	}

	template <class... Args>
	void debug(const char * msg, Args... args)
	{
		_mySElog.debug(msg, args...);
	}

	void warn(const char * msg);    //SE的结果可能有问题的地方，warn 
	void error(const char * msg);   //搜索引擎打开文件失败等，error一下
	void info(const char * msg);    //搜索引擎每执行完一个指令，记录
	void debug(const char * msg);   //搜索引擎调试问题用

	void setPriority(Priority p);
private:
	Mylogger();
	~Mylogger();
private:
	static Mylogger * _pInstance;
	log4cpp::Category & _mySElog;
};

#define prefix(msg) string("[")\
	.append(__FILE__).append(":")\
	.append(__FUNCTION__).append(":")\
	.append(std::to_string(__LINE__)).append("] ")\
	.append(msg).c_str()

/* __VA_ARGS__表示可变参数，是C、C++的预定义宏 */ 
//##__VA_ARGS__ 宏前面加上##的作用在于，当可变参数的个数为0时，
//这里的##起到把前面多余的","去掉的作用,否则会编译出错
/* #define LogError(msg) Mylogger::getInstance()->error(prefix(msg)) */
//这里的...表示参数的形态
#define LogError(msg, ...) Mylogger::getInstance()->error(prefix(msg), ##__VA_ARGS__)
#define LogWarn(msg, ...) Mylogger::getInstance()->warn(prefix(msg), ##__VA_ARGS__)
#define LogInfo(msg, ...) Mylogger::getInstance()->info(prefix(msg), ##__VA_ARGS__)
#define LogDebug(msg, ...) Mylogger::getInstance()->debug(prefix(msg), ##__VA_ARGS__)

#endif

