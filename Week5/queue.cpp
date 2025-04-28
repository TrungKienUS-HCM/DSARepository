#include <iostream>
#include <fstream>
using namespace std;

struct NODE
{
	int key;
	NODE* p_next;
};

struct Queue
{
	NODE* head;
	NODE* tail;
};

NODE* createNode(int key)
{
	NODE* newNode = new NODE;
	newNode->key = key;
	newNode->p_next = NULL;
	return newNode;
}

Queue* initializeQueue();
void enqueue(Queue& q, int key);
int dequeue(Queue& q);
int size(Queue q);
bool isEmpty(Queue q);
void printQueue(Queue q, ostream& os);
void freeQueue(Queue& q);


Queue* initializeQueue()
{
	Queue* newQueue = new Queue;
	newQueue->head = newQueue->tail = NULL;
	return newQueue;
}

void enqueue(Queue& q, int key)
{
	NODE* newNode = createNode(key);
	if (isEmpty(q))
	{
		q.tail = q.head = newNode;
	}
	else
	{
		q.tail->p_next = newNode;
		q.tail = newNode;
	}
}

int dequeue(Queue& q)
{
	if (isEmpty(q)) return -1;
	int head = q.head->key;
	q.head = q.head->p_next;
	if (!q.head)
	{
		q.tail = q.head;
	}
	return head;
}

int size(Queue q)
{
	int cnt = 0;
	for (NODE* pCount = q.head; pCount; pCount = pCount->p_next)
	{
		++cnt;
	}
	return cnt;
}

bool isEmpty(Queue q)
{
	return !q.head;
}

void printQueue(Queue q, ostream& os)
{
	NODE* pPrint = q.head;
	if (isEmpty(q)) os << "EMPTY ";
	for (; pPrint; pPrint = pPrint->p_next)
	{
		os << pPrint->key << ' ';
	}
	os << endl;
}

void freeQueue(Queue& q)
{
	while (!isEmpty(q))
	{
		dequeue(q);
	}
}

int main()
{
	ifstream readOrders("input.txt");
	ofstream printResult("output.txt");
	string getOrders;
	Queue newQueue;
	while (readOrders >> getOrders)
	{
		if (getOrders == "init")
		{
			newQueue = *initializeQueue();
		}
		else if (getOrders == "enqueue")
		{
			int enqueueNum;
			readOrders >> enqueueNum;
			enqueue(newQueue, enqueueNum);
		}
		else 
		{
			dequeue(newQueue);
		}
		printQueue(newQueue, printResult);
	}
	freeQueue(newQueue);
	readOrders.close();
	printResult.close();
	return 0;
}