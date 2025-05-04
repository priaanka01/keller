#include <stdio.h>
void main() {
    int i, j, m, size, val[10][10], badd[10], limit[10], ladd;
    printf("Enter the size of the segment table: ");
    scanf("%d", &size);
    for(i = 0; i < size; i++) {
        printf("\nEnter information about segment %d", i + 1);
        printf("\nEnter base address: ");
        scanf("%d", &badd[i]);
        printf("Enter the limit: ");
        scanf("%d", &limit[i]);
        for(j = 0; j < limit[i]; j++) {
            printf("Enter address value at logical address %d: ", badd[i] + j);
            scanf("%d", &val[i][j]);
        }
    }
    printf("\n\n****SEGMENT TABLE****");
    printf("\nSegment No.\tBase Address\tLimit");
    for(i = 0; i < size; i++) {
        printf("\n%d\t\t%d\t\t%d", i + 1, badd[i], limit[i]);
    }
    printf("\n\nEnter segment number: ");
    scanf("%d", &i);
    if(i < 1 || i > size) {
        printf("Invalid segment number!\n");
    } else {
        i--;
        printf("Enter the logical address: ");
        scanf("%d", &ladd);
        if(ladd >= limit[i]) {
            printf("Invalid logical address!\n");
        } else {
            m = badd[i] + ladd;
            printf("\nMapped physical address: %d", m);
            printf("\nThe value at this address is: %d\n", val[i][ladd]);
        }
    }
}
