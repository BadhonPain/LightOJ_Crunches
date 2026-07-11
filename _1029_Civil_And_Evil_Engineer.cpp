#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, ll, ll> Edge;

vector<ll> parent, sz;

void initialize(ll n)
{
    parent.resize(n + 1);
    sz.assign(n + 1, 1);

    for (ll i = 0; i <= n; i++)
        parent[i] = i;
}

ll findSet(ll node)
{
    if (parent[node] == node)
        return node;
    return parent[node] = findSet(parent[node]);
}

void unionSet(ll u, ll v)
{
    ll pu = findSet(u);
    ll pv = findSet(v);

    if (pu == pv)
        return;

    if (sz[pu] >= sz[pv])
    {
        parent[pv] = pu;
        sz[pu] += sz[pv];
    }
    else
    {
        parent[pu] = pv;
        sz[pv] += sz[pu];
    }
}

ll kruskal(vector<Edge> edges, ll n, bool minimum)
{
    initialize(n);

    if (minimum)
        sort(edges.begin(), edges.end());
    else
        sort(edges.rbegin(), edges.rend());

    ll cost = 0;

    for (auto &[w, u, v] : edges)
    {
        if (findSet(u) != findSet(v))
        {
            unionSet(u, v);
            cost += w;
        }
    }

    return cost;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        ll n;
        cin >> n;

        vector<Edge> edges;

        while (true)
        {
            ll u, v, w;
            cin >> u >> v >> w;

            if (u == 0 && v == 0 && w == 0)
                break;

            edges.push_back({w, u, v});
        }

        ll minCost = kruskal(edges, n, true);
        ll maxCost = kruskal(edges, n, false);

        ll sum = minCost + maxCost;

        cout << "Case " << tc << ": ";

        if (sum % 2 == 0)
            cout << sum / 2 << '\n';
        else
            cout << sum << "/2\n";
    }

    return 0;
}