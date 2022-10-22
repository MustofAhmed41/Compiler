#include <stdio.h>

int main()
{
    FILE *p1, *p2;
    char c;
    p1 = fopen("Efficient.c", "r");
    p2 = fopen("EfficientWrite.txt", "w");
    int lineNumber = 0;
    if(!p1)printf("\nFile can't be opened!");
    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            fputc(c,p2);
        }
    }

    fclose(p1);
    fclose(p2);

    p2=fopen("EfficientWrite.txt", "r");
    while((c=fgetc(p2)) != EOF)
        printf("%c", c);
    fclose(p2);


    return 0;
}
