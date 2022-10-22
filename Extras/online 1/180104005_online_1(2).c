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
        printf("%s", ch[i]);
        process(ch[i]);
    }
    printf("\n\nNo. Of Float %d", float_counter);

    return 0;
}


void take_input_from_console()
{

    FILE *p1;

    char c,prev='z';
    p1 = fopen("input.txt", "r");

    int newLine=0;
    int x=0, j=0;
    if(!p1)printf("\nFile can't be opened!");
    else
    {

        while((c=fgetc(p1))!=EOF)
        {
            ch[x][j] = c;
            if(c=='\n'){
                ch[x][j+1] = '\0';
                j=0;
                x++;
                continue;
            }
            j++;
        }
    }
    lines = x;

    fclose(p1);
}
