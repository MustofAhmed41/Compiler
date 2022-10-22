#include <stdio.h>
#include <string.h>
#include <ctype.h>

char ch[100][100];
char inp[5000];

int lines;

void take_input_from_console();

void process(char *code_line, int line_number)
{
    int n = strlen(code_line);
    int found = 0, store = line_number;

    for(int i = 0 ; i < n; i++)
    {
        if(code_line[i]=='e' && code_line[i+1]=='l' && code_line[i+2]=='s' && code_line[i+3]=='e')
        {
            found = 1;
            break;
        }
    }
    int matcher = 0;
    if(found==1){
        line_number-1;
        while(line_number>=0){

            for(int i = 0 ; i < strlen(ch[i]) - 2; i++)
            {
                if(ch[line_number][i]=='i' && ch[line_number][i+1]=='f')
                {
                    if(matcher==0)
                        break;
                    matcher--;
                }
                else if(ch[line_number][i]=='e' && ch[line_number][i+1]=='l' && ch[line_number][i+2]=='s' && ch[line_number][i+3]=='e')
                {
                    matcher++;
                }
            }
            line_number--;
        }

        if(matcher!=0){
            printf("Mismatch else at line number %d\n", store + 1);
        }
        printf("\n");

    }
}

int main()
{
    take_input_from_console();
    for(int i = 0 ; i < lines; i++)
    {
        //printf("%s\n", ch[i]);
        process(ch[i], i);
    }

    return 0;
}


void take_input_from_console()
{

    char c1;
    int i = 0;
    FILE *fp;

    fp = fopen("input2.txt", "w");
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
