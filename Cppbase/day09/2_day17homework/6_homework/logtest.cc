#include "MyLogger.h"
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

void test() 
{
	int number = 100;
	const char *pstr = "hello, log4cpp";
    int number2 = 200;
    const char *pstr2 = "really";
	/* string pstr = "hello, log4cpp"; */
	/* logInfo("This is an info message. number = %d, str = %s\n", number, pstr); */
	/* logError("This is an error message. number = %d, str = %s\n", number, pstr); */
	/* logWarn("This is a warn message. number = %d, str = %s\n", number, pstr); */
	/* logDebug("This is a debug message. number = %d, str = %s\n", number, pstr); */
    Mylogger::getInstance()->warn("This is an info message.number = %d, str = %s, number2 = %d, pstr2 = %s\n", number, pstr, number2, pstr2);
    Mylogger::getInstance()->error("This is an error message.number = %d, str = %s\n", number, pstr);
}

int main() {
    test();
    return 0;
}

