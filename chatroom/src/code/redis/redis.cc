#include "redis.hpp"

int main(){
    Redis *redis = new Redis();
    // redis->del("key:name");
     redis -> hset("gust", 273270, "sdjiadhjkas");
    delete redis;//释放资源
    return 0;
}