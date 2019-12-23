#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

#define MAXN 1000000
typedef long long ll;

ll a[MAXN];

void fastscale_toposort(ll n, ll input) {
    sort(a, a+n);
    for (int i = 1; i < n; i++) {
        ll input = input;
        if (a[i] != 0) ll num = (input/a[i])+1;
        a[i] = input;
    }
}

int main(int argc, char *argv[]) {
    ll n;
    ll loop;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            n = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-l") == 0)
        {
            loop = atoi(argv[i + 1]);
        }
    }
    for (int i = 1; i <= n; i++) {
        a[i] = 50;
    }
    clock_t start, end;
    start = clock();
    for (ll l = 0; l < loop; l++) {
        fastscale_toposort(n, 100);
    }
    end = clock();
    printf("After %lld runs, the average time is %lf s\n", loop, (double)(end - start)/CLOCKS_PER_SEC/loop);
    return 0;
}
