#include <stdio.h>
#include <string.h>
int main() {
   char a[100] ,b[100];
   int i=0,j=0;
   printf("Enter the string:");
   scanf("%s",&a);
   for(i=0;a[i]!='\0';i++)
   {
       if(a[i]=='D' && a[i+1]=='L'&& a[i+2]=='E'){
           b[j++]='D';
            b[j++]='L';
              b[j++]='E';
                b[j++]='D';
                i+=2;
       }
       else{
             b[j++]=a[i];

       }
   }
   b[j]='\0';
   printf("DLESTX%s DLEETX\n",b);
   return 0;
}
