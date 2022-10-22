#include <stdio.h>
#include <ctype.h>
#include <string.h>

//isdigit(isdigit[i]) || isalpha(word[i]) || word[i]=='_'

int main ()
{
    char inp[100];
    gets(inp);
    int val = detect_pattern(inp);
    if(val == 4 || val == 5){
        printf("Correct");
    }else{
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
    if(isdigit(word[i])){
        s = 1;
    }else if(isalpha(word[i])){
        s = 2;
    }
    else{
        s = -1;
    }
    i++;

    if(s==1){
        for(;i<l;i++){
            if(isdigit(word[i])){
                s = 1;
            }else if(isalpha(word[i])){
                s = 2;
                i++;
                break;
            }else{
                s = -1;
                i++;
                break;
            }
        }
    }

    if(s == 2){
        if(word[i]=='_'){
            s = 3;
        }
        else{
            s = -1;
        }
        i++;
    }

    if(s==3){
        if(isdigit(word[i])){
            s = 4;
        }else{
            s = -1;
        }
        i++;
    }

    if(s==4){
        for(;i<l;i++){
            if(isdigit(word[i])){
                s = 5;
            }else{
                s = -1;
                break;
            }
        }
    }

    return s;
}


/*

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
        fputs("[num ", final_output_tokenized);
    }
    return s;
}

int detect_identifier(char *word)
{
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
    if(s==1)
    {
        printf("[id ");
        fputs("[id ", final_output_tokenized);
        identifier_detector = 1;
    }
    else
    {
        identifier_detector = 0;
    }

    return s;
}


*/
