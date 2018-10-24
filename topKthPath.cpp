#include <iostream>
#include <stdio.h>
#include <list>


using namespace std;

list<int> l1;
int **dp;
int **nums;
int c = 0;
int k;
int min = 0;

void getTopKthPath(int row, int col);

void getResult(int row, int col, int sum);

void getTopKthPath(int row, int col) {

    dp = new int *[row];

    for (int i = 0; i < row; i++) {
        dp[i] = new int[col];
    }

    dp[0][0] = nums[0][0];
    //初始化dp的第一列
    for (int i = 1; i < row; i++) {
        dp[i][0] = dp[i - 1][0] + nums[i][0];
    }

    //初始化dp的第一行
    for (int j = 1; j < col; j++) {
        dp[0][j] = dp[0][j - 1] + nums[0][j];
    }


    //递归计算dp
    for (int i = 1; i < row; i++) {
        for (int j = 1; j < col; j++) {
            int left = dp[i][j - 1] + nums[i][j];
            int up = dp[i - 1][j] + nums[i][j];
            if (left > up) {
                dp[i][j] = left;
            } else {
                dp[i][j] = up;
            }
        }
    }
    getResult(row - 1, col - 1, 0);
    delete (dp);
}

void getResult(int row, int col, int sum) {
    if (row == 0 || col == 0) {
        int distance = dp[row][col] + sum;
        l1.push_back(distance);
        return;
    }
    sum += nums[row][col];
    getResult(row - 1, col, sum);
    getResult(row, col - 1, sum);
}

int main() {
    int row, col;
    list<int>::iterator iter;
    scanf("%d %d", &row, &col);
    scanf("%d", &k);
    nums = new int *[row];
    for (int i = 0; i < row; i++) {
        nums[i] = new int[col];
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", &nums[i][j]);
        }
    }

    getTopKthPath(row, col);
    l1.sort();
    l1.reverse();
    int count = 1;
    for (iter = l1.begin(); iter != l1.end(); iter++, count++) {
        if (count == k) {
            cout << *iter;
            return 0;
        }
        cout << *iter << " ";

    }

    while (count < k) {
        cout << 0 << " ";
        count++;
    }
    cout << 0;
    l1.clear();
    delete (nums);
    return 0;
}