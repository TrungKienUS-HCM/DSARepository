#include <iostream>
#include <fstream>
using namespace std;

struct NODE
{
	int key;
	NODE* p_next;
};

struct Stack
{
	NODE* top;
};

NODE* createNode(int key)
{
	NODE* newNode = new NODE;
	newNode->key = key;
	newNode->p_next = NULL;
	return newNode;
}

Stack* initializeStack();
void stackPush(Stack& s, int key);
int stackPop(Stack& s);
int size(Stack s);
bool isEmpty(Stack s);
void printStack(Stack s, ostream& os);
void freeStack(Stack& s);

Stack* initializeStack()
{
	Stack* newSt = new Stack;
	newSt->top = NULL;
	return newSt;
}

void stackPush(Stack& s, int key)
{
	NODE* newTop = createNode(key);
	if (!isEmpty(s))
	{
		newTop->p_next = s.top;
	}
	s.top = newTop;
}

int stackPop(Stack& s)
{
	if (isEmpty(s)) return -1;

	NODE* oldTop = s.top;
	s.top = s.top->p_next;
	int top = oldTop->key;
	delete oldTop;
	return top;
}

int size(Stack s)
{
	int cnt = 0;
	for (NODE* pCount = s.top; pCount; pCount = pCount->p_next)
	{
		++cnt;
	}
	return cnt;
}

bool isEmpty(Stack s)
{
	return !s.top;
}

void printStack(Stack s, ostream& os)
{
	if (isEmpty(s))
	{
		os << "EMPTY" << endl;
		return;
	}
	for (NODE* pRun = s.top; pRun; pRun = pRun->p_next)
	{
		os << pRun->key << ' ';
	}
	os << endl;
}

void freeStack(Stack& s)
{
	while (!isEmpty(s))
	{
		stackPop(s);
	}
}

int main()
{
	ifstream readOrders("input.txt");
	ofstream printResult("output.txt");
	string getOrders;
	Stack newSt;
	while (readOrders >> getOrders)
	{
		if (getOrders == "init")
		{
			newSt = *initializeStack();
		}
		else if (getOrders == "push")
		{
			int push;
			readOrders >> push;
			stackPush(newSt, push);
		}
		else if (getOrders == "pop")
		{
			stackPop(newSt);
		}
		printStack(newSt, printResult);
	}
	freeStack(newSt);
	readOrders.close();
	printResult.close();
	return 0;
}