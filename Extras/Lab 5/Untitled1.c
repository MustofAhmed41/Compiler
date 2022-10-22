#include <stdio.h>
#include <ctype.h>
#include <string.h>

int i;
char str[1000];
int f;
int l;

void B()
{
    if (str[i] == 'b')
    {
        i++;
        f=1;
        return;
    }
    else
    {
        f=0;
        return;
    }
}

void A()
{
    if (str[i] == 'a')
    {
        i++;
        f=1;
    }
    else
    {
        f=0;
        return;
    }
    if (i<l-1) A();
}

void S()
{
    if ( l==1 && str[i] == 'b')
    {
        i++;
        f=1;
        return;
    }
    else
    {
        A();
        if (f)
        {
            B();
            return;
        }
    }
}


int main()
{
    gets(str);
    puts(str);
    i = 0;
    l = strlen(str);
    S();
    if(f==1){
        printf("Matched");
    }else{
        printf("Not Matched");
    }

    return 0;
}
