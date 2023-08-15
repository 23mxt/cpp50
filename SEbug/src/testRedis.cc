#include <iostream>
#include <string>
#include <sw/redis++/redis++.h>

using std::cout;
using std::endl;
using std::string;
using namespace sw::redis;

class MyRedis{
    public:
        MyRedis() : _redis(Redis("tcp://127.0.0.1:6379"))
       { cout << "MyRedis is ok" << endl; }
    
        string findstr(const string& str){
            //查看redis内是否有缓存
            //如果有就原样返回，没有就返回空
            _key = str;
            _redis.set("key", "val");
            auto optionalValue = _redis.get("key");
            if(optionalValue){
                //有，原样返回                                           
                return *optionalValue;
            }
            //没有去内存读取
            else {
               return "";
            }
        }
    
        void store(const string& value){
            //key是查询内容，value是服务器提供的结果
            _redis.set(_key, value);
        }
    
    private:
        string _key;//存传过来的key值
        Redis _redis;//Redis连接后的返回值
    };
    
int main()
{
    /* MyRedis myRedis; */
    /* string sub = "333"; */
    /* cout << (myRedis.findstr(sub)) << endl; */
    auto redis = Redis("tcp://127.0.0.1:6379");
    redis.set("key","123");
    auto val = redis.get("key");
    cout << *val << endl;
    return 0;
}
