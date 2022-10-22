#include<stdio.h>
#include<string.h>
char a[10000];
int main()
{
    FILE *fp = fopen("input.txt","r");
    FILE *fp2 = fopen("output.txt","w");
    int m=0,i;
    while(fgets(a,1000,fp))
    {
        int s = 0;
        printf("%d %s",strlen(a),a);
        for(i=0;i<strlen(a);i++)
        {
            if(s==1)
                continue;
            else if(i+1<strlen(a) && a[i]=='/' && a[i+1]=='*')
            {
                m  =1;
            }
            else if(i+1<strlen(a) && a[i]=='*' && a[i+1]=='/')
            {
                m  =0;
                i++;
            }
            else if(m==1)
            {
                continue;
            }
            else if(a[i]==' ' || a[i]=='\t')
            {
                fputc(' ',fp2);
                int j = i;
                while(j<strlen(a) && (a[j]==' ' || a[j]=='\t'))
                {
                    j++;
                }
                i =j-1;
            }
            else if(i+1<strlen(a) && a[i]=='/' && a[i+1]=='/')
            {
                s = 1;
                i++;
            }
            else if(a[i]!='\n')
            {
                fputc(a[i],fp2);
            }
        }
    }
}

