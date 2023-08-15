#include "../include/SplitToolCppjieba.hpp"
#include"../include/WordSegmentation.h"
#include<sstream>
SplitToolCppjieba::SplitToolCppjieba()
{
}
SplitToolCppjieba::~SplitToolCppjieba(){

}
std::vector<std::string> SplitToolCppjieba::cut(const std::string &sentence){
    std::vector<std::string> results;
    if(sentence[0]&1<<7){
        results = _wordSeg(sentence);
    }else{
        std::stringstream ss(sentence);
        while(!ss.eof()){
            std::string word;
            ss>>word;
            results.push_back(word);
        }
    }
    return results;
}
