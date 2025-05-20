#include <iostream>
#include <vector>
#include <queue>
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

vector<int> vectorConcat(vector<int> a, const vector<int>& b)
{
	a.insert(a.end(), b.begin(), b.end());
	return a;
}

vector<int> NLR(NODE* pRoot)
{
	vector<int> tmpPush;
	if (!pRoot) return tmpPush;
	tmpPush.push_back(pRoot->key);
	tmpPush = vectorConcat(tmpPush, NLR(pRoot->p_left));
	tmpPush = vectorConcat(tmpPush, NLR(pRoot->p_right));
	return tmpPush;
}

vector<int> LNR(NODE* pRoot)
{
	vector<int> tmpPush;
	if (!pRoot) return tmpPush;
	tmpPush.push_back(pRoot->key);
	tmpPush = vectorConcat(LNR(pRoot->p_left), tmpPush);
	tmpPush = vectorConcat(tmpPush, LNR(pRoot->p_right));
	return tmpPush;
}

vector<int> LRN(NODE* pRoot)
{
	vector<int> tmpPush;
	if (!pRoot) return tmpPush;
	tmpPush.push_back(pRoot->key);
	tmpPush = vectorConcat(vectorConcat(LRN(pRoot->p_left), LRN(pRoot->p_right)), tmpPush);
	return tmpPush;
}

vector<vector<int>> LevelOrder(NODE* pRoot)
{
	vector<vector<int>> lvOrder;
	queue<NODE*> levels;
	int nodes = 1;
	levels.push(pRoot);
	while (!levels.empty())
	{
		vector<int> getNodes;
		for (int i = 0; i < nodes; i++)
		{
			if (!levels.empty())
			{
				if (levels.front()->p_left) levels.push(levels.front()->p_left);
				if (levels.front()->p_right) levels.push(levels.front()->p_right);
				getNodes.push_back(levels.front()->key);
				levels.pop();
			}
		}
		nodes = (int)levels.size();
		lvOrder.push_back(getNodes);
	}
	return lvOrder;
}

int countNode(NODE* pRoot)
{
	if (!pRoot) return 0;
	return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

int sumNode(NODE* pRoot)
{
	if (!pRoot) return 0;
	return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

int Level(NODE* pRoot, NODE* p)
{
	if (!pRoot) return -1;
	if (!p || pRoot == p) return 0;
	int levelPath1 = Level(pRoot->p_left, p);
	int levelPath2 = Level(pRoot->p_right, p);
	if (levelPath1 == -1 && levelPath2 == -1) return -1;
	return 2 + levelPath1 + levelPath2;
}

NODE* findNode(NODE* pRoot, int val)
{
	if (!pRoot) return NULL;
	if (pRoot->key == val) return pRoot;
	NODE* findLeft = findNode(pRoot->p_left, val);
	NODE* findRight = findNode(pRoot->p_right, val);
	return findLeft ? findLeft : findRight;
}

int treeHeight(NODE* pRoot)
{
	if (!pRoot) return -1;
	return 1 + max(treeHeight(pRoot->p_left), treeHeight(pRoot->p_right));
}

int heightNode(NODE* pRoot, int val)
{
	NODE* nodeVal = findNode(pRoot, val);
	if (!nodeVal) return -1;
	return treeHeight(nodeVal);
}

int countLeaf(NODE* pRoot)
{
	if (!pRoot) return 0;
	if (!pRoot->p_left && !pRoot->p_right) return 1;
	return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}