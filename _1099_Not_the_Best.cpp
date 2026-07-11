#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
const int INF = INT_MAX;

vector<vector<pii>> graph;
vector<int> shortest_dist;
vector<int> sec_short_dist;

void dijkstra(int source)
{
    int n = graph.size();

    shortest_dist.assign(n, INF);
    sec_short_dist.assign(n, INF);

    shortest_dist[source] = 0;

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, source});

    while (!pq.empty())
    {
        auto [cost, u] = pq.top();
        pq.pop();

        if (cost > sec_short_dist[u])
            continue;

        for (auto [v, wt] : graph[u])
        {
            int newDist = shortest_dist[u] + wt;
            if (newDist < shortest_dist[v])
            {
                swap(shortest_dist[v], newDist);
                pq.push({shortest_dist[v], v});
            }

            if (newDist > shortest_dist[v] && newDist < sec_short_dist[v])
            {
                sec_short_dist[v] = newDist;
                pq.push({sec_short_dist[v], v});
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        int N, M;
        cin >> N >> M;

        graph.assign(N + 1, {});

        while (M--)
        {
            int u, v, w;
            cin >> u >> v >> w;

            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        dijkstra(1);

        cout << "Case " << tc << ": ";

        if (shortest_dist[N] == INF)
            cout << "Impossible\n";
        else
            cout << shortest_dist[N] << '\n';
    }

    return 0;
}