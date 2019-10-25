#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
inline void remove(std::vector<T> &v, const T e)
{
	v.erase(std::remove(v.begin(), v.end(), e), v.end());
}

template<typename T>
inline bool contains(const std::vector<T> &v, const T e)
{
	return std::find(v.begin(), v.end(), e) != v.end();
}

class Graph
{
public:
    Graph(int n, int m);
    inline void set(int i, int j)
	{
		adj[i * n + j] = 1;
		// visited[i * n + j] = 1;
	}
    inline int get(int i, int j) const { return adj[i * n + j]; }

    const int dfs(int v);

private:
    int n, m;
    std::vector<int> adj;
    std::vector<int> visited;
};

int main(void)
{
    int n, m;
    std::cin >> n >> m;

    while (n != 0 && m != 0)
    {
        Graph g(n, m);

        for (int i = 0; i < m; ++i)
        {
            int u, v, c;
            std::cin >> u >> v >> c;
            g.set(u - 1, v - 1);
            if (c == 2)
                g.set(v - 1, u - 1);
        }

        bool satisfies = true;
        for (int i = 0; i < n; ++i)
        {
            int count = g.dfs(i);
            if (count < n)
            {
                satisfies = false;
                break;
            }
        }
        std::cout << satisfies << std::endl;

        std::cin >> n >> m;
    }

    return 0;
}

Graph::Graph(int n, int m)
{
    this->n = n;
    this->m = m;

    for (int i = 0; i < n * n; ++i)
        adj.push_back(0);
    
    for (int i = 0; i < n * n; ++i)
        visited.push_back(0);
}

const int Graph::dfs(int v)
{
    std::vector<int> _visited;
    for (int i = 0; i < n; ++i)
    {
        if (i == v) _visited.push_back(1);
        else _visited.push_back(0);
    }

    std::vector<int> stack;
    stack.push_back(v);

    while (!stack.empty())
    {
        int u = stack[stack.size() - 1];
        for (int i = 0; i < n; ++i)
        {
            if (get(u, i) && !_visited[i])
            {
                _visited[i] = 1;
                for (int j = 0; j < n; ++j)
                    if (visited[u * n + j] && !_visited[j])
                        _visited[j] = visited[u * n + j];
                stack.push_back(i);
            }
        }
        remove(stack, u);
    }

    for (int i = 0; i < n; ++i)
        if (_visited[i])
            visited[v * n + i] = 1;

    int count = 0;
    for (int i : _visited)
        count += (i) ? 1 : 0;

    return count;
}
