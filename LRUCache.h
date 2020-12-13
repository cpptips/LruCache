#pragma once
#include <string.h>

#include <iostream>

template <class KEY, class VAL>
struct Entry {
   public:
    Entry(){};

    KEY k;
    VAL v;
    struct Entry* next = nullptr;
    struct Entry* prev = nullptr;
};

template <class KEY, class VAL>
class LRUCache {
    using Entry = Entry<KEY, VAL>;

   private:
    int _capacity;
    int _size;
    Entry* _head;
    Entry* _tail;
    void delete_entry(Entry* entry) {
        entry->prev->next = entry->next;
        entry->next->prev = entry->prev;
    }
    // 在头节点之后插入
    void add_entry(Entry* entry) {
        entry->next = _head->next;
        _head->next->prev = entry;
        _head->next = entry;
        entry->prev = _head;
    }

   public:
    LRUCache(int capacity = 24) {
        _capacity = capacity;
        _size = 0;
        _head = new Entry();
        _tail = new Entry();
        _head->next = _tail;
        _head->prev = nullptr;
        _tail->prev = _head;
        _tail->next = nullptr;
    }
    ~LRUCache() {
        Entry* p = _head->next;
        while (p) {
            delete p->prev;
            p = p->next;
        }

        delete _tail;
    }

    int get(KEY key) {
        Entry* p = _head->next;
        while (p->next) {
            if (p->k == key) {  //访问一次之后，把节点放在头部
                delete_entry(p);
                add_entry(p);
                return p->v;
            }
            p = p->next;
        }
        return -1;
    }
    bool set(KEY key, VAL value) {
        Entry* p = _head->next;
        while (p->next) {
            // 链表已经有了
            if (p->k == key) {
                p->v = value;
                return true;
            }
            p = p->next;
        }

        // 空间不够，要释放了
        if (_size >= _capacity) {
            p = _tail->prev->prev;
            delete p->next;
            p->next = _tail;
            _tail->prev = p;
        }

        // 新插入
        p = new Entry();
        p->k = key;
        p->v = value;
        add_entry(p);
        _size++;
        return true;
    }
    void dump() {
        Entry* p = _head->next;
        while (p->next) {
            std::cout << "Key: " << p->k << "Value: " << p->v << std::endl;
            p = p->next;
        }
    }
};
