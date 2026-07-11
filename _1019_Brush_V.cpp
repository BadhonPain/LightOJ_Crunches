#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
const int INF = INT_MAX;

vector<vector<pii>> graph;
vector<int> dist;

void dijkstra(int source)
{
    int n = graph.size();

    dist.assign(n, INF);
    dist[source] = 0;

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, source}); // {distance, vertex}

    while (!pq.empty())
    {
        auto [cost, u] = pq.top();
        pq.pop();

        if (cost > dist[u])
            continue;

        for (auto [v, wt] : graph[u])
        {
            if (dist[u] + wt < dist[v])
            {
                dist[v] = dist[u] + wt;
                pq.push({dist[v], v});
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

        if (dist[N] == INF)
            cout << "Impossible\n";
        else
            cout << dist[N] << '\n';
    }

    return 0;
}