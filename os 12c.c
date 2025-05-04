#include <stdio.h>
int main() {
    int n, i, j, fileLength[20], indexBlock[20], blocks[20][20], fileChoice;
    printf("Enter number of files: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("\nEnter index block of file %d: ", i + 1);
        scanf("%d", &indexBlock[i]);
        printf("Enter length (number of blocks) of file %d: ", i + 1);
        scanf("%d", &fileLength[i]);
        printf("Enter block numbers for file %d:\n", i + 1);
        for (j = 0; j < fileLength[i]; j++) {
            scanf("%d", &blocks[i][j]);
        }
    }
    printf("\nFile\tIndex Block\tLength\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", i + 1, indexBlock[i], fileLength[i]);
    }
    printf("\nEnter file number to view its blocks: ");
    scanf("%d", &fileChoice);
    if (fileChoice < 1 || fileChoice > n) {
        printf("Invalid file number!\n");
        return 1;
    }
    fileChoice--;
    printf("\nFile Number: %d", fileChoice + 1);
    printf("\nIndex Block: %d", indexBlock[fileChoice]);
    printf("\nBlocks occupied are: ");
    for (j = 0; j < fileLength[fileChoice]; j++) {
        printf("%4d", blocks[fileChoice][j]);
    }
    printf("\n");
    return 0;
}
