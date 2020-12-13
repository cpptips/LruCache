#include "LRUCache.h"

int main(int argc, char const* argv[]) {
    LRUCache* pcache = new LRUCache(3);
    pcache->set(1, 999);
    pcache->set(2, 233);
    pcache->set(3, 888);
    pcache->set(4, 666);  // 将会替换掉 （1，999）

    pcache->dump();
    delete pcache;
    return 0;
}

/* outputs
PS E:\4 Code\demo_cpp\LRUCache> .\LRUCache.exe
Key: 4Value: 666
Key: 3Value: 888
Key: 2Value: 233
*/