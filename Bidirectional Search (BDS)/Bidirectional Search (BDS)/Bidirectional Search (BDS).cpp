#include <iostream>
using namespace std;
#include <list>
#include <vector>
#include <queue>
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
	void BDS(int start, int goal);
	void BFS(list<int>* Q, bool* check, int* path);
	int visitedIntersect(bool* start_check, bool* goal_check);
	void printPath(int* start_path, int* goal_path, int start, int goal, int meet);
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

int Graph:: visitedIntersect(bool* start_check, bool* goal_check)
{
	for (int i = V - 1; i >= 0; --i)
	{
		if (start_check[i] && goal_check[i])
		{
			return i;
		}
	}
	return -1;
}

void Graph::BDS(int start, int goal)
{
	bool* start_check = new bool[V];
	bool* goal_check = new bool[V];

	int* start_path = new int[V];
	int* goal_path = new int[V];

	for (int i = 0; i < V; ++i)
	{
		start_check[i] = false;
		goal_check[i] = false;
	}

	list<int> start_list, goal_list;

	int meet = -1;

	start_check[start] = true;
	start_path[start] = -1;
	start_list.push_back(start);

	goal_check[goal] = true;
	goal_path[goal] = -1;
	goal_list.push_back(goal);

	while (!start_list.empty() && !goal_list.empty())
	{
		BFS(&start_list, start_check, start_path);

		BFS(&goal_list, goal_check, goal_path);

		meet = visitedIntersect(start_check, goal_check);

		if (meet != -1)
		{
			printPath(start_path, goal_path, start, goal, meet);
			exit(0);
		}
	}
	cout << "Can't find";
}

void Graph::printPath(int* start_path, int* goal_path, int start, int goal, int meet)
{
	cout << "Successful Search:\nPath: ";
	vector<int> startResult;
	vector<int> goalResult;

	int len;
	int pathLen = 0;

	int startPos = meet;
	int goalPos = meet;

	while (startPos != start)
	{
		len = find(adj[startPos].begin(), adj[startPos].end(), start_path[startPos]) - adj[startPos].begin();
		pathLen += wgt[startPos][len];
		startResult.push_back(start_path[startPos]);
		startPos = start_path[startPos];
	}

	goalResult.push_back(meet);

	while (goalPos != goal)
	{
		len = find(adj[goalPos].begin(), adj[goalPos].end(), goal_path[goalPos]) - adj[goalPos].begin();
		pathLen += wgt[goalPos][len];
		goalResult.push_back(goal_path[goalPos]);
		goalPos = goal_path[goalPos];
	}

	int n = startResult.size();

	cout << startResult[n - 1] ;;

	for (int i = startResult.size() - 2; i >= 0; --i)
		cout << " --> " << startResult[i] ;

	for (int i = 0; i < goalResult.size() ; ++i)
		cout << " --> " << goalResult[i];

	cout << "\nPath Length: " << pathLen;
}

void Graph::BFS(list<int>* Q, bool* check, int* path)
{
	int current = Q->front();
	Q->pop_front();

	vector<int>::iterator i;
	for (i = adj[current].begin(); i != adj[current].end(); ++i)
	{
		if (!check[*i])
		{
			check[*i] = true;
			path[*i] = current;
			Q->push_back(*i);
		}
	}
}

int main()
{
	int n;
	fi >> n;
	Graph g(n);


	int a, b, c;
	while (!fi.eof())
	{
		fi >> a >> b >> c;
		g.addEdge(a, b, c);
	}

	int start = 0;
	int end = 15;
	if (end >= n || start >= n)
	{
		cout << "Can't find information";
		return 0;
	}
	if (start == end)
	{
		cout << "Successful Search\nPath: "<< start;
		return 0;
	}
	g.BDS(start, end);
	return 0;
}