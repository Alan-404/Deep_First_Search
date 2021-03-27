#include <iostream>
using namespace std;
#include <stack>
#include <vector>
#include <fstream>
#define MAX 1000

ifstream fi("Input Graph.txt");

int adj[MAX][MAX] = { 0 };
int n;

void printPath(int* path, int start, int goal)
{
	cout << "Successful Search\nPath: ";
	vector<int> result;
	result.push_back(goal);

	int pos = goal;

	while (pos != start)
	{
		result.push_back(path[pos]);
		pos = path[pos];
	}
	cout << result[result.size() - 1];
	for (int i = result.size() - 1; i >= 0; --i)
	{
		cout << " --> " << result[i];
	}
}

void DFS(int start, int goal)
{
	bool* check = new bool[n];
	for (int i = 0; i < n; ++i)
		check[i] = false;
	check[start] = true;

	int* path = new int[n];
	path[start] = -1;

	stack<int> st;
	st.push(-1);

	int current = start;
	int i = start;
	int v;

	while (current != -1)
	{
		v = 0;
		while (v < n)
		{
			
			if (check[v] == false && adj[i][v] == 1)
			{
				check[v] = true;
				path[v] = current;
				if (v == goal)
				{
					printPath(path, start, goal);
					exit(0);
				}
				st.push(current);
				current = v;
				i = v;
				break;
			}
			++v;
		}
		if (v == n)
		{
			current = st.top();
			i = current;
			st.pop();
		}
	}

}

int main()
{
	fi >> n;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			fi >> adj[i][j];
	}
	int start, goal;
	fi >> start >> goal;

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
	DFS(start, goal);
	return 0;
}