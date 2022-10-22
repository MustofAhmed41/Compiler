#include <stdio.h>
#include <string.h>
#include <ctype.h>


char ch[100][100];
int totalCount = 0;
int n;

void take_input_from_console()
{

    int i = 0;
    n = 0;
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
        n++;
    }
    i = 0 ;
    int x = 0;
    int counter;
    char str[100];
    while(1)
    {
        x=0;
        while(x<strlen(ch[i]))
        {
            printf("%c", ch[i][x]);
            x++;
        }
        printf("\n");
        if(i>n)
        {
            break;
        }
        i++;
    }
}

void detect_par()
{
    int x = 0, i = 0;
    while(1)
    {
        x=0;
        while(x<strlen(ch[i]))
        {
            if(ch[i][x]=='/' && ch[i][x+1]=='/')
            {
                i++;
                break;
            }
            else
            {
                if(ch[i][x]=='{')
                {

                    int found  = 0;
                    int match_found = 0;
                    for(int a = i ; a< n ; a++)
                    {
                        for(int b = x + 1; b<strlen(ch[i]); b++)
                        {
                            if(ch[a][b]=='}')
                            {
                                if(found == 0)
                                {
                                    match_found = 1;
                                    break;
                                }
                                else
                                {
                                    found--;
                                }
                            }
                            else if(ch[a][b]=='{')
                            {
                                found++;
                            }
                        }
                        if(match_found==1)
                            break;
                    }

                    if(match_found==0){
                        printf("Misplaced Curly Braces at Line Number %d\n", i+1);
                    }
                }

            }
             x++;
        }

        if(i>n)
        {
            break;
        }
        i++;
    }
}


void detect_par2()
{
    int x = 0, i = 0;
    while(1)
    {
        x=0;
        while(x<strlen(ch[i]))
        {
            if(ch[i][x]=='/' && ch[i][x+1]=='/')
            {
                i++;
                break;
            }
            else
            {
                if(ch[i][x]=='(')
                {
                    int found  = 0;
                    int match_found = 0;
                    for(int a = i ; a< n ; a++)
                    {
                        for(int b = x + 1; b<strlen(ch[i]); b++)
                        {
                            if(ch[a][b]==')')
                            {
                                if(found == 0)
                                {
                                    //matched
                                    match_found = 1;
                                    break;
                                }
                                else
                                {
                                    found--;
                                }
                            }
                            else if(ch[a][b]=='(')
                            {
                                found++;
                            }
                        }
                        if(match_found==1)
                            break;
                    }

                    if(match_found==0){
                        printf("Misplaced Paranthesis at Line Number %d\n", i+1);
                    }
                }
                x++;
            }
        }

        if(i>n)
        {
            break;
        }
        i++;
    }
}



void detect_par3()
{
    int x = 0, i = n-1;
    while(1)
    {
        x = strlen(ch[i])-1;
        while(x<strlen(ch[i]))
        {
            if(ch[i][x]=='/' && ch[i][x-1]=='/')
            {
                i--;
                break;
            }
            else
            {
                if(ch[i][x]=='}')
                {
                    int found  = 0;
                    int match_found = 0;
                    for(int a = i ; a < n ; a--)
                    {
                        for(int b = x -1 ; b<strlen(ch[i]); b--)
                        {
                            if(ch[a][b]=='{')
                            {
                                if(found == 0)
                                {
                                    //matched
                                    match_found = 1;
                                    break;
                                }
                                else
                                {
                                    found--;
                                }
                            }
                            else if(ch[a][b]=='}')
                            {
                                found++;
                            }
                        }
                        if(match_found==1)
                            break;
                    }

                    if(match_found==0){
                        printf("Misplaced Paranthesis at Line Number %d\n", i+1);
                    }
                }
                x--;
            }
        }

        if(i>n)
        {
            break;
        }
        i--;
    }
}







int main()
{
    take_input_from_console();
    detect_par();
    detect_par2();
    detect_par3();
    return 0;
}
