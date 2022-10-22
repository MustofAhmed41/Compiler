#include <stdio.h>
#include <ctype.h>
#include <string.h>

int detect_numeric(char *lex);
void perform_separate();
void detect_word(char *word, int length);
int detect_keyword(char *word);
int detect_separator(char *word);
int detect_operator(char *word);
int detect_identifier(char *word);
int identifier_detector;

/* TODO */
/*
-MERGING WITH ASSIGNMENT 1
-have to fix operators, now it only works for 1 digit operators, make for 2 digit
*/


int main ()
{
    perform_separate();

//    char str[] = "100.01123";
//    printf("%d", num_rec(str));
    return 0;
}


void perform_separate()
{
    FILE *p1, *p2;
    char c;
    p1 = fopen("Untitled3.c", "r");
    p2 = fopen("read_write.txt", "w");

    if(!p1)printf("\nFile can't be opened!");
    else
    {
        char prev; // saving previous printed character
        int separator = 0; // this separator checks if the previous character is a separator
        // or not. Or else for consecutive separator, multiple spaces gets printed
        while((c=fgetc(p1))!=EOF)
        {

            //add spaces between separators
            if(c=='(' || c==')' || c==',' || c ==';' || c=='{' || c=='}'
            || c=='*' || c=='+' || c=='/' || c=='-' || c=='='|| c=='\''
            || c==':' || c=='[' || c==']' || c=='%' || c=='<' || c=='>'){
                if(c=='='){
                    if(prev=='+' || prev=='-' || prev=='/' || prev=='*' ||
                       prev=='=' || prev=='<' || prev=='>' || prev=='!' || prev=='%' ){
                            fputc(c, p2);
                            fputc(' ', p2);
                            prev = ' ';
                            separator = 1;
                            continue;
                       }
                }
                if(prev!=' ' && separator == 0)
                {
                    fputc(' ',p2);
                }
                fputc(c,p2);
                prev = c;
                c=fgetc(p1);
                if(c!=' ' && c!='+' && c!='-' && c!='/' && c!='*' && c!='<' && c!='>' && c!='=')
                {
                    fputc(' ',p2);
                    //prev = ' ';
                }
                ungetc(c,p1);
                separator = 1;
            }
            else
            {
                fputc(c,p2);
                prev = c;
                separator = 0;
            }

        }
    }

    fclose(p1);
    fclose(p2);

    p2=fopen("read_write.txt", "r");
    char reader[100];
    int readerCounter = 0;
    while((c=fgetc(p2)) != EOF)
    {
        if(c==' ')
        {
            detect_word(reader,readerCounter);
            readerCounter = 0;
        }
        else
        {
            reader[readerCounter] = c;
            readerCounter++;
        }
        //printf("%c", c);
    }
    fclose(p2);
}

void detect_word(char *word, int length)
{

    char str[length];
    for(int i = 0 ; i < length; i++)
    {
        str[i] = word[i];
    }
    int keyword_detector, numeric_detector, separator_detector;
    keyword_detector = detect_keyword(str);

    if(keyword_detector==0)
    {
        numeric_detector = detect_numeric(str);
    }
    if(numeric_detector==0 && keyword_detector==0){
        detect_identifier(str);
        separator_detector = detect_separator(str);
        if(identifier_detector==0 && separator_detector==0){
            printf("[unkn ");
        }
    }

    if(str[0]!='\1') //handling SOH error
        printf("%s] ", str);
}

int detect_separator(char *word){
    if(strlen(word)==1){
        char c = word[0];
        if(c==',' || c ==';' || c==':' || c=='\''){
            printf("[sep ");
            return 1;
        }
        if(c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']'){
            printf("[par ");
            return 1;
        }
        if(c=='+' || c=='-' || c=='*' || c =='/' || c=='='){
            printf("[op ");
            return 1;
        }
    }
    else if(strlen(word)==2){
        char c = word[0];
        char c2 = word[1];
        if( (c=='+' || c=='-' || c=='/' || c=='*' ||
             c=='=' || c=='<' || c=='>' || c=='!' || c=='%')
           && c2=='=' ){
            printf("[op ");
            return 1;
        }
    }else{
        return 0;
    }
}


int detect_keyword(char *word)
{
    char keywords[32][15] =
    {
        "auto", "break", "case", "char", "continue", "const", "default",
        "do", "double", "else", "enum", "extern", "if", "float",
        "for", "goto", "int", "long", "return", "register", "short",
        "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };
    int flag;
    for(int i = 0; i < 32; i++)
    {

        if(strlen(word) != strlen(keywords[i]))
        {
            continue;
        }
        flag = 1;
        for(int j = 0 ; j < strlen(keywords[i]) ; j++)
        {
            if(word[j]!=keywords[i][j])
            {
                flag = 0;
                break;
            }
        }

        if(flag ==1)
        {
            printf("[kw ");
            return 1;
        }
    }
    return 0;
}


int detect_numeric(char *lex)
{
    int i, l, s;
    i=0;
    if(isdigit(lex[i]))
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
    {
        for(; i<l; i++)
        {
            if(isdigit(lex[i]))
                s=1;
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
    }

    if(s==2)
    {
        if(isdigit(lex[i]))
        {
            s=3;
            i++;
        }
        else
            s=0;
    }

    if(s==3)
    {
        for(; i<l; i++)
        {
            if(isdigit(lex[i]))
                s=3;
            else
            {
                s=0;
                break;
            }
        }
    }

    if(s==3 || s==1)
    {
        s=1;
        printf("[num ");
    }
    return s;
}

int detect_identifier(char *word){
int i, l, s;
    i=0;
    if(isalpha(word[i]) || word[i]=='_')
    {
        s=1;
        i++;
    }
    else
    {
        s=0;
    }

    l=strlen(word);

    if(s==1)
    {
        for(; i<l; i++)
        {
            if(isdigit(word[i]) || isalpha(word[i]) || word[i]=='_')
                s=1;
            else
            {
                s=0;
                break;
            }
        }
    }
    if(s==1){
        printf("[id ");
        identifier_detector = 1;
    }else{
        identifier_detector = 0;
    }

    return s;
}
