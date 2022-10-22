#include <stdio.h>
#include <string.h>
#include <ctype.h>



void read_file()
{
    FILE *p1;

    char c,prev='z';
    p1 = fopen("symbol.txt", "r");

    int newLine=0;
    if(!p1)printf("\nFile can't be opened!  ");

    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            printf("%c", c);
        }
    }

    fclose(p1);

    printf("\n\n");
}


int main(){
    read_file();
    return 0;
}

