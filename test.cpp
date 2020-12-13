#include <string>

#include "LRUCache.h"
int main(int argc, char const* argv[]) {
    LRUCache<int, int>* pcache = new LRUCache<int, int>(3);
    pcache->set(1, 999);
    pcache->set(2, 233);
    pcache->set(1, 888);
    // pcache->set(4, 666);  // 将会替换掉 （1，999）
    pcache->dump();
    delete pcache;

    LRUCache<int, std::string>* pcache1 = new LRUCache<int, std::string>(3);
    pcache1->set(1, "999");
    pcache1->set(2, "233");
    pcache1->set(1, "888");
    pcache1->set(4, "666");  // 将会替换掉 （1，999）
    pcache1->dump();
    delete pcache1;

    return 0;
}

/* outputs
PS E:\4 Code\demo_cpp\LRUCache> .\LRUCache.exe
Key: 4Value: 666
Key: 3Value: 888
Key: 2Value: 233
*/