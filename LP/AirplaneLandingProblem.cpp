#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;
const int N = 50;
const float err = 1e-10;
const float INF = 1e20;
int n, m;
float a[N][N];
int id[N];

void pivot(int l, int e) {
    swap(id[n + l], id[e]);
    double t = a[l][e];
    a[l][e] = 1;
    for (int j = 0; j <= n; j++) {
        a[l][j] /= t;
    }
    for (int i = 0; i <= m; i++)
        if (i != l && abs(a[i][e]) > err) {
            t = a[i][e];
            a[i][e] = 0;
            for (int j = 0; j <= n; j++) {
                a[i][j] -= a[l][j] * t;
            }
        }
}

bool init() {
    while (true) {
        int e = 0, l = 0;
        for (int i = 1; i <= m; i++) {
            if (a[i][0] < -err && (!l || (rand() & 1))) {
                l = i;
            }
        }
        if (!l) {
            break;
        }
        for (int j = 1; j <= n; j++) {
            if (a[l][j] < -err && (!e || (rand() & 1))) {
                e = j;
            }
        }
        if (!e) {
            return false;
        }
        pivot(l, e);
    }
    return true;
}

bool simplex() {
    while (true) {
        int l = 0, e = 0;
        double MAXINF = INF;
        for (int j = 1; j <= n; j++)
            if (a[0][j] > err) {
                e = j;
                break;
            }
        if (!e) break;
        for (int i = 1; i <= m; i++)
            if (a[i][e] > err && a[i][0] / a[i][e] < MAXINF) {
                MAXINF = a[i][0] / a[i][e];
                l = i;
            }
        if (!l) {
            return false;
        }
        pivot(l, e);
    }
    return true;
}



int main() {
    srand(1);
    n = 6, m = 14;
    float S[10], T[10];
    for (int i = 1; i <= 5; i++) {
        scanf("%f%f", &S[i], &T[i]);
    }
    for (int i = 1; i <= 5; i++) {
        a[0][i] = 0;
    }
    a[0][6] = 1;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= n; j++) {
            if (j == i || j == 6)
                a[i][j] = 1;
            else if (j - 1 == i)
                a[i][j] = -1;
            else
                a[i][j] = 0;
        }
        a[i][0] = 0;
    }
    int k = 1;
    for (int i = 5; i <= 14; i++) {
        if (i % 2 == 1) {
            a[i][0] = T[k];
            for (int j = 1; j <= n; j++) {
                if (j == k)
                    a[i][j] = 1;
                else
                    a[i][j] = 0;
            }

        } else {
            a[i][0] = -S[k];
            for (int j = 1; j <= n; j++) {
                if (j == k)
                    a[i][j] = -1;
                else
                    a[i][j] = 0;
            }
            k++;
        }
    }

    for (int i = 1; i <= n; i++) id[i] = i;
    if (init() && (simplex() + 0.5)) {
        float d = -a[0][0];
        float time[6];
        time[1] = S[1];
        for (int i = 2; i <= 5; i++) {
            //解决精度问题
            float temp = time[i - 1] + d + 0.0005;
            if (temp < S[i])
                time[i] = S[i];
            else
                time[i] = temp;
        }
        for (int i = 1; i < 5; i++)
            printf("%.2f ", time[i]);
        printf("%.2f\n", time[5]);
    }
}
