#include <stdio.h>
#include <ctype.h>
#include <string.h>


void Term();
void Exp();
void Factor();
void stat();

int i;
char str[1000];
int f;
int l;

void ID()
{
    if(i<l && str[i]>='a' && str[i]<='e')
    {
        i++;
        f = 1;
        return;
    }
    f = 0;
    return;
}

void NUM()
{
    if(i<l && str[i]>='0' && str[i]<='9')
    {
        i++;
        f = 1;
        return;
    }
    f = 0;
    return;
}

void Factor(){

    if(i<l)
        ID();
        if(f==1)
            return;
    if(i<l)
        NUM();
        if(f==1)
            return;

    if(i<l && str[i]=='('){
        i++;
        Exp();
        if(str[i]==')' && f == 1){
           i++;
           f = 1;
           return;
        }else{
            f = 0;
            return;
        }

    }
    f = 0;
    return;
}


void Term(){
    if(i<l)
        Factor();

    if(i==l || f==0)
    {
        return;
    }

    if(str[i]=='*' || str[i]=='/')
    {
        i++;
        Factor();
    }
}

void Exp(){


    if(i<l)
        Term();

    if(i==l || f==0)
    {
        return;
    }

    if(str[i]=='+' || str[i]=='-')
    {
        i++;
        Term();
    }

    if((str[i]=='+' || str[i]=='-') && i<l && f==1){
        i++;
        Exp();
    }
}



void relop()
{
    if(i+1<l && str[i]=='=' && str[i+1]=='=')
    {
        f = 1;
        i+=2;
        return;
    }

    if(i+1<l && str[i]=='!' && str[i+1]=='=')
    {
        f = 1;
        i+=2;
        return;
    }
    if(i+1<l && str[i]=='<' && str[i+1]=='=')
    {
        f = 1;
        i+=2;
        return;
    }
    if(i+1<l && str[i]=='>' && str[i+1]=='=')
    {
        f = 1;
        i+=2;
        return;
    }
    if(i<l && str[i]=='>')
    {
        f = 1;
        i++;
        return;
    }
    if(i<l && str[i]=='<')
    {
        f = 1;
        i++;
        return;
    }
    f = 0;
    return;
}



void extn()
{
    int temp = i;
    relop();
    if(f==1)
    {
        Exp();
        if(f==1)
        {
            return;
        }else{
            f = 0;
            return;
        }
    }
    i = temp;
    f = 1;
    return;
}



void expn()
{
    Exp();
    if(f==1)
    {
        extn();
        return;
    }
    return;
}


void asgn_stat()
{
    ID();
    if(f==1)
    {
        if(i<l && str[i]=='=')
        {
            i++;
            expn();
            return;
        }
        f = 0;
        return;
    }
    return;
}

void extn1()
{
    int temp = i;
    if(i+3<strlen(str) && str[i]=='e' && str[i+1]=='l' && str[i+2]=='s' && str[i+3]=='e')
    {
        i+=4;
        stat();
        if(f==1)
        {
            return;
        }
    }
    i = temp;
    f = 1;
    return;
}


void dscn_stat()
{
    if(i+2<l && str[i]=='i' && str[i+1]=='f' && str[i+2]=='(')
    {
        i+=3;
        expn();
        if(f==1)
        {
            if(i<l && str[i]==')')
            {
                i++;
                stat();
                if(f==1)
                {
                    extn1();
                    return;
                }
                else
                {
                    return;
                }
            }
            else
            {
                f = 0;
                return;
            }
        }
        else
        {
            return;
        }
    }
    f = 0;
    return;
}


void loop_stat()
{
    int temp = i;
    if(i+5<l && str[i]=='w' && str[i+1]=='h' && str[i+2]=='i' && str[i+3]=='l' && str[i+4]=='e' && str[i+5]=='(')
    {
        i+= 6;
        expn();
        if(f==1 && i<l && str[i]==')')
        {
            i++;
            stat();
            if(f==1)
            {
                return;
            }
        }

    }
    i = temp;
    if(i+3<l && str[i]=='f' && str[i+1]=='o' && str[i+2]=='r' && str[i+3]=='(')
    {
        i+=4;
        asgn_stat();
        if(f==1)
        {
            if(i<l && str[i]==';')
            {
                i++;
                expn();
                if(f==1)
                {
                    if(i<l && str[i]==';')
                    {
                        i++;
                        asgn_stat();
                        if(i<l && str[i]==')')
                        {
                            i++;
                            stat();
                            if(f==1)
                                return;
                        }
                    }
                }
            }
        }

    }
    f = 0;
    return;
}



void stat()
{
    int temp = i;
    asgn_stat();
    if(f==1)
        return;

    i = temp;
    dscn_stat();
    if(f==1)
        return;

    i = temp;
    loop_stat();
    if(f==1)
        return;

    f = 0;
    return;
}




int main()
{
    gets(str);
    //puts(str);

    i = 0;
    f = 0;
    l = strlen(str);
    stat();
    //printf("%d %d", i , l);
    if(f==1){
        printf("Matched");
    }else{
        printf("Not Matched");
    }



    return 0;
}


