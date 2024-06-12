#include <cstdio>

struct Node
{
	int val;
	Node* next;
	Node* prev;
	Node(int val = 0, Node* next = nullptr, Node *prev = nullptr) :
		val(val), next(next), prev(prev) {}
	~Node() = default;
};

Node HEAD{};
Node TAIL{};
Node* PTAIL = &TAIL;
Node* PHEAD = &HEAD;
int SIZE = 0;

bool streq(const char* s1, const char* s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return *s1 == *s2 && *s1 == '\0';
}


int main(void)
{
	PHEAD->next = PTAIL;
	PTAIL->prev = PHEAD;

	int N = 0;
	int val = 0;
	char buf[10] = {};
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%s", buf);
		if (streq(buf, "push"))
		{
			scanf("%d", &val);
			PTAIL->prev = new Node(val, PTAIL, PTAIL->prev);
			PTAIL->prev->prev->next = PTAIL->prev;
			SIZE++;
		}
		else if (streq(buf, "pop"))
		{
			if (PHEAD->next == PTAIL)
			{
				printf("-1\n");
			}
			else
			{
				Node* pop = PHEAD->next;
				PHEAD->next = pop->next;
				pop->next->prev = PHEAD;
				SIZE--;
				printf("%d\n", pop->val);
				delete pop;
			}
		}
		else if (streq(buf, "front"))
		{
			printf("%d\n", PHEAD->next == PTAIL ? -1 : PHEAD->next->val);
		}
		else if (streq(buf, "back"))
		{
			printf("%d\n", PTAIL->prev == PHEAD ? -1 : PTAIL->prev->val);
		}
		else if (streq(buf, "size"))
		{
			printf("%d\n", SIZE);
		}
		else if (streq(buf, "empty"))
		{
			printf("%d\n", SIZE == 0);
		}
	}

	while (PHEAD->next != PTAIL)
	{
		Node* pop = PHEAD->next;
		PHEAD->next = pop->next;
		pop->next->prev = PHEAD;
		SIZE--;
		delete pop;
	}

	return 0;
}