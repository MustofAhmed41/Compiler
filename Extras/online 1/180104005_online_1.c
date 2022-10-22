#include <stdio.h>
#include <string.h>
#include <ctype.h>

char ch[100][100];
char inp[5000];
int float_counter = 0;

void take_input_from_console();
int lines;
void process(char *code_line)
{
    int n = strlen(code_line);
    int found = 0;
    int foundCommentNumber = 500;
    int printfFound = 0;


    for(int i = 0 ; i < n-1; i++){
        if(code_line[i]=='/' && code_line[i+1]=='/'){
            found = 1;
            foundCommentNumber = i;
        }
    }

    int start;
    for(int i = 0 ; i < n-5; i++)
    {
        if(code_line[i]=='p' && code_line[i+1]=='r' && code_line[i+2]=='i'
                && code_line[i+3]=='n' && code_line[i+4]=='t' && code_line[i+5]=='f' )
        {
            printfFound = 1;
            start = i;
            break;
        }
    }
    if(printfFound==1 && start<foundCommentNumber)
    {
        for(int i = start; i<n; i++)
        {
            if(code_line[i]=='%' && code_line[i+1]=='f')
            {
                float_counter++;
            }
            if(code_line[i]==';')
            {
                break;
            }
        }
    }

}

int main()
{
    take_input_from_console();
    for(int i = 0 ; i < lines; i++)
    {
        //printf("%s\n", ch[i]);
        process(ch[i]);
    }
    printf("\n\nNo. Of Float %d", float_counter);

    return 0;
}


void take_input_from_console()
{

    char c1;
    int i = 0;
    FILE *fp;

    fp = fopen("main_input_for_assignment_1.txt", "w");
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
