#include <stdio.h>
#include <stdlib.h>
#define ll long long

int main ()
{
    int n;
    scanf("%d",&n);
    ll **matrix = (ll **)malloc((n+1) * sizeof(ll *));
    int i,j;
    for(i = 0; i < n; i++)
    matrix[i] = (ll *)malloc((n+1) * sizeof(ll));
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            matrix[i][j]=(i+1)*(j+1);
        }
    }
    int x1,x2,y1,y2;
    while(1){
        scanf("%d",&x1);
        if(x1==0){
            break;
        }
        scanf("%d%d%d",&y1,&x2,&y2);
        int format = 0, cp = matrix[x2-1][y2-1];
        while(cp>0){
            format++;
            cp/=10;
        }
        for(i=x1;i<=x2;i++){
            for(j=y1;j<=y2;j++){
                printf("%*lld ",format,matrix[i-1][j-1]);
            }
            printf("\n");
        }
    }
    free(matrix);
    return(0);
}
