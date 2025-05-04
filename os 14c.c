#include <stdio.h>
int main() {
    int i, j, k, n, fno, a[50], frame[10], flag, min, pagefault = 0;
    printf("\nEnter the number of frames: ");
    scanf("%d", &fno);
    printf("\nEnter the number of reference strings: ");
    scanf("%d", &n);
    printf("\nEnter the reference string:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (i = 0; i < fno; i++) {
        frame[i] = -1;
    }
    printf("\nOptimal Page Replacement Algorithm\n");
    printf("The given reference string is:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("\nReference No %d -> ", a[i]);
        flag = 0;
        for (j = 0; j < fno; j++) {
            if (frame[j] == a[i]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            int farthest = -1, replace = -1;
            for (j = 0; j < fno; j++) {
                int found = 0;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == a[k]) {
                        found = 1;
                        break;
                    }
                }
                if (found == 0) {
                    replace = j;
                    break;
                }
                if (found == 1) {
                    if (k > farthest) {
                        farthest = k;
                        replace = j;
                    }
                }
            }
            frame[replace] = a[i];
            pagefault++;
            for (j = 0; j < fno; j++) {
                if (frame[j] != -1)
                    printf(" %2d", frame[j]);
                else
                    printf("  -");
            }
        }
    }
    printf("\n\nTotal Page Faults: %d\n", pagefault);
    return 0;
}
