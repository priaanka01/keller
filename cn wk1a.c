#include <stdio.h>

void bitstuffing(int N, int arr[]) {
    int count = 0;
    int i, j = 0;

    int stuffedArr[2 * N];

    for (i = 0; i < N; i++) {
        stuffedArr[j++] = arr[i];
        if (arr[i] == 1) {
            count++;
            if (count == 5) {
                stuffedArr[j++] = 0;
                count = 0;
            }
        } else {
            count = 0;
        }
    }

    for (i = 0; i < j; i++) {
        printf("%d", stuffedArr[i]);
    }
    printf("\n");
}

int main() {
    int N = 6;
    int arr[] = {1,1,1,1,1,1};

    printf("Input binary array: ");
    for (int i = 0; i < N; i++) {
        printf("%d", arr[i]);
    }
    printf("\n");

    printf("After bit stuffing: ");
    bitstuffing(N, arr);

    return 0;
}

