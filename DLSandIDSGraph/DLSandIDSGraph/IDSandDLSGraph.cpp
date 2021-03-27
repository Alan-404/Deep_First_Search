#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <stdlib.h>
using namespace std;
bool* checkvisit;       //Kiểm tra xem đỉnh i đã được đi qua hay chưa
int* depth;             //depth[i] là độ sâu của đỉnh i
int* father;            //Điểm trước đó đã được đi qua
int maxdepth;
int increase=1;
list<int> OPEN;
list<int> NEXT;
list<int> CLOSE;
class Graph
{
    int V;                  //số node
    vector<vector<int>> adjacent;  //Mỗi adjancent[i] là một tập hợp các đỉnh đi qua đỉnh i
public:
    Graph();
    void revise(int V);
    void addEdge(int v, int w);
    bool DLS(int d, int goal);
    bool IDS(int firstpoint, int goal);
    void addRoot(int root);
    void ouputEdge();
    void showSolution(int goal);
    void inputfile(int& start, int& goal, int& depthlimit);
};
Graph::Graph()
{

}
void Graph::revise(int V)
{
    this->V = V;
    adjacent.resize(V);
    checkvisit = new bool[V];
    for (int i = 0; i < V; i++)
    {
        checkvisit[i] = false;
    }
    depth = new int[V];
    father = new int[V];
    maxdepth = 1;
}
void Graph::ouputEdge()
{
    for (int i = 0; i < V; i++)
    {
        cout << "The adjacent points of " << i << " : ";
        for (int j = 0, end = adjacent[i].size(); j < end; j++)
        {
            cout << adjacent[i][j] << " ";
        }
        cout << endl;
    }
}
void Graph::addEdge(int v, int w) {
    adjacent[v].push_back(w);
    adjacent[w].push_back(v);
}
void Graph::addRoot(int root)
{
    OPEN.push_front(root);
    depth[root] = 0;
    checkvisit[root] = true;
    father[root] = -1;            //=-1(NULL)
}
bool Graph::DLS(int d, int goal)
{
    while (!OPEN.empty())
    {
        int u = OPEN.front();
        OPEN.pop_front();
        if (u == goal)
            return true;
        if (depth[u] < d)
        {
            CLOSE.push_front(u);
            for (int i = adjacent[u].size() - 1; i >= 0; i--)
            {
                int v = adjacent[u][i];
                if (checkvisit[v] == false)
                {
                    checkvisit[v] = true;
                    father[v] = u;
                    if (v == goal)
                        return true;
                    OPEN.push_front(v);
                    depth[v] = depth[u] + 1;
                }
            }
        }
        else
            NEXT.push_back(u);
    }
    if (!NEXT.empty())
        maxdepth = d + increase;
    return false;
}
bool Graph::IDS(int firstpoint, int goal)
{
    //Khởi tạo danh sách NEXT chứa u0
    NEXT.push_front(firstpoint);
    depth[firstpoint] = 0;
    checkvisit[firstpoint] = true;
    father[firstpoint] = -1;
    if (firstpoint == goal)
    {
        return true;
    }
    else
        for (int d = 1; d <= maxdepth; d+=increase)
        {
            OPEN.insert(OPEN.begin(), NEXT.begin(), NEXT.end());
            NEXT.erase(NEXT.begin(), NEXT.end());
            if (DLS(d, goal) == true)
            {
                return true;
            }
        }
    return false;
}
void Graph::showSolution(int goal)
{
    int previous = father[goal];
    vector<int> solution;
    solution.push_back(goal);
    while (previous != -1)     //!=NULL(-1)
    {
        solution.push_back(previous);
        previous = father[previous];
    };
    reverse(solution.begin(), solution.end());
    cout << "Solution: " << solution[0];
    for (int i = 1, end = solution.size(); i < end; i++)
        cout << " --> " << solution[i];
    cout << endl;
}
void Graph::inputfile(int& start,int& goal,int& depthlimit) {
    ifstream fileInput("Input.txt");
    if (fileInput.fail())
        cout << "Failed to open this file!" << endl;
    else
    {
        fileInput >> V;
        revise(V);
        int sodong;
        int temp1;
        int temp2;
        fileInput >> sodong;
        for(int i=0;i<sodong;i++)
        {
            fileInput >> temp1;
            fileInput >> temp2;
            addEdge(temp1, temp2);
        }
        fileInput >> start;
        fileInput >> goal;
        fileInput >> depthlimit;
    }
    fileInput.close();
}
int main()
{
    //Khởi tạo đồ thị
    Graph g;
    int start;
    int goal;
    int depthlimit;
    g.inputfile(start,goal,depthlimit);
    //g.ouputEdge();
    //Run IDS
    if (g.IDS(start, goal) == true)
    {
        g.showSolution(goal);
    }
    else
        cout << "Can not find the solution\n";
    //Run DLS
    /*g.addRoot(start);
    if (g.DLS(depthlimit,goal) == true)
    {
        g.showSolution(goal);
    }
    else
        cout << "Can not find the solution\n";*/
    return 0;
}