#include <iostream>
using namespace std;
#include <stack>
#include <vector>
#include <list>
#include <fstream>

ifstream fi("Input Graph.txt");

class Graph
{
	int V;
	vector<int>* adj;
	vector<int>* wgt;
public:
	Graph(int V);
	void addEdge(int a, int b, int wg);
	bool DLS(int start, int goal, int deptLimit);
	void printPath(int* path, int start, int goal);
	void IDS(int start, int goal);
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new vector<int>[V];
	wgt = new vector<int>[V];
}

void Graph::addEdge(int a, int b, int wg)
{
	adj[a].push_back(b);
	wgt[a].push_back(wg);
	adj[b].push_back(a);
	wgt[b].push_back(wg);
}

void Graph::IDS(int start, int goal)
{
	bool flag;
	for (int i = 1; ; ++i)
	{
		flag = DLS(start, goal, i);
		if (flag)
			break;
	}
}

bool Graph::DLS(int start, int goal, int dept_limit)
{
	bool* check = new bool[V];
	int* path = new int[V];
	int* Dept = new int[V];

	for (int i = 0; i < V; ++i)
		check[i] = false;
	check[start] = true;
	path[start] = -1;
	Dept[start] = 0;

	stack<int> st;
	st.push(-1);
	int current = start;
	int i = start;

	while (!st.empty())
	{
		int v = 0;
		int size = adj[current].size();
		while (v < size)
		{
			int tmp = adj[i][v];
			if (!check[tmp])
			{
				check[tmp] = true;
				path[tmp] = current;
				Dept[tmp] = Dept[current] + 1;
				if (Dept[tmp] <= dept_limit)
				{
					st.push(tmp);
				}					
				else
					continue;
				if (tmp == goal)
				{
					printPath(path, start, goal);
					exit(0);
				}
				current = tmp;
				i = tmp;
				break;
			}
			++v;
		}
		if (v == size)
		{
			current = st.top();
			i = current;
			st.pop();
		}
	}


	for (int i = 0; i < V; ++i)
		if (!check[i])
			return false;
	return true;
}

void Graph::printPath(int* path, int start, int goal)
{
	cout << "Successful Search\nPath: ";
	vector<int> result;
	result.push_back(goal);
	int pathLen = 0;
	int len;
	int pos = goal;
	while (pos != start)
	{
		result.push_back(path[pos]);
		len = find(adj[pos].begin(), adj[pos].end(), path[pos]) - adj[pos].begin();
		pathLen += wgt[pos][len];
		pos = path[pos];
	}

	cout << result[result.size() - 1];

	for (int i = result.size() - 2; i >= 0; --i)
	{
		cout << " --> " << result[i] ;
	}
	cout << "\nPath Length: " << pathLen;
}



int main()
{
	int n;
	fi >> n;
	Graph g(n);

	int path;
	fi >> path;
	
	int a, b, c;
	while (!fi.eof())
	{
		fi >> a >> b >> c;
		g.addEdge(a, b, c);
	}

	int start = 0;
	int goal = 6;

	if (start >= n || goal >= n)
	{
		cout << "Can't find";
		return 0;
	}

	if (start == goal)
	{
		cout << "Successful Search\nPath: " << start;
		return 0;
	}
	g.IDS(start, goal);
}