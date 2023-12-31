#include "../include/CacheManager.hpp"
CacheManager *CacheManager::_pInstance = nullptr;
CacheManager::CacheManager()
{
    _cachelist.reserve(4);
}
CacheManager::~CacheManager(){}
CacheManager *CacheManager::createInstance()
{
    if (_pInstance == nullptr)
    {
        _pInstance = new CacheManager();
    }
    return _pInstance;
}
void CacheManager::initcache(size_t idx, const string &filename)
{
    _cachelist[idx - 1]->readfromfile(filename);
}
LRUCache *CacheManager::getcache(size_t idx)
{
    return _cachelist[idx - 1];
}
void CacheManager::periodicupdatecaches()
{
    LRUCache *tmp = getcache(1);
    for (int idx = 1; idx < _cachelist.size(); ++idx)
    {
        tmp->update(_cachelist[idx]);
    }
    tmp->writetofile("../cache/cache.dat");
    for (auto &elem : _cachelist)
    {
        elem->readfromfile("../cache/cache.dat");
    }
}
