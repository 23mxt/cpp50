#ifndef __CacheManager_H__
#define __CacheManager_H__
#include "LRUCache.hpp"
#include <vector>
class CacheManager
{
    friend class Thread;
public:
    static CacheManager* createInstance();
    void initcache(size_t,const string&);
    LRUCache* getcache(size_t);
    void periodicupdatecaches();
private:
    CacheManager();
    ~CacheManager();
private:
    static CacheManager* _pInstance;
    vector<LRUCache*> _cachelist;
};
#endif