#include<iostream>

struct Road {
    int from_num;
    int to_num;
    double distance;
};

const Road kRoads[] = {
    {0, 1, 15.5},
    {1, 2, 10.0},
    {2, 3, 25.6},
    {3, 4, 13.6},
    {4, 5, 20.8},
    {5, 6, 5.8},
    {6, 7, 6.7},
    {7, 8, 9.3},
    {8, 9, 12.9},
    {9, 0, 15.8},
    {4, 7, 5.7},
    {5, 8, 10.6},
    {6, 9, 13.6},
    {7, 0, 7.8},
    {8, 1, 30.0},
    {9, 2, 2.6}
};

int used[10] = {};

double dfs(int v, double s, int n)
{
    if(used[v])
    {
        if(n == 10 && v == 0)
        {
            return s;
        }
        return -1.0;
    }
    double a = -1.0;
    double t;
    for(auto r:kRoads)
    {
        if(r.from_num == v)
        {
            t = dfs(r.to_num, s + r.distance, n + 1);
            if(t != -1.0)
            {
                if(a == -1.0)
                {
                    a = t;
                }
                else
                {
                    a = std::min(a, t);
                }
            }
        }
        if(r.to_num == v)
        {
            t = dfs(r.from_num, s + r.distance, n + 1);
            if(t != -1.0)
            {
                if(a == -1.0)
                {
                    a = t;
                }
                else
                {
                    a = std::min(a, t);
                }
            }
        }
    }
    return a;
}

void test()
{
    assert(dfs(0, 0.0, 0) == 122.2);
}

int main()
{
    double d = dfs(0, 0.0, 0);
    if(d == -1)
    {
        std::cout << "The problem is unsolvable";
    }
    else
    {
        std::cout << d;
    }
    return 0;
}
