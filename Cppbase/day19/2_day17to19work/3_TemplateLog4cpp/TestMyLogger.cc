#include "MyLogger.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

using std::string;

void test()
{
    //优先级设置的是DEBUG
	Mylogger::getInstance()->error(prefix("this is an error message!"));
	Mylogger::getInstance()->warn("this is a warn message!");
	Mylogger::getInstance()->info("this is an info message!");
	Mylogger::getInstance()->debug("this is a debug message!");
	cout << "Mylogger::Priority::WARN = " << Mylogger::Priority::WARN << endl;
	cout << "Mylogger::Priority::ERROR = " << Mylogger::Priority::ERROR << endl;
	cout << "Mylogger::Priority::INFO = " << Mylogger::Priority::INFO << endl;
	cout << "Mylogger::Priority::DEBUG = " << Mylogger::Priority::DEBUG << endl;

    LogInfo("hello", "world");

	Mylogger::getInstance()->setPriority(Mylogger::Priority::WARN);
	Mylogger::getInstance()->error(prefix("this is an error message!"));
	Mylogger::getInstance()->warn("this is a warn message!");
	Mylogger::getInstance()->info("this is an info message!");
	Mylogger::getInstance()->debug("this is a debug message!");
	cout << "Mylogger::Priority::WARN = " << Mylogger::Priority::WARN << endl;
	cout << "Mylogger::Priority::ERROR = " << Mylogger::Priority::ERROR << endl;
	cout << "Mylogger::Priority::INFO = " << Mylogger::Priority::INFO << endl;
	cout << "Mylogger::Priority::DEBUG = " << Mylogger::Priority::DEBUG << endl;
}

void test2()
{
	cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << endl;
}

void test3()
{
	LogError("this is an error message! ");
	LogWarn("this is a warn message!");
	LogInfo("this is a info message!");
	LogDebug("this is a debug message!");
}

void test4()
{
	int number = 10;
	const char * pstr = "hello,world";
	Mylogger::getInstance()->debug(prefix("this is a error message! number = %d, str = %s"), number, pstr);
	/* LogError("this is a error message! number = %d, str = %s", number, pstr); */
	/* LogWarn("this is a error message!"); */
	/* LogInfo("this is a error message!"); */
	/* LogDebug("this is a error message!"); */

    /* printf("hello,world %d%s\n", number, pstr); */

    LogError("hello, world, %d,%p %s %d\n",
             number, &number, pstr, number);
    LogWarn("hello, world, %d,%p %s %d\n",
             number, &number, pstr, number);
    LogInfo("hello, world, %d,%p %s %d\n",
             number, &number, pstr, number);
}

int main(int argc, char **argv)
{
    /* test(); */
	test4();
	/* test2(); */
	/* test3(); */

	return 0;
}

