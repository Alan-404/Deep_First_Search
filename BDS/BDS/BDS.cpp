#include <iostream>
using namespace std;
#include <list>
#include <vector>
#include <queue>
#include <fstream>
#define MAX 1000

ifstream fi("Test.txt");

int adj[MAX][MAX] = { 0 };
int n;

void BFS(list<int>& Q, bool* check, int* path)
{
	int current = Q.front();
	Q.pop_front();

	for (int i = 0; i < n; ++i)
	{
		if (check[i] == false && adj[current][i] == 1)

		{
			check[i] = true;
			path[i] = current;
			Q.push_back(i);
		}
	}
}

int visitedIntersect(bool* start_check, bool* goal_check)
{
	for (int i = n - 1; i >= 0; --i)
		if (start_check[i] & goal_check[i])
			return i;
	return -1;
}

void printPath(int *start_path, int *goal_path, int start, int goal, int meet)
{
	cout << "Successful Search\nPath: ";
	vector<int> startResult;
	vector<int> goalResult;


	int startPos = meet;
	int goalPos = meet;

	while (startPos != start)
	{
		startResult.push_back(start_path[startPos]);
		startPos = start_path[startPos];
	}

	goalResult.push_back(meet);

	while (goalPos != goal)
	{
		goalResult.push_back(goal_path[goalPos]);
		goalPos = goal_path[goalPos];
	}

	cout << startResult[startResult.size() - 1];

	for (int i = startResult.size() - 2; i >= 0; --i)
		cout << " --> " << startResult[i] ;

	
	for (int i = 0; i < goalResult.size(); ++i)
		cout << " --> " << goalResult[i] ;
}


void BDS(int start, int goal)
{
	bool* start_check = new bool[n];
	bool* goal_check = new bool[n];

	int* start_path = new int[n];
	int* goal_path = new int[n];

	for (int i = 0; i < n; ++i)
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
		BFS(start_list, start_check, start_path);

		BFS(goal_list, goal_check, goal_path);

		meet = visitedIntersect(start_check, goal_check);

		if (meet != -1)
		{
			printPath(start_path, goal_path, start, goal, meet);
			exit(0);
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
	

	if (start >= n || goal >= n)
	{
		cout << "Can't find";
		return 0;
	}

	if (start == goal)
	{
		cout << "Successful Search\nPath: "<< start;
		return 0;
	}

	BDS(start, goal);

}