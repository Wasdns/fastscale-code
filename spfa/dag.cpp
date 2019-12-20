#include <bits/stdc++.h>
#define M 3 //一共多少层
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
vector<Edge> g[MAXN]; //邻接表

ll m; // 每层多少结点
ll n;
ll dis[MAXN], vis[MAXN], pre[MAXN];
ll src, dst;



void dag()
{
	ll no = 1;
	for(ll i = 1; i <= n; i++)
	{
		ll layer = ((i-1)/m)+1;
		for(ll j = 1; j <= m; j++)
		{
			if(layer*m+j <= n)
			{
				g[i].push_back(Edge(layer*m+j, no++));
			}
		}
	}
}

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


int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-m") == 0)
		{
			m = atoi(argv[i + 1]);
		}
	}
	n = M*m;
	dag();
	for(ll i = 1; i <= n; i++)
	{
		for(ll j = 0; j < g[i].size(); j++)
		{
			printf("%lld %lld %lld\n", i, g[i][j].next, g[i][j].dis);
		}
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
