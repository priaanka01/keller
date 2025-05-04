#include <stdio.h>
int main() {
    int i, sn;
    int st[20];
    char op;
    printf("How many stations: ");
    scanf("%d", &sn);
    do {
        printf("\nEnter status of stations:\n");
        for (i = 0; i < sn; i++) {
            printf("Enter status of station %d (0 or 1): ", i + 1);
            scanf("%d", &st[i]);
        }
        printf("\nStations ready to transmit:");
        for (i = 0; i < sn; i++) {
            if (st[i] == 1) {
                printf("\nStation %d is ready to transmit", i + 1);
            }
        }
        printf("\n\nRepeat? Press Y/y to continue: ");
        scanf(" %c", &op);
    } while (op == 'y' || op == 'Y');
    return 0;
}
