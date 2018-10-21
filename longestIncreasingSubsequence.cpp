#include <iostream>

using namespace std;

int binarySearch(int *a, int fromIndex, int toIndex, int key) {
    int low = fromIndex;
    int high = toIndex - 1;

    while (low <= high) {
        int mid = (low + high) >> 1;
        int midVal = a[mid];

        if (midVal < key)
            low = mid + 1;
        else if (midVal > key)
            high = mid - 1;
        else
            return mid; // key found
    }
    return -(low + 1);  // key not found.
}

int lengthOfLIS(int *nums, int numsLen) {
    int *dp = new int[numsLen];
    for (int i = 0; i < numsLen; i++) {
        dp[i] = 0;
    }
    int len = 0;
    for (int j = 0; j < numsLen; j++) {
        int num = nums[j];
        int i = binarySearch(dp, 0, len, num);
        if (i < 0) {
            i = -(i + 1);
        }
        dp[i] = num;
        if (i == len) {
            len++;
        }
    }
    return len;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int m;
        scanf("%d", &m);
        int *nums = new int[m];
        for (int j = 0; j < m; j++) {
            scanf("%d", &nums[j]);
        }
        int result = lengthOfLIS(nums,m);
        printf("%d\n",result);
    }
    return 0;
}