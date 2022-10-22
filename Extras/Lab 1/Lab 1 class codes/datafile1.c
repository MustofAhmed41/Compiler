#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <math.h>
//reads headers
int main(void)
{

    FILE *p1, *p2;
    char c;
    p1 = fopen("datafile1.c", "r");
    p2 = fopen("header.txt", "w");
    int counter=10;
    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
        int a = 0;
        while((c=fgetc(p1))!=EOF)
        {
            if(c=='#'){
             counter = 12;
            }
            counter--;
            if(c=='<' && counter >0)
            {
                c=fgetc(p1);
                a = 1;
            }
            if(c=='>' && counter >-10)
            {
                a=3;
            }
            if(a==1)
            {
                fputc(c,p2);
            }
            if(a==3)
            {
                fputc('\n',p2);
                a=0;
            }


        }
    }

    fclose(p1);
    fclose(p2);

    p2=fopen("header.txt", "r");
    while((c=fgetc(p2)) != EOF)
        printf("%c", c);
    fclose(p2);

}

