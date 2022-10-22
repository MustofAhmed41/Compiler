#include<stdio.h>
#include<string.h>

int isSep(char c)
{
    if(c==';' || c==',' || c=='\'')
        return 1;
    return 0;
}
int isOp(char c)
{
    if(c=='+' || c=='-' || c=='*' || c=='/' || c=='>' || c=='<' || c=='!' || c=='=')
        return 1;
    return 0;
}
int isDigit(char c)
{
    if(c>='0' && c<='9')
        return 1;
    return 0;
}
int isPar(char c)
{
    if(c==')' || c=='(' || c=='}' || c=='{' )
        return 1;
    return 0;
}


int isSepa(char* c)
{
    if(strlen(c)==1 && isSep(c[0]))
        return 1;
    return 0;
}

int isKey(char* c)
{
    if(strlen(c)==3 && c[0]=='i' && c[1]=='n' && c[2]=='t')
        return 1;
    if(strlen(c)==5 && c[0]=='f' && c[1]=='l' && c[2]=='o' && c[3]=='a' && c[4]=='t' )
        return 1;
    if(strlen(c)==4 && c[0]=='c' && c[1]=='h' && c[2]=='a' && c[3]=='r')
        return 1;
    if(strlen(c)==4 && c[0]=='e' && c[1]=='l' && c[2]=='s' && c[3]=='e')
        return 1;
    if(strlen(c)==2 && c[0]=='i' && c[1]=='f')
        return 1;
    return 0;
}

int isOper(char* c)
{
    if(strlen(c)>2)
        return 0;
    if(strlen(c)==1)
    {
        if(isOp(c[0]))
            return 1;
        return 0;
    }
    if(isOp(c[0]) && c[1]=='=')
        return 1;
    return 0;
}

int isParen(char* c)
{
    if(strlen(c)==1 && isPar(c[0]))
        return 1;
    return 0;
}

int isNum(char *lex)
{
    int i, l, s;
    i=0;
    if(isDigit(lex[i]))
    {
        s=1;
        i++;
    }
    else if(lex[i]=='.')
    {
        s=2;
        i++;
    }
    else s=0;
    l=strlen(lex);
    if(s==1)
        for(; i<l; i++)
        {
            if(isDigit(lex[i]))  s=1;
            else if(lex[i]=='.')
            {
                s=2;
                i++;
                break;
            }
            else
            {
                s=0;
                break;
            }
        }
    if(s==2)
        if(isDigit(lex[i]))
        {
            s=3;
            i++;
        }
        else
            s=0;
    if(s==3)
        for(; i<l; i++)
        {
            if(isDigit(lex[i]))  s=3;
            else
            {
                s=0;
                break;
            }
        }
    if(s==3) s=1;
    return s;
}

int isId(char* c)
{
    int i=0;
    int x = 0;
    for(i=0; i<strlen(c); i++)
    {
        if((c[i]>='a' && c[i]<='z') || (c[i]>='A' && c[i]<='Z') || c[i]=='_')
        {

            x = 1;
            // printf("x = %d\n",x);
            continue;
        }
        else if(isDigit(c[i])==1)
        {
            if(x==0)
                return 0;
        }
        else return 0;
    }
    return 1;
}
int main()
{
    char a[1000];
    char b[1000];
    FILE* fp = fopen("input.txt","r");

    if (fp==NULL)
    {
        printf("no such file.");
        return 0;
    }
    int i = 0;
    while(fscanf(fp,"%c",&a[i])!=EOF)
    {
        i++;
    }
    puts(a);
    //gets(a);
    a[i] = '\0';
    int flag  =0;
    int n = strlen(a),j=0;
    int sepOn = 0;
    for(i=0; i<n; i++)
    {
        if(isSep(a[i])==1)
        {
            if(a[i]=='\'')
            {
                if(sepOn)
                {
                    sepOn = 0;
                    b[j++]  = ' ';
                    b[j++]  = a[i];
                }
                else
                {
                    b[j++]  = a[i];
                    b[j++]  = ' ';
                    sepOn = 1;
                }
            }
            else
            {
                b[j++]  = ' ';
                b[j++]  = a[i];
            }


        }
        else if(isOp(a[i])==1)
        {
            if(a[i+1]=='=')
            {
                b[j++]  = ' ';
                b[j++]  = a[i];
                b[j++]  = a[i+1];
                i++;
                b[j++]  = ' ';
            }
            else
            {
                b[j++]  = ' ';
                b[j++]  = a[i];
                b[j++]  = ' ';
            }
            flag  =1;
        }
        else if(isDigit(a[i])==1)
        {
            if(flag==0)
            {
                flag = 1;
                b[j++]  = ' ';
            }
            b[j++]  = a[i];
        }
        else if(isPar(a[i])==1)
        {
            b[j++]  = ' ';
            b[j++]  = a[i];
            if(a[i]!=')' && a[i]!='}')
                b[j++]  = ' ';
        }

        else
        {
            flag  =1;
            b[j++]  = a[i];
        }
    }
    b[j] = '\0';
    printf("\n\n");
    puts(b);
    printf("\n\n");




    a[0] = '\0';
    j = 0;
    for(i=0; i<strlen(b); i++)
    {
        if(b[i]==' ')
        {
            a[j++] = '\0';
            if(strlen(a)==0)
            {
                j  =0;
                continue;
            }
            if(isSepa(a)==1)
            {
                printf("[sep %s] ",a);
            }
            else if(isKey(a)==1)
            {
                printf("[kw %s] ",a);
            }
            else if(isId(a)==1)
            {
                printf("[id %s] ",a);
            }
            else if(isOper(a)==1)
            {
                printf("[op %s] ",a);
            }
            else if(isParen(a)==1)
            {
                printf("[par %s] ",a);
            }
            else if(isNum(a)==1)
            {
                printf("[num %s] ",a);
            }
            else
            {
                printf("[unkn %s] ",a);
            }
            j= 0;
        }
        else
        {
            a[j++]  = b[i];
        }

    }
    a[j++] = '\0';
    if(strlen(a)>0)
    {
        //printf("%s\n",a);
        if(isSepa(a)==1)
        {
            printf("[sep %s] ",a);
        }
        else if(isKey(a)==1)
        {
            printf("[kw %s] ",a);
        }
        else if(isId(a)==1)
        {
            printf("[id %s] ",a);
        }
        else if(isOper(a)==1)
        {
            printf("[op %s] ",a);
        }
        else if(isParen(a)==1)
        {
            printf("[par %s] ",a);
        }
        else if(isNum(a)==1)
        {
            printf("[num %s] ",a);
        }
        else
        {
            printf("[unkn %s] ",a);
        }
    }

}


// char c; int x1, x_2; float y1, y2; x1=5; x_2=10; y1=2.5+x1*45; y2=100.o5-x_2/3; if(y1<=y2) c='y'; else c='n';
