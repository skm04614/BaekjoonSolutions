#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using ull = unsigned long long;

struct Element
{
    char name[21];
    Element* next;

    Element() : name{}, next{}
    {
    }

    ~Element()
    {
        if (next)
        {
            delete next;
        }
    }

    Element& operator=(const Element& other)
    {
        char* ptr = name;
        const char* ptr2 = other.name;
        while (*ptr++ = *ptr2++);
        return *this;
    }

    Element(const char* name) : Element{}
    {
        char* ptr = this->name;
        while (*ptr++ = *name++);
    }

    int cmp(const Element& other) const
    {
        const char* ptr1 = name;
        const char* ptr2 = other.name;
        while (*ptr1 && *ptr2 && *ptr1 == *ptr2)
        {
            ptr1++;
            ptr2++;
        }

        if (*ptr1 == 0 && *ptr2 == 0)
        {
            return 0;
        }

        return *ptr1 > *ptr2 ? 1 : -1;
    }
};

struct HashMap
{
    constexpr static int SIZE = 50021;
    
    Element* pool[SIZE];

    HashMap() : pool{}
    {
    }

    ~HashMap()
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (pool[i])
            {
                delete pool[i];
            }
        }
    }

    void insert(const char* name)
    {
        ull hash = djb2_hash(name);

        Element* e = new Element{ name };
        if (pool[hash] == nullptr)
        {
            pool[hash] = e;
        }
        else
        {
            for (Element* current = pool[hash]; ; current = current->next)
            {
                if (current->cmp(*e) == 0)
                {
                    delete e;
                    break;
                }

                if (current->next == nullptr)
                {
                    current->next = e;
                    break;
                }
            }
        }
    }

    Element* get(const char* name)
    {
        Element e{ name };
        ull hash = djb2_hash(name);

        for (Element* current = pool[hash]; current; current = current->next)
        {
            if (current->cmp(e) == 0)
            {
                return current;
            }
        }

        return nullptr;
    }

private:
    ull djb2_hash(const char* name)
    {
        ull hash = 5381;
        while (*name)
        {
            hash = ((hash << 5) + hash + *name++) % SIZE;
        }
        return hash;
    }
};

HashMap MAP;

Element ARR[500500];
int K;

void swap(Element& e1, Element& e2)
{
    Element tmp = e1;
    e1 = e2;
    e2 = tmp;
}

void _qsort(Element* arr, int idx0, int idx1)
{
    if (idx0 >= idx1)
    {
        return;
    }

    int pivot = idx0;
    int left = pivot + 1;
    int right = idx1;
    for (;;)
    {
        while (left <= right && arr[left].cmp(arr[pivot]) != 1)
        {
            left++;
        }

        while (left <= right && arr[right].cmp(arr[pivot]) != -1)
        {
            right--;
        }

        if (left > right)
        {
            swap(arr[pivot], arr[right]);
            break;
        }
        
        swap(arr[left], arr[right]);
    }

    _qsort(arr, idx0, right - 1);
    _qsort(arr, right + 1, idx1);
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    char buf[21];
    int N, M;
    std::cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        std::cin >> buf;
        MAP.insert(buf);
    }

    for (int i = 0; i < M; i++)
    {
        std::cin >> buf;
        Element* e = MAP.get(buf);
        if (e)
        {
            ARR[K++] = *e;
        }
    }
    std::cout << K << '\n';
    _qsort(ARR, 0, K - 1);
    for (int i = 0; i < K; i++)
    {
        std::cout << ARR[i].name << '\n';
    }

    return 0;
}