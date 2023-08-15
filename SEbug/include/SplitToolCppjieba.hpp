#ifndef __CPPJIEBA_HPP__
#define __CPPJIEBA_HPP__
#include "SplitTool.hpp"
#include "WordSegmentation.h"
class SplitToolCppjieba:public SplitTool{
public:
    SplitToolCppjieba();
    ~SplitToolCppjieba();
    std::vector<std::string> cut(const std::string &sentence);
    WordSegmentation& getWordSeg(){
        return _wordSeg;
    }
private:
    WordSegmentation _wordSeg;
};
#endif