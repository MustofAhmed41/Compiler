#include <stdio.h>
#include <string.h>
#include <ctype.h>

char ch[100][100];
char inp[5000];

void take_input_from_console();
int lines;

int main()
{
    take_input_from_console();
    return 0;
}


void take_input_from_console()
{

    char c1;
    int i = 0;
    FILE *fp;

    fp = fopen("inputtt2.txt", "w");
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
        for(int j = 0 ; j < strlen(ch[i]); j++)
        {
            if(ch[i][j]!='\0')
            {
                fputc(ch[i][j],fp);
            }
        }
        i++;
        fputc('\n',fp);
        lines++;
    }

    fclose(fp);
}
