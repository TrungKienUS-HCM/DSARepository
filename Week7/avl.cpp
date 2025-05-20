#include <iostream>
using namespace std;

struct NODE
{
	int key;
	NODE* p_left;
	NODE* p_right;
	int height;
};

NODE* createNode(int data)
{
	NODE* newNode = new NODE;
	newNode->key = data;
	newNode->height = 0;
	newNode->p_left = newNode->p_right = NULL;
	return newNode;
}

bool isBalanced(NODE* pRoot)
{
	if (!pRoot) return true;
	int hLeft = -1, hRight = -1;
	if (pRoot->p_left) hLeft = pRoot->p_left->height;
	if (pRoot->p_right) hRight = pRoot->p_right->height;
	return abs(hLeft - hRight) <= 1;
}

NODE* findParent(NODE* pRoot, NODE* p)
{
	if (!pRoot || !p || pRoot == p) return NULL;
	if (pRoot->p_left && pRoot->p_left == p) return pRoot;
	if (pRoot->p_right && pRoot->p_right == p) return pRoot;
	NODE* checkLeft = findParent(pRoot->p_left, p);
	NODE* checkRight = findParent(pRoot->p_right, p);
	if (checkLeft || checkRight)
	{
		if (checkLeft) return checkLeft;
		if (checkRight) return checkRight;
	}
	return NULL;
}

int height(NODE* pRoot)
{
	if (!pRoot) return -1;
	int heightLeft = 1 + height(pRoot->p_left);
	int heightRight = 1 + height(pRoot->p_right);
	return max(heightLeft, heightRight);
}

void heightUpdate(NODE*& pRoot)
{
	if (!pRoot) return;
	pRoot->height = height(pRoot);
	heightUpdate(pRoot->p_left);
	heightUpdate(pRoot->p_right);
}

void RRotation(NODE*& pRoot)
{
	if (!pRoot) return;
	NODE* pA = pRoot;
	NODE* pB = pA->p_left;
	if (!pB) return;
	NODE* pC = pB->p_left;

	pA->p_left = pB->p_right;
	pB->p_right = pA;
	pRoot = pB;

	heightUpdate(pRoot);
}

void LRotation(NODE*& pRoot)
{
	if (!pRoot) return;
	NODE* pA = pRoot;
	NODE* pB = pA->p_right;
	if (!pB) return;
	NODE* pC = pB->p_right;

	pA->p_right = pB->p_left;
	pB->p_left = pA;
	pRoot = pB;
	
	heightUpdate(pRoot);
}

void LRRotation(NODE*& pRoot)
{
	if (!pRoot) return;
	NODE* pB = pRoot->p_left;
	if (!pRoot->p_left) return;
	if (!pB->p_right) return;

	LRotation(pRoot->p_left);
	RRotation(pRoot);
}

void RLRotation(NODE*& pRoot)
{
	if (!pRoot) return;
	NODE* pB = pRoot->p_right;
	if (!pRoot->p_right) return;
	if (!pB->p_left) return;

	RRotation(pRoot->p_right);
	LRotation(pRoot);
}

void balanceTree(NODE*& pRoot)
{
	if (!pRoot) return;
	balanceTree(pRoot->p_left);
	balanceTree(pRoot->p_right);
	heightUpdate(pRoot);
	if (!isBalanced(pRoot))
	{
		NODE* pCheck = pRoot;
		if (height(pCheck->p_left) > height(pCheck->p_right))
		{
			pCheck = pCheck->p_left;
			if (!pCheck) return;
			if (height(pCheck->p_left) >= height(pCheck->p_right))
			{
				RRotation(pRoot);
			}
			else
			{
				LRRotation(pRoot);
			}
		}
		else
		{
			pCheck = pCheck->p_right;
			if (!pCheck) return;
			if (height(pCheck->p_right) >= height(pCheck->p_left))
			{
				LRotation(pRoot);
			}
			else
			{
				RLRotation(pRoot);
			}
		}
	}
}

void Insert(NODE*& pRoot, int x)
{
	NODE* newNode = createNode(x);
	if (!pRoot)
	{
		pRoot = newNode;
		return;
	}
	NODE* pFind = pRoot;
	NODE* pInsert = NULL;
	while (pFind)
	{
		pInsert = pFind;
		if (x > pFind->key)
		{
			pFind = pFind->p_right;
		}
		else if (pFind->key == x)
		{
			return;
		}
		else
		{
			pFind = pFind->p_left;
		}
	}
	if (pInsert->key < x)
	{
		pInsert->p_right = newNode;
	}
	else
	{
		pInsert->p_left = newNode;
	}

	balanceTree(pRoot);
}

NODE* Search(NODE* pRoot, int x)
{
	if (!pRoot) return NULL;

	NODE* pSearch = pRoot;
	while (pSearch && pSearch->key != x)
	{
		if (x >= pSearch->key) pSearch = pSearch->p_right;
		else pSearch = pSearch->p_left;
	}

	return pSearch;
}

NODE* findLeftMost(NODE* pRight)
{
	if (!pRight->p_left) return pRight;
	return findLeftMost(pRight->p_left);
}

void Remove(NODE*& pRoot, int x)
{
	if (!pRoot) return;
	NODE* pDel = Search(pRoot, x);
	if (!pDel) return;
	NODE* pPar = NULL;
	if (pDel->p_left && pDel->p_right)
	{
		NODE* pSwap = findLeftMost(pDel->p_right);
		pPar = findParent(pRoot, pSwap);
		swap(pSwap->key, pDel->key);
		pDel = pSwap;
	}
	if ((pDel->p_left && !pDel->p_right) || (!pDel->p_left && pDel->p_right))
	{
		pPar = findParent(pRoot, pDel);
		if (pPar)
		{
			NODE* pConnect = NULL;
			if (pDel->p_right) pConnect = pDel->p_right;
			else pConnect = pDel->p_left;
			if (pDel == pPar->p_left) pPar->p_left = pConnect;
			else pPar->p_right = pConnect;
		}
		else
		{
			if (pRoot->p_left) pRoot = pRoot->p_left;
			else pRoot = pRoot->p_right;
		}
	}
	if (!pPar) pPar = findParent(pRoot, pDel);
	if (pPar)
	{
		if (pDel == pPar->p_left) pPar->p_left = NULL;
		if (pDel == pPar->p_right) pPar->p_right = NULL;
	}
	else
	{
		if (pRoot == pDel)
		{
			pRoot = NULL;
		}
	}
	delete pDel;
	balanceTree(pRoot);
}

NODE* findMax(NODE* pRoot)
{
	if (!pRoot) return NULL;
	NODE* pLeft = findMax(pRoot->p_left);
	NODE* pRight = findMax(pRoot->p_right);
	int cmpRoot = pRoot->key;
	int cmpLeft = cmpRoot, cmpRight = cmpRoot;
	if (pLeft) cmpLeft = pLeft->key;
	if (pRight) cmpRight = pRight->key;
	int res = max(max(cmpRoot, cmpLeft), cmpRight);
	if (res == pRoot->key)
	{
		return pRoot;
	}
	else
	{
		if (pLeft && res == pLeft->key)
		{
			return pLeft;
		}
		if (pRight && res == pRight->key)
		{
			return pRight;
		}
	}
	return NULL;
}

NODE* findMin(NODE* pRoot)
{
	if (!pRoot) return NULL;
	NODE* pLeft = findMax(pRoot->p_left);
	NODE* pRight = findMax(pRoot->p_right);
	int cmpRoot = pRoot->key;
	int cmpLeft = cmpRoot, cmpRight = cmpRoot;
	if (pLeft) cmpLeft = pLeft->key;
	if (pRight) cmpRight = pRight->key;
	int res = min(min(cmpRoot, cmpLeft), cmpRight);
	if (res == pRoot->key)
	{
		return pRoot;
	}
	else
	{
		if (pLeft && res == pLeft->key)
		{
			return pLeft;
		}
		if (pRight && res == pRight->key)
		{
			return pRight;
		}
	}
	return NULL;
}

bool isBST(NODE* pRoot)
{
	if (!pRoot) return true;
	NODE* leftSubTree = findMax(pRoot->p_left);
	NODE* rightSubTree = findMin(pRoot->p_right);
	bool checkLeft = true, checkRight = true;
	if (leftSubTree) checkLeft = pRoot->key >= leftSubTree->key;
	if (rightSubTree) checkRight = pRoot->key <= rightSubTree->key;
	return checkLeft && checkRight && isBST(pRoot->p_left) && isBST(pRoot->p_right);
}

bool isAVL(NODE* pRoot)
{
	if (!pRoot) return true;
	bool checkLeft = isBalanced(pRoot->p_left) && isBST(pRoot->p_left) && isAVL(pRoot->p_left);
	bool checkRight = isBalanced(pRoot->p_right) && isBST(pRoot->p_right) && isAVL(pRoot->p_right);
	return checkLeft && checkRight;
}