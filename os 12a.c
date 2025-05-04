#include <stdio.h>
#define MAX 20
int main(void) {
    int n, i, j;
    int blocks[MAX], startBlock[MAX], tempStart[MAX], blockMap[MAX][MAX];
    int fileChoice;
    printf("Enter number of files: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("\nEnter number of blocks occupied by file %d: ", i + 1);
        scanf("%d", &blocks[i]);
        printf("Enter the starting block of file %d: ", i + 1);
        scanf("%d", &startBlock[i]);
        tempStart[i] = startBlock[i];
        for (j = 0; j < blocks[i]; j++) {
            blockMap[i][j] = startBlock[i]++;
        }
    }
    printf("\nFilename\tStart block\tLength\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\n", i + 1, tempStart[i], blocks[i]);
    }
    printf("\nEnter file number to view details: ");
    scanf("%d", &fileChoice);

    if (fileChoice < 1 || fileChoice > n) {
        printf("Invalid file number!\n");
        return 1;
    }
    fileChoice--;
    printf("\nFile name: %d", fileChoice + 1);
    printf("\nLength (number of blocks): %d", blocks[fileChoice]);
    printf("\nBlocks occupied: ");
    for (i = 0; i < blocks[fileChoice]; i++) {
        printf("%4d", blockMap[fileChoice][i]);
    }
    printf("\n");
    return 0;
}
