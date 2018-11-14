#include <iostream>
#include <algorithm>

using namespace std;

int numOfPeople;
int people[5000000];
int boat;
//flag用来记录这艘船是不是只装了一个人，因为需要考虑只能装一个人的情况
bool flag = false;

bool compare(int a, int b) {
    return a > b;
}

int main() {
    int res = 0;

    scanf("%d", &numOfPeople);
    scanf("%d", &boat);

    for (int i = 0; i < numOfPeople; i++) {
        scanf("%d", &people[i]);
    }


    sort(people, people + numOfPeople, compare);

    while (true) {
        for (int i = 0; i < numOfPeople; i++) {
            if (people[i] != -1) {
                flag = false;
                for (int j = i + 1; j < numOfPeople; j++) {
                    if (people[j] == -1) {
                        continue;
                    }
                    if (people[i] + people[j] <= boat) {
                        people[i] = -1;
                        people[j] = -1;
                        res++;
                        flag = true;
                        break;
                    }
                }
                if (flag == false) {
                    res++;
                    people[i] = -1;
                    flag = true;
                }
            }
        }
        break;
    }

    printf("%d", res);
    return 0;
}