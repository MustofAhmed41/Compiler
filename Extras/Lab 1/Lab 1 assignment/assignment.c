#include <stdio.h>// hello world
// hello world
int main()
{
    FILE *p1, *p2;
    char c;
    p1 = fopen("assignment.c", "r");
    p2 = fopen("assignment.txt", "w"); // hello world
    int newLine=0;
    if(!p1)printf("\nFile can't be opened!");
    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            if(c=='\n'){
                newLine = 1;
            }
            if(newLine==1){
                while((c=fgetc(p1))==' '){}
                newLine = 0;
            }
            if(c=='/'){
                if((c=fgetc(p1))=='/'){
                    while((c=fgetc(p1))!='\n'){}
                }else{
                    fputc('/',p2);
                }
            }
            if(c!='\n')fputc(c,p2);
        }
    }

    fclose(p1);
    fclose(p2);

    p2=fopen("assignment.txt", "r");
    while((c=fgetc(p2)) != EOF)
        printf("%c",c);
    fclose(p2);

    return 0;
}

