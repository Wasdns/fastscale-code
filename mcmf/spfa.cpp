#include <bits/stdc++.h>
#define MAXN 501
#define INF 99999
using namespace std;
typedef long long ll;

struct Edge
{
	ll next, dis;

	Edge(ll _next, ll _dis)
	{
		next = _next;
		dis = _dis;
	}
};

vector<Edge> g[MAXN]; //ÁÚ½Ó±í

//ll m[MAXN][MAXN]; //ÁÚ½Ó¾ØÕó

ll n,m;
ll dis[MAXN], vis[MAXN], pre[MAXN];
ll src, dst;

void SPFA()
{
	queue<ll>  q;
	for(ll i = 1; i <= n; i++)
	{
		dis[i] = INF;
	}
	memset(vis, 0, sizeof(vis));
	q.push(src);
	vis[src] = 1;
	dis[src] = 0;
	while(!q.empty())
	{
		ll u = q.front();
		q.pop();
		vis[u] = 0;
		for(ll i = 0; i < g[u].size(); i++)
		{
			ll v = g[u][i].next;
			if(dis[v] > dis[u] + g[u][i].dis)
			{
				dis[v] = dis[u] + g[u][i].dis;
				pre[v] = u;
				if(vis[v] == 0)
				{
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	}
}

void add(ll a,ll b,ll d)
{
	g[a].push_back(Edge(b, d));
	//m[a][b] = d;
}

int main()
{
	scanf("%lld%lld", &n, &m);
	ll a, b, d;
	for (ll i = 1; i <= m; i++)
	{
		scanf("%lld%lld%lld", &a, &b, &d);
		add(a, b, d);
	}
	src = 1;
	dst = n;
	while(1)
	{
		memset(vis, 0, sizeof(pre));
		SPFA();
		if(dis[dst] == INF)
		{
			break;
		}	
		printf("The shortest distance from %lld to %lld is %lld\n", src, dst, dis[dst]);
		ll  l = pre[dst], r = dst;
		printf("The shortest path from %d to %d is %d ", dst, src, r);
		while(l != 0)
		{
			printf("-> %d ", l);
			for(int i = 0; i < g[l].size(); i++)
			{
				if(g[l][i].next == r)
				{
					g[l][i].dis = INF;
					break;
				}
			}
			r = l;
			l = pre[l];
		}
		printf("\n");
	}


	return 0;
}
