//
// Created by Vacant lot on 2025/4/15.
//

#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <vector>
#include <random>
#include <ctime>
using namespace std;
constexpr int MAX_LEVEL = 10;
constexpr double P_FACTOR = 0.5;

template<typename T>
struct SkiplistNode {
    T val;
    std::vector<SkiplistNode *> forward;

    SkiplistNode() = default;

    explicit SkiplistNode(T val, int maxLevel = MAX_LEVEL)
        : val(val), forward(maxLevel, nullptr) {
    }
};

template<typename T>
class Skiplist {
public:
    // 此处new SkiplistNode<T>(-1)，会根据模板参数，进行类型转换，但是不通用
    Skiplist() : head(new SkiplistNode<T>(T{})), level(0), e(time(nullptr)), u(0, 1) {
    }

    ~Skiplist() {
        SkiplistNode<T>* node = head;
        while (node) {
            SkiplistNode<T>* next = node->forward[0];
            delete node;
            node = next;
        }
    }

    bool search(T target) {
        SkiplistNode<T> *cur = this->head;
        // 从最高层开始往下找
        for (int i = level - 1; i >= 0; i--) {
            while (cur->forward[i] && cur->forward[i]->val < target) {
                cur = cur->forward[i];
            }
        }
        cur = cur->forward[0];
        if (cur && cur->val == target)
            return true;
        return false;
    }

    void add(T num) {
        // 记录每一层最后的元素
        vector<SkiplistNode<T> *> update(MAX_LEVEL, head);
        SkiplistNode<T> *cur = this->head;
        for (int i = level - 1; i >= 0; i--) {
            while (cur->forward[i] && cur->forward[i]->val < num) {
                cur = cur->forward[i];
            }
            // 最后一个元素的前一个，值肯定小于num
            update[i] = cur;
        }
        int lv = random_Level();
        level = max(level, lv);
        SkiplistNode<T> *newNode = new SkiplistNode(num, lv);
        for (int i = 0; i < lv; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    int random_Level() {
        int lv = 1;
        while (u(e) < P_FACTOR && lv < MAX_LEVEL) {
            lv++;
        }
        return lv;
    }

private:
    SkiplistNode<T> *head;
    int level;

    default_random_engine e;

    std::uniform_real_distribution<double> u;
};


#endif //SKIPLIST_H
