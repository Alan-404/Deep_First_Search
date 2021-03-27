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
	void DFS(int start, int goal);
	void printPath(int* path, int start, int goal);
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

void Graph::DFS(int start, int goal)
{
	bool* check = new bool[V];
	for (int i = 0; i < V; ++i)
		check[i] = false;
	check[start] = true;

	int* path = new int[V];
	path[start] = -1;

	stack<int> st;
	st.push(-1);

	int current = start;
	int i = start;
	int tmp;

	while (current != -1)
	{
		int v = 0;
		int size = adj[current].size();
		while (v < size )
		{
			tmp = adj[i][v];
			if (!check[tmp])
			{
				check[tmp] = true;
				path[tmp] = current;
				if (tmp == goal)
				{
					printPath(path, start, goal);
					exit(0);
				}
				st.push(current);
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
}

void Graph::printPath(int* path, int start, int goal)
{
	cout << "Successful Search\nPath: ";
	int pathLen = 0;
	int len;
	
	vector<int> result;
	result.push_back(goal);

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
		cout <<" --> " << result[i] ;
	}
	cout << "\nPath length: " << pathLen;
}

int main()
{
	int n;
	fi >> n;
	Graph g(n);

	int path; // so canh
	fi >> path;
	int a, b, c;
	while (!fi.eof()) {
		fi >> a;
		fi >> b;
		fi >> c;
		g.addEdge(a, b, c);
	}

	int start = 0, goal = 5;

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

	
	g.DFS(start, goal);
}