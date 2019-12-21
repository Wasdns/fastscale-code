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



int main()
{
	scanf("%lld",&m);
	n = M*m;
	dag();
	for(ll i = 1; i <= n; i++)
	{
		for(ll j = 0; j < g[i].size(); j++)
		{
			printf("%lld %lld %lld\n", i, g[i][j].next, g[i][j].dis);
		}
	}
	
	return 0;
}
