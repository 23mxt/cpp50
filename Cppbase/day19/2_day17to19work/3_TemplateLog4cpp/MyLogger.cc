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
: _mycat(log4cpp::Category::getRoot().getInstance("MyCat"))
{
	using namespace log4cpp;

	cout << "Mylogger()" << endl;

    //日志的格式
	PatternLayout * ppl1 = new PatternLayout();
	ppl1->setConversionPattern("%d %c [%p] %m%n");

	PatternLayout * ppl2 = new PatternLayout();
	ppl2->setConversionPattern("%d %c [%p] %m%n");

    //日志的目的地
	OstreamAppender *poa = new OstreamAppender("OstreamAppender", &cout);
	poa->setLayout(ppl1);

	FileAppender *pfa = new FileAppender("FileAppender", "wd.log");
	pfa->setLayout(ppl2);

    //添加日志目的地到Category
	_mycat.addAppender(poa);
	_mycat.addAppender(pfa);

    //日志的优先级
	_mycat.setPriority(log4cpp::Priority::DEBUG);
}

Mylogger::~Mylogger()
{
	cout << "~Mylogger()" << endl;
	log4cpp::Category::shutdown();
}

void Mylogger::warn(const char *msg)
{
	_mycat.warn(msg);
}

void Mylogger::error(const char *msg)
{
	_mycat.error(msg);
}

void Mylogger::info(const char *msg)
{
	_mycat.info(msg);
}

void Mylogger::debug(const char *msg)
{
	_mycat.debug(msg);
}

void Mylogger::setPriority(Priority p)
{
    switch(p)
	{
    case WARN:
		_mycat.setPriority(log4cpp::Priority::WARN);
		break;
	case ERROR:
		_mycat.setPriority(log4cpp::Priority::ERROR);
		break;
	case INFO:
		_mycat.setPriority(log4cpp::Priority::INFO);
		break;
	case DEBUG:
		_mycat.setPriority(log4cpp::Priority::DEBUG);
		break;
	}
}


