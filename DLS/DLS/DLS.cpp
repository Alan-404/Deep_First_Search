#include <iostream>
using namespace std;
#include <stack>
#include <fstream>
#include <vector>
#define MAX 1000

ifstream fi("Input Graph.txt");

int adj[MAX][MAX];
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
	for (int i = result.size() - 2; i >= 0; --i)
	{
		cout << " --> " << result[i];
	}
}

void DLS(int start, int goal, int dept_limit)
{
	bool* check = new bool[n];
	int* path = new int[n];
	int* Dept = new int[n];

	for (int i = 0; i < n; ++i)
		check[i] = false;
	check[start] = true;
	Dept[start] = 0;

	stack<int> st;
	st.push(-1);
	int current = start;
	int i = start;

	while (current != -1)
	{
		int v = 0;
		while (v < n)
		{
			if (!check[v] && adj[i][v] == 1)
			{
				check[v] = true;
				path[v] = current;
				Dept[v] = Dept[current] + 1;
				if (Dept[v] <= dept_limit)
				{
					st.push(v);
				}
				else
					continue;
				if (v == goal)
				{
					printPath(path, start, goal);
					exit(0);
				}
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
	cout << "Can't find";
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

	int limit;
	fi >> limit;

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

	DLS(start, goal, limit);
}