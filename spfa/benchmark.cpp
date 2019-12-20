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
vector<Edge> g[MAXN]; //邻接表

ll M = 5; //一共多少层，默认是5
ll m = 3; // 每层多少结点，默认是3
ll loop = 1000; //循环次数，默认是1000
ll n; //总共有多少结点，n=M*m
ll src, dst; //源结点，目的结点，默认为1和n
ll dis[MAXN], vis[MAXN], pre[MAXN];



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
		else if (strcmp(argv[i], "-M") == 0)
		{
			M = atoi(argv[i + 1]);
		}
		else if (strcmp(argv[i], "-l") == 0)
		{
			loop = atoi(argv[i + 1]);
		}
	}
	n = M*m;
	if(n >= 501)
	{
		printf("The value of N is up to 500 and the value entered is %lld\n",n);
		return 0;
	}
	dag();
	//	for(ll i = 1; i <= n; i++)
	//	{
	//		for(ll j = 0; j < g[i].size(); j++)
	//		{
	//			printf("%lld %lld %lld\n", i, g[i][j].next, g[i][j].dis);
	//		}
	//	}
	src = 1;
	dst = n;
	clock_t start,end;
	start = clock();
	for(ll l = 0; l < loop; l++)
	{
		while(1)
		{
			memset(vis, 0, sizeof(pre));
			SPFA();
			if(dis[dst] == INF)
			{
				break;
			}
			//printf("The shortest distance from %lld to %lld is %lld\n", src, dst, dis[dst]);
			ll  l = pre[dst], r = dst;
			//printf("The shortest path from %d to %d is %d ", dst, src, r);
			while(l != 0)
			{
				//printf("-> %d ", l);
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
			//printf("\n");
		}
	}
	end = clock();
	printf("The time taken to execute the program is %lf ms", (double)(end - start) / CLOCKS_PER_SEC / loop);
	return 0;
}
