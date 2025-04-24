#include <stdio.h>
void main(){
int a[50];
int i,j,n,count=0,pos;
printf("\n Enter the number of bits: ");
scanf("%d",&n);
printf("\n Enter the bits (0s and 1s):\n ");
for(i=0; i<n;i++){
    scanf("%d",&a[i]);
}
for(i=0;i<n;i++){
    if(a[i]==1){
    count++;
    if(count==5){
    pos=i+1;
    for(j=n;j>pos;j--){
    a[j]=a[j-1];
    }
    a[pos]=0;
    n++;
    count=0;
    i++;
    }
    }
    else{
    count=0;
    }
}
printf("\n Data after stuffing:\n0111110");
for(i=0;i<n;i++){
    printf("%d" ,a[i]);
}
printf("0111110\n");
}
