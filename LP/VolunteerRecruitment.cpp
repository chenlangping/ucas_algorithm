#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;
const int INF = 1e9 + 10;
const double eps = 1e-8;
int N, M;
long long a[10001][1001];

inline int read() {
    char c = getchar();
    int x = 0, f = 1;
    while (c < '0' || c > '9') {
        if (c == '-') {
            f = -1;
        }
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}


void pivot(int l, int e) {
    double t = a[l][e];
    a[l][e] = 1;
    for (int i = 0; i <= N; i++) {
        a[l][i] /= t;
    }
    for (int i = 0; i <= M; i++) {
        if (i != l && abs(a[i][e]) > eps) {
            t = a[i][e];
            a[i][e] = 0;
            for (int j = 0; j <= N; j++)
                a[i][j] -= a[l][j] * t;
        }
    }
}

bool simplex() {
    while (1) {
        int l = 0, e = 0;
        double mn = INF;
        for (int i = 1; i <= N; i++)
            if (a[0][i] > eps) {
                e = i;
                break;
            }
        if (!e) break;
        for (int i = 1; i <= M; i++)
            if (a[i][e] > eps && a[i][0] / a[i][e] < mn)
                mn = a[i][0] / a[i][e], l = i;
        pivot(l, e);
    }
    return 1;
}

int main() {
    N = read();
    M = read();
    for (int i = 1; i <= N; i++) a[0][i] = read();
    for (int i = 1; i <= M; i++) {
        int S = read(), T = read(), C = read();
        for (int j = S; j <= T; j++)
            a[i][j] = 1;
        a[i][0] = C;
    }
    simplex();
    printf("%lld", -a[0][0]);
    return 0;
}
