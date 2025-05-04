#include <stdio.h>
int main() {
    int i, j, temp, framearr[20], pages, pageno, frames;
    int memsize, log, pagesize, prosize, base;
    printf("Enter the Process size: ");
    scanf("%d", &prosize);
    printf("\nEnter the main memory size: ");
    scanf("%d", &memsize);
    printf("\nEnter the page size: ");
    scanf("%d", &pagesize);
    pages = (prosize + pagesize - 1) / pagesize;
    frames = memsize / pagesize;
    printf("\nThe process is divided into %d pages", pages);
    printf("\n\nThe main memory is divided into %d frames\n", frames);
    for (i = 0; i < frames; i++)
        framearr[i] = -1;
    for (i = 0; i < pages; i++) {
        while (1) {
            printf("\nEnter the frame number of page %d: ", i);
            scanf("%d", &temp);
            if (temp >= frames) {
                printf("\n\t**** Invalid frame number ****\n");
            } else {
                framearr[temp] = i;
                break;
            }
        }
    }
    printf("\n\nFrame No\tPage No\tValidation Bit");
    printf("\n--------\t------\t--------------");
    for (i = 0; i < frames; i++) {
        printf("\n %d \t\t %2d \t", i, framearr[i]);
        printf(framearr[i] == -1 ? "0" : "1");
    }
    printf("\nEnter the logical address: ");
    scanf("%d", &log);
    printf("\nEnter the base address: ");
    scanf("%d", &base);
    pageno = log / pagesize;
    j = log % pagesize;
    int frame_no = -1;
    for (i = 0; i < frames; i++) {
        if (framearr[i] == pageno) {
            frame_no = i;
            break;
        }
    }
    if (frame_no == -1) {
        printf("\nInvalid logical address! Page not found.");
    } else {
        int physical_address = base + (frame_no * pagesize) + j;
        printf("\nPhysical address is: %d", physical_address);
    }
    return 0;
}
