#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

#define CAN_NOT_REACH 1000000001
#define MAX 7

/**
 * 自定义数据结构Point，便于之后计算
 */
typedef struct Point {
    double x;
    double y;
} Point;


/**
 * 返回两个点的欧式距离
 * @param a
 * @param b
 * @return
 */
double getDistance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

/**
 * 按照从小到大的顺序排列
 * @param a
 * @param b
 * @return
 */
bool compByX(Point a, Point b) {
    return a.x < b.x;
}

bool compByY(Point a, Point b) {
    return a.y < b.y;
}

double getMinimalDistance(Point *points, int length) {
    //distance是最后最短的两个点的距离
    double distance;
    //d1d2用来记录两个子问题中最短的距离
    double d1, d2;
    //初始化循环变量
    int i = 0;
    int j = 0;
    int k = 0;
    //特殊情况排除，但是OJ说了最小是2，所以其实可以不用写
    if (length < 2) {
        return CAN_NOT_REACH;
    }
    if (length == 2) {
        //如果只有两个点
        distance = getDistance(points[0], points[1]);
        return distance;
    } else {
        Point *points1 = new Point[length];
        Point *points2 = new Point[length];
        //为了求解中位数，需要先进行排序
        sort(points, points + length, compByX);
        //求解中位数
        double mid = points[(length - 1) / 2].x;
        for (i = 0; i < length / 2; i++) {
            points1[i] = points[i];
        }
        for (int j = 0, i = length / 2; i < length; i++) {
            points2[j++] = points[i];
        }
        //求解左半部分
        d1 = getMinimalDistance(points1, length / 2);
        //求解右半部分
        d2 = getMinimalDistance(points2, length - length / 2);
        if (d1 < d2) {
            distance = d1;
        } else {
            distance = d2;
        }
        Point *points3 = new Point[length];
        for (i = 0, k = 0; i < length; i++) {
            if (abs(points[i].x - mid) < distance) {
                points3[k++] = points[i];
            }
        }
        for (i = 0; i < k; i++) {
            for (j = i + 1; j < k && j <= i + MAX; j++) {
                if (abs(points3[i].y - points3[j].y) >= distance) {
                    continue;
                }
                double d4 = getDistance(points3[i], points3[j]);
                if (d4 < distance) {
                    //发现有一对跨越中间线的点的距离小于目前最小的
                    distance = d4;
                }
            }
        }
        free(points1);
        free(points2);
        free(points3);
    }
    return distance;
}


int main() {
    int n;
    double diatance;
    while (scanf("%d", &n) != EOF) {
        Point *points = new Point[n];
        for (int i = 0; i < n; i++) {
            scanf("%lf", &points[i].x);
            scanf("%lf", &points[i].y);
        }
        diatance = getMinimalDistance(points, n);
        printf("%.2lf\n", diatance);
    }
    return 0;
}
