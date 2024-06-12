#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Node
{
    int val;
    int idx;
    Node* next;
    Node* prev;

    ~Node()
    {
        if (next)
        {
            next->prev = nullptr;
            delete next;
            next = nullptr;
        }

        if (prev)
        {
            prev->next = nullptr;
            delete prev;
            prev = nullptr;
        }
    }
};

struct DQ
{
    Node* head;
    Node* tail;

    DQ()
    {
        head = new Node{};
        tail = new Node{};

        head->val = -1;
        head->idx = -1;
        head->next = tail;
        head->prev = nullptr;

        tail->val = -1;
        tail->idx = -1;
        tail->next = nullptr;
        tail->prev = head;
    }

    ~DQ()
    {
        delete head;
    }

    Node* front() const
    {
        if (empty())
        {
            return nullptr;
        }

        return head->next;
    }

    Node* back() const
    {
        if (empty())
        {
            return nullptr;
        }

        return tail->prev;
    }

    bool empty() const
    {
        return head->next == tail && tail->prev == head;
    }

    void push_back(int val, int idx)
    {
        Node* new_node = new Node{ val, idx, tail, tail->prev };

        tail->prev = new_node;
        new_node->prev->next = new_node;
    }

    void pop_front()
    {
        if (empty())
        {
            return;
        }

        Node* target = head->next;

        head->next = target->next;
        head->next->prev = head;

        target->next = target->prev = nullptr;
        delete target;
    }

    void pop_back()
    {
        if (empty())
        {
            return;
        }

        Node* target = tail->prev;

        tail->prev = target->prev;
        tail->prev->next = tail;

        target->next = target->prev = nullptr;
        delete target;
    }
};

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    DQ dq;

    int N, L;
    std::cin >> N >> L;
    for (register int i = 1; i <= N; i++)
    {
        int val;
        std::cin >> val;

        while (!dq.empty() && dq.back()->val > val)
        {
            dq.pop_back();
        }

        dq.push_back(val, i);

        while (dq.front()->idx < i - L + 1)
        {
            dq.pop_front();
        }

        std::cout << dq.front()->val << ' ';
    }

    return 0;
}