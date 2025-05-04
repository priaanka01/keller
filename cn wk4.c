#include <stdio.h>
int main() {
    int tF, wS, cF = 0, aF;
    printf("Enter the total number of frames: ");
    scanf("%d", &tF);
    printf("Enter the window size: ");
    scanf("%d", &wS);
    while (cF < tF) {
        printf("\nSending frames:\n");
        for (int i = 0; i < wS && cF + i < tF; i++) {
            printf("Sent Frame: %d\n", cF + i);
        }
        printf("\nEnter the number of frames acknowledged: ");
        scanf("%d", &aF);
        if (aF == 0) {
            printf("No acknowledgment received. Resending frames...\n");
        } else {
            cF += aF;
            printf("%d frames acknowledged.\n", aF);
        }
    }
    printf("\nAll frames sent successfully!\n");
    return 0;
}
