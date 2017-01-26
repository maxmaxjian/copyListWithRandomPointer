#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <ctime>

struct ListNode {
    int val;
    std::shared_ptr<ListNode> next;
    std::shared_ptr<ListNode> jump;

    ListNode(int v, const std::shared_ptr<ListNode> & nx=nullptr) : val(v), next(nx), jump(nullptr)
    {}
};

using pNode = std::shared_ptr<ListNode>;

pNode nodeAt(const pNode & head, int n) {
    pNode p = head;
    int count = 0;
    while (count < n) {
        p = p->next;
        count++;
    }
    return p;
}

pNode createList(const std::vector<int> & nums) {
    srand(time(NULL));
    pNode head = nullptr;
    std::for_each(nums.rbegin(), nums.rend(), [&](int i){head = std::make_shared<ListNode>(i,head);});
    pNode p = head;
    while (p != nullptr) {
        int idx = rand()%nums.size();
        p->jump = nodeAt(head, idx);
        p = p->next;
    }
    return head;
}

int getLength(const pNode & head) {
    int count = 0;
    pNode p = head;
    while (p != nullptr) {
        count++;
        p = p->next;
    }
    return count;
}

void printNext(const pNode & head) {
    if (head != nullptr) {
        std::cout << head->val << " -> ";
        printNext(head->next);
    }
    else {
        std::cout << "null" << std::endl;
    }
}

void printRandom(const pNode & head) {
    pNode p = head;
    while (p != nullptr) {
        std::cout << p->val << " -> jump = ";
        if (p->jump != nullptr)
            std::cout << p->jump->val << std::endl;
        else
            std::cout << "null" << std::endl;
        p = p->next;
    }
}

class solution {
  public:
    pNode deepCopy(const pNode & head) {
        // copy each node
        pNode p = head;
        while (p != nullptr) {
            pNode cpy = std::make_shared<ListNode>(p->val,p->next);
            p->next = cpy;
            p = cpy->next;
        }
        // printNext(head);
        // printRandom(head);
        // set the jump pointer of each copied node
        p = head;
        while (p != nullptr) {
            p->next->jump = p->jump->next;
            p = p->next->next;
        }
        printNext(head);
        printRandom(head);
        // split these two interleaved lists
        pNode newhead, newp;
        p = head;
        newhead = head->next;
        while (p != nullptr) {
            newp = p->next;
            p->next = newp->next;
            if (p->next != nullptr)
                newp->next = p->next->next;
            p = p->next;
        }
        // printNext(head);
        // printNext(newhead);
        
        return newhead;
    }
};

int main() {
    std::vector<int> nums{1,2,3,4,5};
    pNode list = createList(nums);
    printNext(list);
    printRandom(list);

    std::cout << "After copying:\n";
    solution soln;
    pNode cpy = soln.deepCopy(list);
    printNext(cpy);
    printRandom(cpy);
}


