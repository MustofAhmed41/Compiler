#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main ()
{
    char inp[100];
    printf("Input String : ");
    gets(inp);
    int val = detect_pattern(inp);
    if(val == 5)
    {
        printf("String follows the pattern.");
    }
    else
    {
        printf("String does not follow the pattern.");
    }
    return 0;
}

int detect_pattern(char *word)
{
    int i, l, s, ret;
    l = strlen(word);
    i = 0;
    s = 0;
    if(isdigit(word[i]))
    {
        s = 1;
    }
    else if(isalpha(word[i]))
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
            if(isalpha(word[i]))
            {
                s = 2;
                i++;
                break;
            }
            else if(isdigit(word[i]))
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
        }
    }

    if(s == 3)
    {
        if(isalpha(word[i]))
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

