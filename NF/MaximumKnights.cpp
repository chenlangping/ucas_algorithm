#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

#define maxn 10000000
#define INF 2147483647
int n, m, num = 1;
int S, T;
int head[maxn], dis[maxn], cur[maxn];
bool flag[maxn];
struct node {
    int to, pre, v;
} E[maxn];

using namespace std;

int Cal(int x, int y) {
    return n * (x - 1) + y;
}

bool BFS() {
    for (int i = S; i <= T; i++) {
        dis[i] = -1;
        cur[i] = head[i];
    }
    queue<int> q;
    q.push(S);
    dis[S] = 0;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = head[now]; i; i = E[i].pre) {
            int to = E[i].to;
            if (E[i].v > 0 && dis[to] == -1) {
                dis[to] = dis[now] + 1;
                if (to == T) {
                    return 1;
                }
                q.push(to);
            }
        }
    }
    return dis[T] != -1;
}

void Insert(int from, int to, int v) {
    E[++num].to = to;
    E[num].v = v;
    E[num].pre = head[from];
    head[from] = num;
    E[++num].to = from;
    E[num].v = 0;
    E[num].pre = head[to];
    head[to] = num;
}

int dinic(int x, int flow) {
    if (x == T || flow == 0) {
        return flow;
    }
    int rest = flow;
    for (int &i = cur[x]; i; i = E[i].pre) {
        int to = E[i].to;
        if (dis[to] == dis[x] + 1 && E[i].v > 0) {
            int delta = dinic(to, min(rest, E[i].v));
            E[i].v -= delta;
            E[i ^ 1].v += delta;
            rest -= delta;
        }
    }
    flow -= rest;
    return flow;
}

bool check(int x, int y) {
    if (x <= n && x >= 1 && y <= n && y >= 1 && !flag[Cal(x, y)]) {
        //对马进行确认
        return 1;
    }
    return 0;
}

int read() {
    int i = 0;
    char ch = getchar();
    while (ch <= '9' && ch >= '0') {
        i = i * 10 + ch - '0';
        ch = getchar();
    }
    return i;
}

int main() {
    n = read();
    m = read();
    S = 0, T = n * n + 1;
    int x, y;
    for (int i = 1; i <= m; i++) {
        x = read();
        y = read();
        flag[Cal(x, y)] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (flag[Cal(i, j)]) {
                continue;
            }
            if ((i + j) & 1) {
                Insert(S, Cal(i, j), 1);
                if (check(i + 1, j - 2))Insert(Cal(i, j), Cal(i + 1, j - 2), 1);
                if (check(i + 1, j + 2))Insert(Cal(i, j), Cal(i + 1, j + 2), 1);

                if (check(i - 1, j - 2))Insert(Cal(i, j), Cal(i - 1, j - 2), 1);
                if (check(i - 1, j + 2))Insert(Cal(i, j), Cal(i - 1, j + 2), 1);

                if (check(i + 2, j - 1))Insert(Cal(i, j), Cal(i + 2, j - 1), 1);
                if (check(i + 2, j + 1))Insert(Cal(i, j), Cal(i + 2, j + 1), 1);

                if (check(i - 2, j - 1))Insert(Cal(i, j), Cal(i - 2, j - 1), 1);
                if (check(i - 2, j + 1))Insert(Cal(i, j), Cal(i - 2, j + 1), 1);

            } else {
                Insert(Cal(i, j), T, 1);
            }
        }
    }
    int ans = 0;
    while (BFS()) {
        ans += dinic(S, INF);
    }
    printf("%d", n * n - ans - m);
}
