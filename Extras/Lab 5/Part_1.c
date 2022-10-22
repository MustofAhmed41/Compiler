#include <stdio.h>
#include <ctype.h>
#include <string.h>


void Term();
void Exp();
void Factor();


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





void X()
{
    if(i+2<l){
        if((str[i]=='b' && str[i+1]=='b') || (str[i]=='b' && str[i+1]=='c')){
            i += 2;
            f = 1;
            X();
        }else{
            f = 0;
        }
    }else{
        f = 1;
        return;
    }
}

void A()
{
    if(l==2 && str[i] == 'a' && str[i+1] == 'd')
    {
        f = 1;
        return;
    }else if(l%2 == 1){
        f = 0;
        return;
    }
    else
    {
        if(str[i]=='a' && str[l-1]=='d'){
            i+=1;
            X();
        }else{
            f = 0;
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

    //Exp();
    A();

    if( f==1){
        printf("Matched");
    }else{
        printf("Not Matched");
    }


    return 0;
}

