#pragma once
#include <string.h>

#include <iostream>
#include <unordered_set>

template <class KEY, class VAL>
struct Entry {
   public:
    Entry(){};
    Entry(KEY key) : k(key){};
    KEY k;
    VAL v;
    struct Entry* next = nullptr;
    struct Entry* prev = nullptr;
    inline KEY key() { return k; }
};

template <class KEY, class VAL>
class LRUCache {
    using EntryPtr = Entry<KEY, VAL>*;
    // using Entry = Entry<KEY, VAL>;
    struct Hash {
        size_t operator()(const EntryPtr& x) const {
            return std::hash<int>()(x->key());
        }
    };

    struct Equal {
        bool operator()(const EntryPtr& x, const EntryPtr& y) const {
            return x->key() == y->key();
        }
    };

    using EntryMap = std::unordered_set<EntryPtr, Hash, Equal>;

   private:
    int _capacity;
    int _size;
    EntryPtr _head;
    EntryPtr _tail;
    EntryMap _entriy_map;
    void delete_entry(EntryPtr entry) {
        entry->prev->next = entry->next;
        entry->next->prev = entry->prev;
        _entriy_map.erase(entry);
    }
    // 在头节点之后插入
    void add_entry(EntryPtr entry) {
        entry->next = _head->next;
        _head->next->prev = entry;
        _head->next = entry;
        entry->prev = _head;
        _entriy_map.insert(entry);
    }

   public:
    LRUCache(int capacity = 24) {
        _capacity = capacity;
        _size = 0;
        _head = new Entry<KEY, VAL>();
        _tail = new Entry<KEY, VAL>();
        _head->next = _tail;
        _head->prev = nullptr;
        _tail->prev = _head;
        _tail->next = nullptr;
    }
    ~LRUCache() {
        EntryPtr p = _head->next;
        while (p) {
            delete p->prev;
            p = p->next;
        }

        delete _tail;
    }

    int get(KEY key) {
        // 通过hashtable来查找
        auto it = _entriy_map.find(new Entry<KEY, VAL>(key));
        if (it == _entriy_map.end()) {
            return -1;
        }
        EntryPtr p = *it;
        delete_entry(p);
        add_entry(p);
        return p->v;
    }
    bool set(KEY key, VAL value) {
        EntryPtr p = new Entry<KEY, VAL>(key);
        auto it = _entriy_map.find(p);
        if (it != _entriy_map.end()) {  // cache hit
            (*it)->v = value;
            return true;
        }

        // 空间不够，要释放了
        if (_size >= _capacity) {
            p = _tail->prev->prev;
            delete p->next;
            p->next = _tail;
            _tail->prev = p;
            _size--;
        }

        // 新插入
        p->v = value;
        add_entry(p);
        _size++;
        return true;
    }
    void dump() {
        EntryPtr p = _head->next;
        while (p->next) {
            std::cout << "Key: " << p->k << "Value: " << p->v << std::endl;
            p = p->next;
        }
    }
};
