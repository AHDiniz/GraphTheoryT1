#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

#define INFINITY (INT_MAX - 10)

template<typename T>
inline void remove(std::vector<T> &v, const T e)
{
    v.erase(std::remove(v.begin(), v.end(), e), v.end());
}

template<typename T>
inline bool contains(std::vector<T> v, const T e)
{
    return std::find(v.begin(), v.end(), e) != v.end();
}

class Graph
{
public:
    Graph(int n, int m);

    inline void set(const int u, const int v) { adj[u * n + v] = 1; }
    inline void unset(const int u, const int v) { adj[u * n + v] = 0; }
    inline int get(const int u, const int v) const { return adj[u * n + v]; }

    const int dijkstra(int s, int e) const;
private:
    int n, m;
    std::vector<int> adj;
};

int main(void)
{
    while (!std::cin.eof())
    {
        int n, m;
        std::cin >> n >> m;

         Graph* g = new Graph(n, m);

        for (int i = 0; i < m; i++)
        {
            int u, v;
            std::cin >> u >> v;
            g->set(u - 1, v - 1);
            g->set(v - 1, u - 1);
        }

        int c, r, e;
        std::cin >> c >> r >> e;

        for (int i = 0; i < n; i++)
        {
            g->unset(i, e - 1);
            g->unset(e - 1, i);
        }

        std::cout << g->dijkstra(c - 1, r - 1) << std::endl;
        delete g;
    }

    return 0;
}

Graph::Graph(int n, int m)
{
    this->n = n;
    this->m = m;

    for (int i = 0; i <= n * n; ++i)
        adj.push_back(0);
}

const int Graph::dijkstra(int s, int e) const
{
    std::vector<int> costs;
    std::vector<int> closed;

    for (int i = 0; i < n; ++i)
    {
        if (i == s) costs.push_back(0);
        else costs.push_back(INFINITY);
    }

    while (closed.size() != n)
    {
        int closest = 0;
        for (int i = 0; i < n; ++i)
            if (!contains(closed, i))
                closest = (costs[i] < costs[closest]) ? i : closest;
        closed.push_back(closest);
        for (int i = 0; i < n; ++i)
        {
            if (!contains(closed, i) && get(closest, i))
            {
                int c = get(closest, i) + costs[closest];
                costs[i] = (costs[i] < c) ? costs[i] : c;
            }
        }
    }
    
    return costs[e];
}
