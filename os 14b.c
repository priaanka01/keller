#include <stdio.h>
int main() {
    int i, j, k, n, fno, a[50], frame[10], lru[10];
    int pagefault = 0, avail, pos = 0;
    printf("Enter the number of frames: ");
    scanf("%d", &fno);
    printf("Enter the number of reference strings: ");
    scanf("%d", &n);
    printf("Enter the reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (i = 0; i < fno; i++) {
        frame[i] = -1;
        lru[i] = 0;
    }
    printf("\nLRU Page Replacement Algorithm\n");
    printf("Reference string: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("\nReference %d -> ", a[i]);
        avail = 0;
        for (j = 0; j < fno; j++) {
            if (frame[j] == a[i]) {
                avail = 1;
                lru[j] = 0;
            } else if (frame[j] != -1) {
                lru[j]++;
            }
        }
        if (!avail) {
            int lru_pos = 0;
            for (j = 0; j < fno; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (j == fno) {
                for (j = 1; j < fno; j++) {
                    if (lru[j] > lru[lru_pos])
                        lru_pos = j;
                }
                pos = lru_pos;
            }
            frame[pos] = a[i];
            lru[pos] = 0;
            for (j = 0; j < fno; j++) {
                if (j != pos && frame[j] != -1)
                    lru[j]++;
            }
            pagefault++;
        }
        for (j = 0; j < fno; j++) {
            if (frame[j] != -1)
                printf("%3d", frame[j]);
            else
                printf("  -");
        }
    }
    printf("\n\nTotal Page Faults: %d\n", pagefault);
    return 0;
}
