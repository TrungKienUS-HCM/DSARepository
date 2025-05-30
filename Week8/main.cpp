#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;

vector<vector<int>> convertMatrixToList(const string& filename)
{
	vector<vector<int>> adjList;
	ifstream getMatrix(filename);
	if (!getMatrix.is_open()) return adjList;

	int n;
	getMatrix >> n;
	adjList.push_back(vector<int>(1, n));
	for (int i = 0; i < n; ++i)
	{
		vector<int> vertex;
		vertex.push_back(0);
		for (int j = 0; j < n; ++j)
		{
			int edge;
			getMatrix >> edge;
			if (edge == 1)
			{
				vertex.push_back(j);
				vertex[0]++;
			}
		}
		adjList.push_back(vertex);
	}

	getMatrix.close();
	return adjList;
}

vector<vector<int>> convertListToMatrix(const string& filename)
{
	ifstream getList(filename);
	int n; getList >> n;
	vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
	adjMatrix.insert(adjMatrix.begin(), vector<int>(1, n));
	for (int i = 1; i <= n; ++i)
	{
		int vertices;
		getList >> vertices;
		for (int j = 0; j < vertices; j++)
		{
			int idx;
			getList >> idx;
			if (idx < n) adjMatrix[i][idx] = 1;
		}
	}
	getList.close();
	return adjMatrix;
}

bool isDirected(const vector<vector<int>>& adjMatrix)
{
	for (int i = 1; i < (int)adjMatrix.size(); i++)
	{
		for (int j = i; j < (int)adjMatrix.size() - 1; j++)
		{
			if (adjMatrix[i][j] * adjMatrix[j + 1][i - 1]  == 1)
			{
				return false;
			}
		}
	}
	return true;
}

int countVertices(const vector<vector<int>>& adjMatrix)
{
	return (int)adjMatrix.size() - 1;
}

int countEdges(const vector<vector<int>>& adjMatrix)
{
	int cnt = 0;
	for (int i = 1; i < (int)adjMatrix.size(); i++)
	{
		for (int j = i; j < (int)adjMatrix.size() - 1; j++)
		{
			int iEdge = j + 1, jEdge = i - 1;
			if (adjMatrix[i][j] + adjMatrix[iEdge][jEdge] >= 1) ++cnt;
		}
	}
	return cnt;
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix)
{
	vector<int> isolatedCount;
	for (int i = 1; i < (int)adjMatrix.size(); i++)
	{
		int j = 0;
		for (; j < (int)adjMatrix.size() - 1; j++)
		{
			if (adjMatrix[i][j] + adjMatrix[j + 1][i - 1] != 0)
			{
				break;
			}
		}
		if (j == (int)adjMatrix.size() - 1) isolatedCount.push_back(i - 1);
	}
	return isolatedCount;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix)
{
	int edges = countEdges(adjMatrix);
	int vertices = countVertices(adjMatrix);
	return edges == (vertices * (vertices - 1)) / 2;
}

bool DFSColoring(const vector<vector<int>>& adjMatrix, vector<int>& coloring, int color, int vertex)
{
	if (coloring[vertex] == color)
		return true;
	if (coloring[vertex] == 1 - color)
		return false;
	coloring[vertex] = color;
	for (int i = 0; i < countVertices(adjMatrix); i++)
	{
		if (adjMatrix[vertex + 1][i])
		{
			if (!DFSColoring(adjMatrix, coloring, 1 - color, i))
			{
				return false;
			}
		}
	}
	return true;
}

bool isBipartite(const vector<vector<int>>& adjMatrix)
{
	int n = countVertices(adjMatrix);
	int firstAdj = -1;
	for (int i = 1; i <= n && firstAdj < 0; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (adjMatrix[i][j])
			{
				firstAdj = i - 1;
				break;
			}
		}
	}

	if (firstAdj < 0) return false;
	vector<int> coloring(n + 1, -1);
	return DFSColoring(adjMatrix, coloring, 0, firstAdj);
}

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix)
{
	int n = countVertices(adjMatrix);
	int firstAdj = -1;
	for (int i = 1; i <= n && firstAdj < 0; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (adjMatrix[i][j])
			{
				firstAdj = i - 1;
				break;
			}
		}
	}

	if (firstAdj < 0) return false;
	vector<int> coloring(n, -1);
	if (!DFSColoring(adjMatrix, coloring, 0, firstAdj)) return false;

	vector<int> white;
	vector<int> black;
	for (int i = 0; i < (int)coloring.size(); i++)
	{
		if (coloring[i])
		{
			white.push_back(i);
		}
		else
		{
			black.push_back(i);
		}
	}

	for (int i = 0; i < (int)white.size(); i++)
	{
		for (int j = 0; j < (int)black.size(); j++)
		{
			if (!adjMatrix[white[i] + 1][black[j]])
			{
				return false;
			}
		}
	}

	return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix)
{
	int mtxSize = (int)adjMatrix.size() - 1;
	vector<vector<int>> unDir(mtxSize, vector<int>(mtxSize, 0));
	for (int i = 1; i <= mtxSize; i++)
	{
		for (int j = 0; j < mtxSize; j++)
		{
			if (adjMatrix[i][j])
			{
				unDir[i - 1][j] = 1;
				unDir[j][i - 1] = 1;
			}
		}
	}
	unDir.insert(unDir.begin(), vector<int>(1, mtxSize));
	return unDir;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix)
{
	int mtxSize = (int)adjMatrix.size() - 1;
	vector<vector<int>> complement(mtxSize + 1, vector<int>(mtxSize, 1));
	for (int i = 1; i <= mtxSize; i++)
	{
		for (int j = i; j < mtxSize; j++)
		{
			if (adjMatrix[i][j])
			{
				int iCom = j + 1, jCom = i - 1;
				complement[iCom][jCom] = 0;
				complement[i][j] = 0;
			}
		}
		complement[i][i - 1] = 0;
	}
	complement[0] = vector<int>(1, adjMatrix.size() - 1);
	return complement;
}

void DFSToCheckVisited(const vector<vector<int>>& adjMatrix, int start, vector<bool>& visited)
{
	visited[start] = true;
	for (int i = 0; i < countVertices(adjMatrix); i++)
	{
		if (adjMatrix[start + 1][i] && !visited[i])
		{
			DFSToCheckVisited(adjMatrix, i, visited);
		}
	}
}

int vertexDegree(const vector<vector<int>>& adjMatrix, int vertex)
{
	int deg = 0;
	int n = countVertices(adjMatrix);
	for (int i = 0; i < n; i++)
	{
		if (adjMatrix[vertex][i]) ++deg;
	}
	return deg;
}

bool checkDirectedEulerCycle(const vector<vector<int>>& adjMatrix)
{
	int n = countVertices(adjMatrix);

	vector<bool> visited(n + 1, false);

	int start = -1;
	for (int i = 1; i <= n && start == -1; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (adjMatrix[i][j])
			{
				start = i - 1;
				break;
			}
		}
	}

	if (start < 0) return false;

	DFSToCheckVisited(adjMatrix, start, visited);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (adjMatrix[i][j] && !visited[j])
			{
				return false;
			}
		}
	}

	for (int i = 1; i <= n; i++)
	{
		int in = 0, out = 0;
		for (int j = 0; j < n; j++)
		{
			if (adjMatrix[i][j])
			{
				out++;
			}
			if (adjMatrix[j + 1][i - 1])
			{
				in++;
			}
		}
		if (in != out) return false;
	}

	return true;
}

bool checkUndirectedEulerCycle(const vector<vector<int>>& adjMatrix)
{
	int n = countVertices(adjMatrix);

	vector<bool> visited(n + 1, false);

	int start = -1;
	for (int i = 1; i <= n && start == -1; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (adjMatrix[i][j])
			{
				start = i - 1;
				break;
			}
		}
	}

	if (start < 0) return false;

	DFSToCheckVisited(adjMatrix, start, visited);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (adjMatrix[i][j] && !visited[i - 1])
			{
				return false;
			}
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (vertexDegree(adjMatrix, i) % 2) return false;
	}

	return true;
}

vector<int> convertToVector(stack<int> st)
{
	vector<int> res;
	while (!st.empty())
	{
		res.push_back(st.top());
		st.pop();
	}
	return res;
}

void deletePath(vector<vector<int>>& adjMatrix, int u, int v)
{
	adjMatrix[u + 1][v] = adjMatrix[v + 1][u] = 0;
}

int getFirstAdjacent(vector<vector<int>> adjMatrix, int vertex)
{
	int n = countVertices(adjMatrix);
	for (int i = 0; i < n; i++)
	{
		if (adjMatrix[vertex + 1][i]) return i;
	}
	return -1;
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix)
{
	stack<int> eulerCycle;
	if (!isDirected(adjMatrix) && !checkUndirectedEulerCycle(adjMatrix)) return {};
	if (isDirected(adjMatrix) && !checkDirectedEulerCycle(adjMatrix)) return {};
	stack<int> path;
	vector<vector<int>> adjMatrix2 = adjMatrix;
	int start = -1, n = countVertices(adjMatrix);
	for (int i = 1; i <= n; i++)
	{
		if (vertexDegree(adjMatrix2, i) > 0)
		{
			start = i - 1;
			break;
		}
	}

	path.push(start);
	while (!path.empty())
	{
		int adj = getFirstAdjacent(adjMatrix2, path.top());
		if (adj >= 0)
		{
			deletePath(adjMatrix2, path.top(), adj);
			path.push(adj);
		}
		else
		{
			eulerCycle.push(path.top());
			path.pop();
		}
	}

	return convertToVector(eulerCycle);
}

void DFSTree(const vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<vector<int>>& res, int vertex)
{
	if (visited[vertex]) return;
	visited[vertex] = true;
	int n = countVertices(adjMatrix);
	for (int i = 0; i < n; i++)
	{
		if (adjMatrix[vertex + 1][i] && !visited[i])
		{
			res[vertex + 1][i] = res[i + 1][vertex] = 1;
			DFSTree(adjMatrix, visited, res, i);
		}
	}
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start)
{
	int n = countVertices(adjMatrix);
	vector<vector<int>> adjTree(n, vector<int>(n, 0));
	adjTree.insert(adjTree.begin(), vector<int>(1, n));
	vector<bool> visited(n, false);
	DFSTree(adjMatrix, visited, adjTree, start);
	for (bool check : visited)
	{
		if (!check)
		{
			return {};
		}
	}
	return adjTree;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start)
{
	int n = countVertices(adjMatrix);
	vector<vector<int>> adjTree(n, vector<int>(n, 0));
	adjTree.insert(adjTree.begin(), vector<int>(1, n));
	queue<int> neighbors;
	vector<bool> visited(n, false);
	neighbors.push(start);
	visited[start] = true;
	while (!neighbors.empty())
	{
		int currVertex = neighbors.front();
		neighbors.pop();
		for (int i = 0; i < n; i++)
		{
			if (adjMatrix[currVertex + 1][i] && !visited[i])
			{
				visited[i] = true;
				adjTree[currVertex + 1][i] = adjTree[i + 1][currVertex] = 1;
				neighbors.push(i);
			}
		}
	}

	for (bool check : visited)
	{
		if (!check)
		{
			return {};
		}
	}

	return adjTree;
}

bool dfsCheckConnected(int u, int v, const vector<vector<int>>& adjMatrix, vector<bool>& visited)
{
	if (u == v) return true;
	visited[u] = true;
	int n = countVertices(adjMatrix);
	for (int i = 0; i < n; i++)
	{
		if (adjMatrix[u + 1][i] && !visited[i])
		{
			if (dfsCheckConnected(i, v, adjMatrix, visited))
				return true;
		}
	}
	visited[u] = false;
	return false;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix)
{
	if (u == v) return true;
	vector<bool> visited(countVertices(adjMatrix), false);
	return dfsCheckConnected(u, v, adjMatrix, visited);
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix)
{
	int n = countVertices(adjMatrix);
	vector<int> distance(n, INT_MAX);
	vector<int> prev(n, -1);
	vector<bool> explored(n, false);
	distance[start] = 0;

	for (int k = 0; k < n; k++)
	{
		int minVertex = -1;
		for (int j = 0; j < n; j++)
		{
			if (!explored[j] && (minVertex == -1 || distance[minVertex] > distance[j]))
			{
				minVertex = j;
			}
		}

		if (distance[minVertex] == INT_MAX) break;
		explored[minVertex] = true;

		for (int i = 0; i < n; i++)
		{
			if (!explored[i])
			{
				if (adjMatrix[minVertex + 1][i] && adjMatrix[minVertex + 1][i] + distance[minVertex] < distance[i])
				{
					distance[i] = adjMatrix[minVertex + 1][i] + distance[minVertex];
					prev[i] = minVertex;
				}
			}
		}
	}

	vector<int> path;
	for (int find = end; find != -1; find = prev[find])
	{
		path.insert(path.begin(), find);
	}

	if (path[0] != start) return {};

	return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix)
{
	int n = countVertices(adjMatrix);
	vector<int> distance(n, INT_MAX);
	vector<int> prev(n, -1);

	distance[start] = 0;
	bool updated = false;
	for (int k = 1; k < n; k++)
	{
		updated = false;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (adjMatrix[i][j] && distance[i - 1] != INT_MAX)
				{
					int newDis = adjMatrix[i][j] + distance[i - 1];
					if (newDis < distance[j])
					{
						distance[j] = newDis;
						prev[j] = i - 1;
						updated = true;
					}
				}
			}
		}
		if (!updated) break;
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (adjMatrix[i][j])
			{
				if (adjMatrix[i][j] + distance[i - 1] < distance[j])
					return {};
			}
		}
	}

	vector<int> path;
	for (int find = end; find != -1; find = prev[find])
	{
		path.insert(path.begin(), find);
	}

	if (path[0] != start) return {};
	return path;
}
