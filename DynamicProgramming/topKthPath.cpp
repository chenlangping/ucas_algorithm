#include <iostream>
#include<stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int row, col, k;
    scanf("%d", &row);
    scanf("%d", &col);
    scanf("%d", &k);

    //grid用来存放数值
    int grid[row][col];

    //获取输入
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int val = 0;
            scanf("%d", &val);
            grid[i][j] = val;
        }
    }

    //res第1个，即res[row][col][0]存的是长度，所以要开k+1
    int res[row][col][k + 1];
    int i = 0, j = 0;
    while (i != row || j != col - 1) {
        j = 0;
        //注意，下面仅仅是给第i行的第一个元素进行赋值
        if (i > 0) {
            //如果不是第一行
            res[i][j][0] = 1;
            res[i][j][1] = res[i - 1][j][1] + grid[i][j];
        } else {
            //如果是第一行
            res[i][j][0] = 1;
            res[i][j][1] = grid[i][j];
        }

        while (j + 1 < col) {
            j++;
            if (i - 1 >= 0) {
                //分别记下左边和上面可以有多少条路
                int left_len = res[i][j - 1][0];
                int up_len = res[i - 1][j][0];

                //初始化长度
                res[i][j][0] = min(left_len + up_len, k);
                int len = res[i][j][0];

                //初始化左边元素和上面的元素，因为要开始遍历它们
                int index_left = 1, index_up = 1;
                for (int index = 1; index <= len; index++) {
                    int left = 0, up = 0;
                    //计算第index+1条路径从左边过来的距离和从上面下来的距离
                    if (index_left <= left_len) {
                        left = res[i][j - 1][index_left];
                    }
                    if (index_up <= up_len) {
                        up = res[i - 1][j][index_up];
                    }

                    //谁大就记录谁，同时把对应的index++
                    if (left > up) {
                        res[i][j][index] = left + grid[i][j];
                        index_left++;
                    } else {
                        res[i][j][index] = up + grid[i][j];
                        index_up++;
                    }
                }
            } else {
                //第一行除了开头第一个元素外的所有元素进行赋值
                res[i][j][0] = 1;
                res[i][j][1] = res[i][j - 1][1] + grid[i][j];
            }
        }
        //开始下一行
        i++;
    }

    //输出结果即可
    int res_len = res[row - 1][col - 1][0];
    for (int i = 1; i < res_len; i++) {
        printf("%d ", res[row - 1][col - 1][i]);
    }
    printf("%d\n", res[row - 1][col - 1][res_len]);
    return 0;
}