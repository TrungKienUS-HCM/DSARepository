#include <iostream>
using namespace std;

struct NODE
{
	int key;
	NODE* p_left;
	NODE* p_right;
};

NODE* createNode(int data)
{
	NODE* newNode = new NODE;
	newNode->key = data;
	newNode->p_left = newNode->p_right = NULL;
	return newNode;
}

NODE* Search(NODE* pRoot, int x)
{
	if (!pRoot) return NULL;

	NODE* pSearch = pRoot;
	while (pSearch && pSearch->key != x)
	{
		if (x > pSearch->key) pSearch = pSearch->p_right;
		else pSearch = pSearch->p_left;
	}

	return pSearch;
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
		if (x >= pFind->key)
		{
			pFind = pFind->p_right;
		}
		else
		{
			pFind = pFind->p_left;
		}
	}
	if (pInsert->key <= x)
	{
		pInsert->p_right = newNode;
	}
	else
	{
		pInsert->p_left = newNode;
	}
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

NODE* findLeftMost(NODE* pRight)
{
	if (!pRight->p_left) return pRight;
	return findLeftMost(pRight->p_left);
}

void Remove(NODE*& pRoot, int x)
{
	if (!pRoot) return;
	NODE* pDel = Search(pRoot, x);
	NODE* pPar = NULL;
	if (!pDel) return;
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
}

NODE* createTree(int a[], int n)
{
	NODE* newTree = NULL;
	for (int i = 0; i < n; i++)
	{
		Insert(newTree, a[i]);
	}
	return newTree;
}

void removeTree(NODE*& pRoot)
{
	if ((!pRoot) || (!pRoot->p_left && !pRoot->p_right))
	{
		return;
	}
	removeTree(pRoot->p_left);
	removeTree(pRoot->p_right);
	delete pRoot;
	pRoot = NULL;
}

int Height(NODE* pRoot)
{
	if (!pRoot) return -1;
	int heightLeft = 1 + Height(pRoot->p_left);
	int heightRight = 1 + Height(pRoot->p_right);
	return max(heightLeft, heightRight);
}

int countLess(NODE* pRoot, int x)
{
	if (!pRoot) return 0;
	int cnt = countLess(pRoot->p_right, x) + countLess(pRoot->p_left, x);
	if (pRoot->key < x) ++cnt;
	return cnt;
}

int countGreater(NODE* pRoot, int x)
{
	if (!pRoot) return 0;
	int cnt = countGreater(pRoot->p_right, x) + countGreater(pRoot->p_left, x);
	if (pRoot->key > x) ++cnt;
	return cnt;
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

bool isFullBST(NODE* pRoot)
{
	if (!pRoot) return true;
	if (!pRoot->p_left && pRoot->p_right) return false;
	if (pRoot->p_left && !pRoot->p_right) return false;
	return isBST(pRoot) && isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
}