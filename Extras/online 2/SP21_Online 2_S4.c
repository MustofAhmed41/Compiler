#include <stdio.h>
#include <ctype.h>
#include <string.h>

//isdigit(isdigit(word[i])) || isalpha(word[i]) || word[i]=='_'

int main ()
{
    char inp[100];
    gets(inp);
    int val = detect_pattern(inp);
    if(val == 4 || val == 5)
    {
        printf("Correct");
    }
    else
    {
        printf("Wrong");
    }
    return 0;
}

int detect_pattern(char *word)
{
    int i, l, s, ret;
    l = strlen(word);
    i = 0;
    s = 0;
    if(isalpha(word[i]))
    {
        s = 1;
    }
    else if(word[i]=='a')
    {
        s = 2;
    }
    else
    {
        s = -1;
    }
    i++;

    if(s==1)
    {
        for(; i<l; i++)
        {
            if(word[i]=='a')
            {
                s = 2;
                i++;
                break;
            }
            else if(isalpha(word[i]))
            {
                s = 1;
            }
            else
            {
                s = -1;
                i++;
                break;
            }

        }
    }

    if(s == 2)
    {
        if(word[i]=='_')
        {
            s = 3;
            i++;
        }
        else
        {
            s = -1;
            i++;
        }
    }

    if(s == 3)
    {
        if(isdigit(word[i]))
        {
            s = 4;
            i++;
        }
        else
        {
            s = -1;
        }
    }

    if(s == 4)
    {
        if(isdigit(word[i]))
        {
            s = 5;
            i++;
        }
        else
        {
            s = -1;
            i++;
        }
    }

    if (s == 5 && i<l){
        for(; i<l; i++)
        {
            if(isdigit(word[i]))
            {
                s = 5;
            }else{
                s = -1;
            }
        }
    }



    return s;
}

