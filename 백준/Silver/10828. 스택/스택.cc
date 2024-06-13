#include <iostream>
#include <cstring>
using namespace std;

class Node {
	int val;
	Node *prev;
public:
	Node() {}
	Node(int val) { this->val = val; }
	Node *getPrev(void) const { return prev; }
	int getVal(void) const { return val; }
	void setPrev(Node *prev);
};

class Stack {
	Node *top;
	int size;
public:
	Stack(void) {
		top = NULL;
		size = 0;
	}
	void push(int val);
	int pop(void);
	int peek(void) const;
	int isEmpty(void) const;
	int getSize(void) const;
	~Stack(void);
};

void Node::setPrev(Node *prev) {
	this->prev = prev;
}

void Stack::push(int val) {
	Node *p = new Node(val);
	p->setPrev(top);
	top = p;
	size++;
}

int Stack::pop(void) {
	if (top == NULL) {
		return -1;
	}

	Node *p = top;
	top = top->getPrev();
	int val = p->getVal();
	delete p;
	size--;

	return val;
}

int Stack::peek(void) const {
	if (top == NULL) {
		return -1;
	}

	return top->getVal();
}

int Stack::isEmpty(void) const {
	return top == NULL;
}

int Stack::getSize(void) const {
	return size;
}

Stack::~Stack(void) {
	Node *temp;
	while (top != NULL) {
		temp = top;
		top = top->getPrev();
		delete temp;
	}
}

int decimalize(const char *str) {
	int num = 0;
	while (*str) {
		if (*str >= '0' && *str <= '9') {
			num = 10 * num + *str - '0';
		}
		str++;
	}
	return num;
}

void sol(void) {
	Stack s;
	int n;
	char command[51];
	cin >> n;
	cin.ignore(1);
	for (int i = 0; i < n; i++) {
		cin.getline(command, 51);
		if (strcmp(command, "pop") == 0) {
			cout << s.pop() << endl;
		}
		else if (strcmp(command, "top") == 0) {
			cout << s.peek() << endl;
		}
		else if (strcmp(command, "empty") == 0) {
			cout << s.isEmpty() << endl;
		}
		else if (strcmp(command, "size") == 0) {
			cout << s.getSize() << endl;
		}
		else {
			s.push(::decimalize(command));
		}
	}

}

int main(void) {
	sol();

	return 0;
}