#include <stdio.h>
#include <string.h>
#include "symbol_table_header.h"

char intermediate_symbol_table[1000][50];
int intermediate_symbol_table_counter=0;

void print_file(FILE *p2)
{
    char c;
    while((c=fgetc(p2)) != EOF)printf("%c",  c);
}


void process_token(char *token)
{
    FILE *p1;
    p1 = fopen("identified_tokens.txt", "a");
    char first[20],second[30];
    char c;
    int i;
    for(i = 0; i < strlen(token); i++)
    {
        if(token[i]==' ')
            break;
        first[i] = token[i];
    }
    first[++i] = '\0';
    int j;
    for(j = 0; j < strlen(token); j++, i++)
    {
        second[j] = token[i];
    }
    second[++j] = '\0';
    if(!strcmp(first,"id"))
    {
        printf("[id %s] ", second);
        fputs("[id ",p1);
        fputs(second,p1);
        fputs("] ",p1);
        char str[50] = "id ";
        strcat(str, second);
        strcpy(intermediate_symbol_table[intermediate_symbol_table_counter++],str);
    }
    else
    {
        printf("[%s] ", second);
        fputs("[", p1);
        fputs(second, p1);
        fputs("] ", p1);
        strcpy(intermediate_symbol_table[intermediate_symbol_table_counter++],second);
    }

    fclose(p1);
}

void _read_each_tokens_from_file(FILE *p2)
{

    char c;
    char token[100];
    token[0] = '\0';
    char cToStr[2];
    cToStr[1] = '\0';
    while(c=fgetc(p2))
    {
        if(c=='[')
            continue;
        if(c==']')
            break;
        cToStr[0] = c;
        strcat(token,cToStr);
    }
    fgetc(p2);
    process_token(token);
}

void tokenizeSeparator()
{
    FILE *p1;

    char c;
    p1 = fopen("tokenized_file.txt", "r");

    if(!p1)printf("\nTokenized File can't be opened!");
    else
    {
        while((c=fgetc(p1)) != EOF)
        {
            _read_each_tokens_from_file(p1);
        }
    }

    fclose(p1);
}



int detect_variable_declaration(int i)
{
    if(!strcmp(intermediate_symbol_table[i],"float")
            || !strcmp(intermediate_symbol_table[i+2],"double")
            || !strcmp(intermediate_symbol_table[i+2],"int") )
    {
        if(!strcmp(intermediate_symbol_table[i+2],"=")){
            //var assignment and declaration
        }else if(!strcmp(intermediate_symbol_table[i+2],";")){
            //var declaration only
        }else if(!strcmp(intermediate_symbol_table[i+2],"(")){
            //function declaration;
        }

    }else if(!strcmp(intermediate_symbol_table[i+1],"="){
        //var assignment OR Function call which returns a value
    }

}

void detect_function_declaration()
{

}

void process_intermediate_symbol_table()
{
//    for(int i = 0 ; i < intermediate_symbol_table_counter ; i++){
//        puts(intermediate_symbol_table[i]);
//    }

    for(int i = 0 ; i < intermediate_symbol_table_counter ; i++)
    {
        int var_detection = detect_variable_declaration(i);
        if(var_detection==0)
        {
            detect_function_declaration();
        }

    }

}

int main()
{
    tokenizeSeparator();
    process_intermediate_symbol_table();
    return 0;
}
