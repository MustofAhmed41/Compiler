/*

    Author: Alam Khan
    AUST CSE 40th Batch
*/


#include<stdio.h>
#include<string.h>
char str[10000][10000];
char ar[10000],br[10000];
char a[10000],b[10000],temp[10000],c[70][70][500];
int inde[10000];
int cur = 0;
int sz[1000];
struct data
{
    char * name;
    char * idType;
    char* dataType;
    char* scope;
    char* value;

} v[100];
void insert(int ind,char* _name, char* _id,char* _dat,char* _scope,char* _value)
{
    v[ind].name  =_name;
    v[ind].idType= _id;
    v[ind].dataType = _dat;
    v[ind].scope  =_scope;
    v[ind].value  =_value;
}

void display()
{
    int i=0;
    printf("\nSl. No.\t\tName\t\tId Type\t\tData Type\tScope\t\tValue\n");
    for(i=0; i<cur; i++)
    {
        printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n",i+1,v[i].name,v[i].idType,v[i].dataType,v[i].scope,v[i].value);
    }
}



int search(char* _name,char* _id,char* _scope)
{
    int i=0;

    for(i=0; i<cur; i++)
    {
        if(strcmp(v[i].name,_name)==0 && strcmp(v[i].idType,_id)==0 && strcmp(v[i].scope,_scope)==0 )
        {
            return i;
        }
    }
    return -1;
}

char* modify(char * x)
{
    if(strlen(x)==0)
        return x;
    if(x[0]>='0' && x[0]<='9')
        return x;
    return "";
}

void update(int cur,char* val)
{
    v[cur].value  = val;
}
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
    if(c==')' || c=='(')
        return 1;
    return 0;
}

int isBrc(char c)
{
    if(c=='}' || c=='{')
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
    else if(strlen(c)==3 && c[0]=='f' && c[1]=='o' && c[2]=='r')
        return 1;
    else if(strlen(c)==5 && c[0]=='f' && c[1]=='l' && c[2]=='o' && c[3]=='a' && c[4]=='t' )
        return 1;
    else if(strlen(c)==5 && c[0]=='w' && c[1]=='h' && c[2]=='i' && c[3]=='l' && c[4]=='e' )
        return 1;
    else if(strlen(c)==6 && c[0]=='d' && c[1]=='o' && c[2]=='u' && c[3]=='b' && c[4]=='l' && c[5]=='e')
        return 1;
    else if(strlen(c)==4 && c[0]=='c' && c[1]=='h' && c[2]=='a' && c[3]=='r')
        return 1;
    else if(strlen(c)==4 && c[0]=='e' && c[1]=='l' && c[2]=='s' && c[3]=='e')
        return 1;
    else if(strlen(c)==4 && c[0]=='v' && c[1]=='o' && c[2]=='i' && c[3]=='d')
        return 1;
    else if(strlen(c)==2 && c[0]=='i' && c[1]=='f')
        return 1;
    else if(strlen(c)==6 && c[0]=='r' && c[1]=='e' && c[2]=='t' && c[3]=='u' && c[4]=='r' && c[5]=='n')
        return 1;
    else if(strlen(c)==2 && c[0]=='d' && c[1]=='0')
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
int isBrace(char* c)
{
    if(strlen(c)==1 && isBrc(c[0]))
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
    int i,n,t,k,j,x=0,y=0,m;
    FILE *fp = fopen("input.txt","r");
    FILE *fp2 = fopen("intermediate ouput.txt","w");
    FILE *fp3 = fopen("error.txt","w");
    i = 1;

    // take input and comment remove 1st assignment
    int c1 = 0, c2  = 0;
    while(fgets(str[i],500,fp))
    {
        int sz = strlen(str[i]);
        c1 = 0;
        for(j=0; j<sz; j++)
        {

            if(j+1<sz && str[i][j]=='/' && str[i][j+1]=='/')
            {
                c1 = 1;
                str[i][j]  = str[i][j+1]  = ' ';
                j++;
            }
            else if(j+1<sz && str[i][j]=='/' && str[i][j+1]=='*')
            {
                c2 = 1;
                str[i][j] = str[i][j+1]  =' ';
                j++;
            }
            else if(j+1<sz && str[i][j]=='*' && str[i][j+1]=='/')
            {
                c2 = 0;
                str[i][j]  = str[i][j+1] = ' ';
                j++;
            }
            else if(c1 || c2)
            {
                str[i][j]  = ' ';
            }

        }
        i++;
    }
    int totalsz = i;



    // add proper space 2nd assignment
    for(k=1; k<totalsz; k++)
    {

        int flag  =0;
        int n = strlen(str[k]);
        strcpy(ar,str[k]);
        j = 0;
        int sepOn = 0;
        for(i=0; i<n; i++)
        {

            if(isSep(ar[i])==1)
            {
                if(ar[i]=='\'')
                {
                    if(sepOn)
                    {
                        sepOn = 0;
                        br[j++]  = ' ';
                        br[j++]  = ar[i];
                    }
                    else
                    {
                        br[j++]  = ar[i];
                        br[j++]  = ' ';
                        sepOn = 1;
                    }
                }
                else
                {
                    br[j++]  = ' ';
                    br[j++]  = ar[i];
                }
                br[j++]  = ' ';


            }
            else if(isOp(ar[i])==1)
            {
                if(ar[i+1]=='=')
                {
                    br[j++]  = ' ';
                    br[j++]  = ar[i];
                    br[j++]  = ar[i+1];
                    i++;
                    br[j++]  = ' ';
                }
                else
                {
                    br[j++]  = ' ';
                    br[j++]  = ar[i];
                    br[j++]  = ' ';
                }
                flag  =1;
            }
            else if(isDigit(ar[i])==1)
            {
                if(flag==0)
                {
                    flag = 1;
                    br[j++]  = ' ';
                }
                br[j++]  = ar[i];
            }
            else if(isPar(ar[i])==1)
            {
                br[j++]  = ' ';
                br[j++]  = ar[i];
                if(ar[i]!=')')
                    br[j++]  = ' ';
            }
            else if(isBrc(ar[i])==1)
            {
                br[j++]  = ' ';
                br[j++]  = ar[i];
                if(ar[i]!='}')
                    br[j++]  = ' ';
            }
            else
            {
                flag  =1;
                br[j++]  = ar[i];
            }
        }
        br[j-1]  = ' ';
        br[j] = '\0';

        strcpy(str[k],br);
    }



    //remove multiple whitespace 1st assignment

    for(k=1; k<totalsz; k++)
    {
        strcpy(ar,str[k]);
        br[0]  = '\0';
        j = 0;
        for(i=0; i<strlen(ar); i++)
        {
            if(ar[i]==' ')
            {
                br[j++]  = ' ';
                while(i<strlen(ar) && ar[i]==' ')
                    i++;
                i--;
            }
            else br[j++]  =ar[i];

        }
        br[j]  = '\0';
        strcpy(str[k],br);
    }


    //label the tokens assignment 2
    int fb = 0,sb = 0;
    int isIf = 0,semicolonIf=0;
    for(k=1; k<=totalsz; k++)
    {
        j = 0;
        int forloop = 0;
        int pt = 0;
        fprintf(fp2,"%d ",k);
        strcpy(br,str[k]);
        char pre[100] = {'-','1'};
        for(i=0; i<strlen(br); i++)
        {
            if(br[i]==' ')
            {

                ar[j++] = '\0';
                if(strlen(ar)==0)
                {
                    j  =0;
                    continue;
                }

                if(isSepa(ar)==1)
                {
                    fprintf(fp2,"sep %s ",ar);
                    if(strcmp(ar,";")==0)
                    {
                        semicolonIf++;
                        if(forloop==2 || forloop==3)
                            forloop++;
                        else if(forloop>=4)
                        {
                            fprintf(fp3,"Only two semicolon in for loop at line %d\n",k);
                        }
                        else if(strcmp(ar,pre)==0)
                        {
                            fprintf(fp3,"Duplicate token at line %d\n",k);
                        }
                    }
                    else if(strcmp(ar,pre)==0)
                    {
                        fprintf(fp3,"%Duplicate token at line %d\n",k);
                    }
                    strcpy(c[k][pt++],ar);

                }
                else if(isKey(ar)==1)
                {
                    fprintf(fp2,"kw %s ",ar);
                    if(strcmp(ar,"if")==0)
                    {
                        isIf  = 1;
                        semicolonIf = 0;
                    }
                    else if(strcmp(ar,"else")==0)
                    {
                        if(isIf==0 || semicolonIf!=1)
                        {
                            fprintf(fp3,"'else' without a previous 'if' at line %d\n",k);
                        }
                        else isIf  = 0;
                    }
                    else if(strcmp(ar,"for")==0)
                    {
                        forloop = 1;
                    }
                    if(strcmp(ar,pre)==0)
                    {
                        fprintf(fp3,"Duplicate token at line %d\n",k);
                    }
                    strcpy(c[k][pt++],ar);

                }
                else if(isId(ar)==1)
                {

                    fprintf(fp2,"id %s ",ar);
                    if(strcmp(ar,pre)==0)
                    {
                        fprintf(fp3,"Duplicate token at line %d\n",k);
                    }
                    strcpy(c[k][pt++],"id");
                    strcpy(c[k][pt++],ar);
                }
                else if(isOper(ar)==1)
                {
                    fprintf(fp2,"op %s ",ar);
                    strcpy(c[k][pt++],ar);
                }
                else if(isParen(ar)==1)
                {
                    fprintf(fp2,"par %s ",ar);
                    if(strcmp(ar,"(")==0)
                    {
                        fb++;
                        if(forloop==1)
                            forloop++;
                    }
                    else
                    {
                        if(forloop>0 && forloop<4)
                        {
                            fprintf(fp3,"Expected ‘;’ in for loop at line %d\n",k);
                        }
                        else if(fb==0)
                            fprintf(fp3,"Misplaced ‘)’ at line %d\n",k);
                        else
                        {
                            fb--;
                            if(forloop>0)
                                forloop = 0;
                        }
                    }
                    strcpy(c[k][pt++],ar);

                }
                else if(isBrace(ar)==1)
                {
                    fprintf(fp2,"brc %s ",ar);
                    if(strcmp(ar,"{")==0)
                        sb++;
                    else
                    {

                        if(sb==0)
                            fprintf(fp3,"Misplaced ‘}’ at line %d\n",k);
                        else sb--;
                    }
                    strcpy(c[k][pt++],ar);
                }
                else if(isNum(ar)==1)
                {
                    fprintf(fp2,"num %s ",ar);
                    strcpy(c[k][pt++],ar);
                }
                else
                {
                    fprintf(fp2,"unkn %s ",ar);
                    fprintf(fp3,"Undeclared/Unknown %s at line %d\n",ar,k);
                    strcpy(c[k][pt++],ar);
                }
                j= 0;
                strcpy(pre,ar);
            }
            else
            {
                ar[j++]  = br[i];
            }

        }
        fprintf(fp2,"\n");
        sz[k] =  pt;
    }
    if(sb>0)
        fprintf(fp3,"Expected ‘}’ at line %d\n",k-1);
    if(fb>0)
        fprintf(fp3,"Expected ‘)’ at line %d\n",k-1);



    //duplicate/no declaration assignment 3
    int it = 0;
    char * scope = "global";
    for(k=1; k<totalsz; k++)
    {
        for(i=0; i<sz[k]; i++)
        {
            if(strcmp(c[k][i],"id")==0)
            {
                if(strcmp(c[k][i+2],"(")==0)
                {
                    if(strcmp(c[k][i-1],"int")==0 || strcmp(c[k][i-1],"double")==0 || strcmp(c[k][i-1],"float")==0 || strcmp(c[k][i-1],"char")==0 || strcmp(c[k][i-1],"void")==0)
                    {
                        inde[it++]  = cur;
                        insert(cur++,c[k][i+1],"func",c[k][i-1],scope,"");
                        scope = c[k][i+1];
                        i+= 2;
                    }
                    else
                    {
                        int pq  = search(c[k][i+1],"func","global");
                        if(pq!=-1)
                            inde[it++] = pq;
                        else fprintf(fp3,"Expected declaration of function %s at line %d\n",c[k][i+1],k);
                        i+= 2;
                    }
                }
                else if(strcmp(c[k][i+2],"=")==0)
                {
                    if(strcmp(c[k][i-1],"int")==0 || strcmp(c[k][i-1],"double")==0 || strcmp(c[k][i-1],"float")==0 || strcmp(c[k][i-1],"char")==0 )
                    {
                        if(search(c[k][i+1],"var",scope)==-1)
                        {
                            inde[it++]  = cur;
                            insert(cur++,c[k][i+1],"var",c[k][i-1],scope,modify(c[k][i+3]));
                        }
                        else
                        {
                            fprintf(fp3,"ID %s at line %d already declared in %s scope\n",c[k][i+1],k,scope);
                        }
                    }
                    else
                    {
                        int pq = search(c[k][i+1],"var",scope);
                        if(pq==-1)
                        {
                            fprintf(fp3,"Expected declaration of %s at line %d\n",c[k][i+1],k);
                        }
                        else
                        {
                            update(pq,modify(c[k][i+3]));
                            inde[it++]  = pq;
                        }
                    }
                    i+=2;
                }
                else if(strcmp(c[k][i+2],";")==0 || strcmp(c[k][i+2],",")==0 || strcmp(c[k][i+2],")")==0 )
                {
                    if(strcmp(c[k][i-1],"int")==0 || strcmp(c[k][i-1],"double")==0 || strcmp(c[k][i-1],"float")==0 || strcmp(c[k][i-1],"char")==0 )
                    {
                        if(search(c[k][i+1],"var",scope)==-1)
                        {
                            inde[it++]  = cur;
                            insert(cur++,c[k][i+1],"var",c[k][i-1],scope,"");
                        }
                        else fprintf(fp3,"ID %s at line %d already declared in %s scope\n",c[k][i+1],k,scope);
                        i+= 2;
                    }
                    else
                    {
                        if(search(c[k][i+1],"var",scope)==-1)
                        {
                            fprintf(fp3,"Expected declaration of %s at line %d\n",c[k][i+1],k);
                        }
                        else inde[it++]  = search(c[k][i+1],"var",scope);
                        i+= 2;
                    }
                }
            }
            else if(strcmp(c[k][i],"}")==0)
            {
                scope = "global";
            }
        }
    }






}
