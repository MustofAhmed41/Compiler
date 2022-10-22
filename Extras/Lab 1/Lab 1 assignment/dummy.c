#include <stdio.h>

//xx
int main()
{
    FILE *p1, *p2, *p3;
    char c;
    p1 = fopen("dummy.c", "r");
    p2 = fopen("dummy.txt", "w");
    int len;

    while((c=fgetc(p1))!=EOF)
    {
        if(c=='x')
        {
            if((c=fgetc(p1))=='x'){
                ungetc('y',p1);
            }
        }
        fputc(c,p2);
    }

    fclose(p1);
    fclose(p2);

    p2=fopen("dummy.txt", "r");
    while((c=fgetc(p2)) != EOF)
        printf("%c",c);
    fclose(p2);
}
