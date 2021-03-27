#include <fstream>
#include<iostream> 
#include <list>
#include<vector>
#define MAX 100

using namespace std;

int a[MAX][MAX] = { 0 };
int n;                  //Số đỉnh
bool* checkvisit;       //Kiểm tra xem đỉnh i đã được đi qua hay chưa
int* father;            //Điểm trước đó đã được đi qua
int* depth;             //depth[i] là độ sâu của đỉnh i
int maxdepth;
int increase = 1;
list<int> OPEN;
list<int> NEXT;
list<int> CLOSE;
void revise() {
    checkvisit = new bool[n];
    for (int i = 0; i < n; i++)
    {
        checkvisit[i] = false;
    }
    depth = new int[n];
    father = new int[n];
    maxdepth = 1;

}
void addRoot(int root)
{
    OPEN.push_front(root);
    depth[root] = 0;
    checkvisit[root] = true;
    father[root] = -1;            //=-1(NULL)
}
bool DLS(int limit, int goal)
{
    while (!OPEN.empty()) {
        int checking = OPEN.front();
        OPEN.pop_front();
        if (checking == goal)
            return true;
        if (depth[checking] < limit)
        {
            CLOSE.push_front(checking);
            for (int i = n - 1; i >= 0; i--)
            {
                if (a[checking][i] == 1) {

                    int adjacent = i;
                    if (checkvisit[adjacent] == false)
                    {
                        checkvisit[adjacent] = true;
                        father[adjacent] = checking;
                        if (adjacent == goal)
                            return true;
                        OPEN.push_front(adjacent);
                        depth[adjacent] = depth[checking] + 1;
                    }
                }
            }
        }
        else
            NEXT.push_back(checking);
    }
    if (!NEXT.empty())
        maxdepth = limit + increase;
    return false;
}

void inputfile(int& start, int& goal, int& depthlimit) {
    ifstream fileInput("Input.txt");
    if (fileInput.fail())
        cout << "Failed to open this file!" << endl;
    else
    {
        fileInput >> n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                fileInput >> a[i][j];
        fileInput >> start;
        fileInput >> goal;
        fileInput >> depthlimit;
    }
    fileInput.close();
}
void showSolution(int goal)
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
bool IDS(int firstpoint, int goal)
{
    //Khởi tạo danh sách NEXT chứa u0
    NEXT.push_front(firstpoint);
    depth[firstpoint] = 0;
    checkvisit[firstpoint] = true;
    father[firstpoint] = -1;
    if (firstpoint == goal)
    {
        //showSolution(goal);
        return true;
    }
    else
        for (int d = 1; d <= maxdepth; d+= increase)
        {
            OPEN.insert(OPEN.begin(), NEXT.begin(), NEXT.end());
            NEXT.erase(NEXT.begin(), NEXT.end());

            if (DLS(d, goal) == true)
            {
                //showSolution(goal);
                return true;
            }
        }
    return false;
}
int main()
{
    int start;
    int goal;
    int depthlimit;
    inputfile(start,goal,depthlimit);
    revise();
    //DLS
    /*addRoot(start);
    if (DLS(depthlimit, goal)) showSolution(goal);
    else cout << "can't find solution\n";*/
    //IDS
    if (IDS(start, goal)) showSolution(goal);
    else cout << "CAN'T FIND SOLUTION\n";
    return 0;
}
