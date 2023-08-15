
#ifndef __MYLOGGER_TCC__
#define __MYLOGGER_TCC__
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/RollingFileAppender.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/PropertyConfigurator.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Category.hh"
#include<iostream>
#include<string>
#include<typeinfo>
using std::string;
mylog::Mylogger* mylog::Mylogger::_mylogger = &mylog::Mylogger::getInstance();
pthread_once_t mylog::Mylogger::_once_ctl = PTHREAD_ONCE_INIT;
void mylog::Mylogger::init(){
    _mylogger = new Mylogger();
    atexit(destroyInstance);
}
mylog::Mylogger& mylog::Mylogger::getInstance(){
    pthread_once(&_once_ctl,init);
    return *_mylogger;
}
void mylog::Mylogger::destroyInstance(){
    if(_mylogger!=nullptr){
        delete _mylogger;
        _mylogger = nullptr;
    }
}
void mylog::Mylogger::error(const char*msg){
    this->_cat.error(msg);
}
void mylog::Mylogger::info(const char*msg){
    this->_cat.info(msg);
}
void mylog::Mylogger::warn(const char*msg){
    this->_cat.warn(msg);
}
void mylog::Mylogger::debug(const char*msg){
    this->_cat.debug(msg);
}
mylog::Mylogger::~Mylogger(){
    log4cpp::Category::shutdown();
}
mylog::Mylogger::Mylogger()
:_cat(log4cpp::Category::getInstance("mylogger"))
{
    auto *layout1 = new log4cpp::PatternLayout();
    layout1->setConversionPattern("%d %c [%p] %m%n");
    auto *layout2 = new log4cpp::PatternLayout();
    layout2->setConversionPattern("%d %c [%p] %m%n");
    auto *osA =new log4cpp::OstreamAppender("console",&std::cout);
    osA->setLayout(layout1);
    auto *fileA= new log4cpp::FileAppender("mylogger","../log/loggerApp.log");
    fileA->setLayout(layout2);
    fileA->setThreshold(log4cpp::Priority::INFO);
    this->_cat.setPriority(log4cpp::Priority::DEBUG);
    this->_cat.addAppender(osA);
    this->_cat.addAppender(fileA);
}
template<class...Args>
void mylog::Mylogger::error(const char* fomat,const Args&...args){
    this->_cat.error(fomat,args...);
}
template<class...Args>
void mylog::Mylogger::info(const char* fomat,const Args&...args){
    this->_cat.info(fomat,args...);
}
template<class...Args>
void mylog::Mylogger::warn(const char* fomat,const Args&...args){
    this->_cat.warn(fomat,args...);
}
template<class...Args>
void mylog::Mylogger::debug(const char* fomat,const Args&...args){
    this->_cat.debug(fomat,args...);
}
#endif
