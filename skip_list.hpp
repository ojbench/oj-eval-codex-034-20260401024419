// Skip list implementation per assignment template
#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <random>

template<typename T>
class SkipList {
private:
    struct Node {
        T value;
        std::vector<Node*> forward;
        Node(int level, const T& val) : value(val), forward(level, nullptr) {}
    };

    int maxLevel;
    double p;
    int level;
    Node* header;
    std::mt19937_64 rng;
    std::uniform_real_distribution<double> dist;

    int randomLevel() {
        int lvl = 1;
        while (dist(rng) < p && lvl < maxLevel) ++lvl;
        return lvl;
    }

    void clear() {
        Node* cur = header->forward[0];
        while (cur) {
            Node* next = cur->forward[0];
            delete cur;
            cur = next;
        }
        std::fill(header->forward.begin(), header->forward.end(), nullptr);
        level = 1;
    }

public:
    SkipList()
        : maxLevel(32), p(0.5), level(1), header(nullptr), rng(std::random_device{}()), dist(0.0, 1.0) {
        // Create a header node with dummy value; it won't be used
        header = new Node(maxLevel, T());
    }

    ~SkipList() {
        clear();
        delete header;
    }

    void insert(const T & item) {
        std::vector<Node*> update(maxLevel, nullptr);
        Node* x = header;
        for (int i = level - 1; i >= 0; --i) {
            while (x->forward[i] && x->forward[i]->value < item) {
                x = x->forward[i];
            }
            update[i] = x;
        }

        x = x->forward[0];
        if (x && !(item < x->value) && !(x->value < item)) {
            // already exists
            return;
        }

        int rl = randomLevel();
        if (rl > level) {
            for (int i = level; i < rl; ++i) update[i] = header;
            level = rl;
        }
        Node* n = new Node(rl, item);
        for (int i = 0; i < rl; ++i) {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
    }

    bool search(const T & item) {
        Node* x = header;
        for (int i = level - 1; i >= 0; --i) {
            while (x->forward[i] && x->forward[i]->value < item) {
                x = x->forward[i];
            }
        }
        x = x->forward[0];
        if (x && !(item < x->value) && !(x->value < item)) return true;
        return false;
    }

    void deleteItem(const T & item) {
        std::vector<Node*> update(maxLevel, nullptr);
        Node* x = header;
        for (int i = level - 1; i >= 0; --i) {
            while (x->forward[i] && x->forward[i]->value < item) {
                x = x->forward[i];
            }
            update[i] = x;
        }
        x = x->forward[0];
        if (!x || (item < x->value) || (x->value < item)) return;
        int nodeLevel = static_cast<int>(x->forward.size());
        for (int i = 0; i < nodeLevel; ++i) {
            if (update[i]->forward[i] == x) update[i]->forward[i] = x->forward[i];
        }
        delete x;
        while (level > 1 && header->forward[level - 1] == nullptr) --level;
    }
};

#endif

