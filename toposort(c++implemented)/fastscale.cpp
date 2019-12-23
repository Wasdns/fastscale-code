#include <bits/stdc++.h>
#define MAXN 501
#define ROOT 1
#define INF 99999
using namespace std;
typedef long long ll;

struct Edge
{
	ll from, to, weight;

	Edge() {}

	Edge(ll _from, ll _to, ll _weight)
	{
		from = _from;
		to = _to;
		weight = _weight;
	}
};

vector<Edge> g[MAXN];

ll root_rate;
ll capacities[MAXN];
ll scale_out_plan[MAXN] = {0};
ll n,m;

void add(ll a,ll b,ll d)
{
	g[a].push_back(Edge(-1, b, d));
	g[b].push_back(Edge(a, -1, d));
}


void fastscale()
{
	/*start from root (1), iterate through every NF*/
	ll current = 1;
	ll in_rate = 0;
	for(ll i = 1; i <= n; i++)
	{
		/*calculate input rate*/
		if(i == ROOT) /*i.e., if len(predecessors) == 0*/
		{
			in_rate = root_rate;
			//printf("i: %lld in_rate:%lld\n",i, in_rate);
		}
		else
		{
			for(auto v:g[i])
			{
				if(v.to == -1)
				{
					ll rate_pre2current = v.weight;
					in_rate += rate_pre2current;
				}
			}
			//printf("i: %lld in_rate:%lld\n",i, in_rate);
		}
		/*calculate scale-out plan*/
		ll current_capacity = capacities[current];
		ll num = (ll)ceil(in_rate*1.0/current_capacity*1.0);
		scale_out_plan[current] = num;

		/*update output edge capacity*/
		ll new_out_rate = in_rate;
		ll old_out_rate = 0;
		if(i != n) /*if len(successors) != 0*/
		{
			/*calculate old_out_rate*/
			for(auto v:g[i])
			{
				if(v.from == -1)
				{
					ll rate_current2succ = v.weight;
					old_out_rate += rate_current2succ;
				}
			}
			/*update output edge weight*/
			for(auto v:g[i])
			{
				if(v.from == -1)
				{
					ll rate_current2succ = v.weight;
					double proportion = rate_current2succ*1.0/old_out_rate*1.0;
					ll new_rate_current2succ = (ll)new_out_rate*proportion;
					v.weight = new_rate_current2succ;
					for(ll j = 0;j < g[v.to].size();j++)
					{
						if(g[v.to][j].from == i && g[v.to][j].to == -1)
						{
							g[v.to][j].weight = new_rate_current2succ;
						} 
					} 
				}
			}
		}
		in_rate = 0;
		current = current+1;
	}
}

int main()
{


	root_rate = 100;
	add(1, 2, 30);
	add(1, 3, 20);
	add(2, 4, 30);
	add(3, 4, 20);	
	capacities[1] = 50;
	capacities[2] = 30;
	capacities[3] = 10;
	capacities[4] = 50;
	n = 4;
//	for(ll i = 1; i <= n; i++)
//	{
//		for(ll j = 0; j < g[i].size(); j++)
//		{
//			printf("%lld %lld %lld %lld\n", i, g[i][j].from, g[i][j].to, g[i][j].weight);
//		}
//	}
	fastscale();
	for(ll i = 1; i <= n; i++)
	{
		printf("the %lld-th NF needs: %lld instances\n", i, scale_out_plan[i]);
	}
//	for(ll i = 0; i <= n; i++)
//	{
//		for(ll j = 0; j < g[i].size(); j++)
//		{
//			printf("%lld %lld %lld %lld\n", i, g[i][j].from, g[i][j].to, g[i][j].weight);
//		}
//	}
	return 0;
}

