/**
 * Project Untitled
 */


#ifndef _SPLITTOOL_H
#define _SPLITTOOL_H
#include<vector>
#include<string>
#include"WordSegmentation.h"
class SplitTool {
public: 
    SplitTool(){}
    virtual ~SplitTool(){}
    virtual std::vector<std::string> cut(const std::string &sentence) =0;   
    virtual WordSegmentation& getWordSeg()=0;
};

#endif //_SPLITTOOL_H