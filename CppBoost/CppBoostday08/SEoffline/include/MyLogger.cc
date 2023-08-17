#include "MyLogger.h"
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>

#include <iostream>
using std::cout;
using std::endl;

Mylogger * Mylogger::_pInstance = nullptr;

Mylogger * Mylogger::getInstance()
{
    cout << "getInstance" << endl;
	if(nullptr == _pInstance)
    {
		_pInstance = new Mylogger();
	}

	return _pInstance;
}

void Mylogger::destroy()
{
    cout << "destroy" << endl;
	if(_pInstance)
    {
		delete _pInstance;
        _pInstance = nullptr;
	}
}

Mylogger::Mylogger()
: _mySElog(log4cpp::Category::getRoot().getInstance("_mySElog"))
{
	using namespace log4cpp;

	cout << "Mylogger()" << endl;

    //日志的格式

	PatternLayout * ppl2 = new PatternLayout();
	ppl2->setConversionPattern("%d %c [%p] %m%n");

    //日志的目的地

	FileAppender *pfa = new FileAppender("FileAppender", "mySE.log");
	pfa->setLayout(ppl2);

    //添加日志目的地到Category
	_mySElog.addAppender(pfa);

    //日志的优先级
    //未完成时，调试信息也要记录
	_mySElog.setPriority(log4cpp::Priority::DEBUG);
}

Mylogger::~Mylogger()
{
	cout << "~Mylogger()" << endl;
	log4cpp::Category::shutdown();
}

void Mylogger::warn(const char *msg)
{
	_mySElog.warn(msg);
}

void Mylogger::error(const char *msg)
{
	_mySElog.error(msg);
}

void Mylogger::info(const char *msg)
{
	_mySElog.info(msg);
}

void Mylogger::debug(const char *msg)
{
	_mySElog.debug(msg);
}

void Mylogger::setPriority(Priority p)
{
    switch(p)
	{
    case WARN:
		_mySElog.setPriority(log4cpp::Priority::WARN);
		break;
	case ERROR:
		_mySElog.setPriority(log4cpp::Priority::ERROR);
		break;
	case INFO:
		_mySElog.setPriority(log4cpp::Priority::INFO);
		break;
	case DEBUG:
		_mySElog.setPriority(log4cpp::Priority::DEBUG);
		break;
	}
}


