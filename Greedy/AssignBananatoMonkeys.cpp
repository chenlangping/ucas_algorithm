#include <iostream>
#include <algorithm>

using namespace std;

int a[3000000];
int monkey[3000000];
int banana[5000000];

int main() {
    int num = 0;
    while (scanf("%d", &a[num]) != EOF) {
        num++;
    }
    num = num / 2;
    for (int i = 0; i < num; i++) {
        monkey[i] = a[i];
    }
    for (int i = 0; i < num; i++) {
        banana[i] = a[i + num];
    }
    sort(monkey, monkey + num);
    sort(banana, banana + num);
    int max = monkey[0] - banana[0] > 0 ? monkey[0] - banana[0] : banana[0] - monkey[0];
    for (int i = 0; i < num; i++) {
        int a = monkey[i] - banana[i] >= 0 ? monkey[i] - banana[i] : banana[i] - monkey[i];
        if (a > max) {
            max = a;
        }
    }
    printf("%d", max);
    return 0;
}