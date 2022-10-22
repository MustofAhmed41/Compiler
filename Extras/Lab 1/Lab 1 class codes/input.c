#include <stdio.h>
//add line numbers to all the lines of codes
int main(void)
{

    FILE *p1, *p2;
    char c, con;
    p1 = fopen("input.c", "r");
    p2 = fopen("lineNumber.txt", "w");

    int lineCounter = 2;
    int l = 0;
    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
        fputc('1',p2);
        fputc(':',p2);
        while((c=fgetc(p1))!=EOF)
        {
            if(c=='\n')
            {
                fputc('\n',p2);
                con = (char) lineCounter-208;
                char con2 = (char) l-208;
                if(l!=0)
                {
                    fputc(con2,p2);
                }
                lineCounter++;
                fputc(con,p2);
                fputc(':',p2);
                if(lineCounter>9)
                {
                    lineCounter = 0;
                    l++;
                }
            }
            else
            {
                fputc(c,p2);
            }
        }
    }

    fclose(p1);
    fclose(p2);

    p2=fopen("lineNumber.txt", "r");
    while((c=fgetc(p2)) != EOF)
        printf("%c", c);
    fclose(p2);

}
