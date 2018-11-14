#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int random_partion(int *p, int n) {
    int idx = rand() % n;
    swap(p[idx], p[n - 1]);
    int i = -1;    //i表示最后一个小于p[n-1]的元素的位置
    int j = 0;     //j用来扫描数组
    for (j = 0; j < n; j++) {
        //将小于p[n-1]的数交换到前半部分
        if (p[j] < p[n - 1]) {
            swap(p[++i], p[j]);
        }
    }
    swap(p[++i], p[n - 1]);
    return i;
}

int getMaxK(int *p, int n, int k) {
    int mid;
    if (k <= 0)
        return -1;
    if (n < k)
        return -1;
    mid = random_partion(p, n);   //对原数组进行一次划分
    if (mid == n - k)      //如果mid==n-k，那么返回该值，这就是第k大的数
        return p[mid];
    else if (mid < n - k)
        return getMaxK(p + mid + 1, n - mid - 1, k);  //如果mid<n-k，那么第k大的数在右半数组，而且仍然是第k大数
    else
        return getMaxK(p, mid, k - (n - mid));   //如果mid>n-k，那么第k大的数在左半数组，且在左半数组中是第k-(n-mid)大的数
}


int main() {
    int numsLen = 0;
    while (scanf("%d", &numsLen) != EOF) {
        int *nums = new int[numsLen];
        int k = 0;
        int i = 0;
        scanf("%d", &k);
        for (i = 0; i < numsLen; i++) {
            scanf("%d", &nums[i]);
        }
        printf("%d\n", getMaxK(nums,numsLen,k));
    }
    return 0;
}

