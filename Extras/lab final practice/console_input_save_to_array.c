#include <stdio.h>
#include <string.h>
#include <ctype.h>

char ch[100][100];
char inp[5000];
int lines;


void take_input_from_console()
{

    char c1;
    int i = 0;
    int eof_tracker = 0;
    while(1)
    {
        gets(ch[i]);
        if(ch[i][0]=='\0')
        {
            eof_tracker++;
            if(eof_tracker==3)
            {
                break;
            }
        }
        else
        {
            eof_tracker = 0;
        }
        i++;
        lines++;
    }
    printf("\n\n");
    i = 0;
    while(i<lines)
    {
        puts(ch[i]);
        i++;
    }
}


int main()
{
    take_input_from_console();
    return 0;
}
