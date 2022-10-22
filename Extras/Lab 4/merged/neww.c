#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "myheader.h"

void take_input_from_console(); // unchanged
void error_remove_comment_and_generate_stream(); //cannot merge
int error_get_number_for_file(int num, FILE *p); //new added
void error_add_number_in_the_file(); //new added
void error_perform_separate(); //can try to merge
int error_detect_identifier(char *word);//changed a bit
int error_detect_keyword(char *word);//changed a bit
int error_detect_separator(char *word);//changed a bit
void error_detect_word(char *word, int length);//changed a bit
void error_tokenizer();//changed
void findError();//new added
void error__read_each_tokens_from_file(FILE *p2); //changed
void error_process_token(char *token); // changed
void find_error(); //new added
void check_if_same(); //new added
void check_if_balanced();//new added
void check_if_else();//new added

FILE *error_identifier_detector;
int error_identifier_detector;
int error_tokenize_line_counter = 0;
char error_token_id[1000][50];
char error_token[1000][50];
int error_token_line_number[1000];
int error_token_line_number_tracker = 1;
int error_token_tracker=0;


int main ()
{
    take_input_from_console();
    error_remove_comment_and_generate_stream();
    remove_extra_spaces();
    error_perform_separate();
    error_tokenizer();
    generate_token_for_error();
    printf("\nTOKEN TABLE\n");
    for(int i = 0 ; i < error_token_tracker ; i++)
    {
        printf("%s %s %d\n", error_token_id[i], error_token[i], error_token_line_number[i] );
    }
    find_error();
    //error_add_number_in_the_file();
    return 0;
}

void find_error()
{
    check_if_same();
    check_if_balanced("(",")");
    check_if_balanced("{","}");
    check_if_else();
}

void check_if_else()
{
    for(int i = error_token_tracker-1 ; i >= 0; i--)
    {
        if(!strcmp(error_token[i],"else") && strcmp(error_token[i+1],"if"))
        {
            int found = 1;
            for(int j = i-1 ; j >= 0; j--)
            {
                if(!strcmp(error_token[j],"else"))
                {
                    if(!strcmp(error_token[j+1],"if")){}
                    else{found++;}

                }
                else if(!strcmp(error_token[j],"if"))
                {
                    if(!strcmp(error_token[j-1],"else")){

                    }else{
                        found--;
                        if(found==0)
                        {
                            break;
                        }
                    }

                }
                else if(!strcmp(error_token_id[j],"kw") && !strcmp(error_token_id[j+1],"id") && !strcmp(error_token[j+2],"(")  )
                {
                    break;
                }
            }
            if(found!=0)
            {
                printf("Misplaced else at line %d\n", error_token_line_number[i] );
            }

        }
    }
}

void check_if_balanced(char *opening, char *closing)
{

    //checking forward
    for(int i = 0 ; i < error_token_tracker; i++)
    {
        if(!strcmp(error_token[i],opening))
        {
            int found = 1;
            for(int j = i+1 ; j < error_token_tracker; j++)
            {
                if(!strcmp(error_token[j],opening))
                {
                    found++;
                }
                else if(!strcmp(error_token[j],closing))
                {
                    found--;
                    if(found==0)
                    {
                        break;
                    }
                }
                else if(!strcmp(error_token_id[j],"kw") && !strcmp(error_token_id[j+1],"id") && !strcmp(error_token[j+2],"(")  )
                {
                    break;
                }
            }
            if(found!=0)
            {
                printf("Misplaced %s at line %d\n", opening,error_token_line_number[i] );
            }
        }
    }
    //checking backward
    for(int i = error_token_tracker-1 ; i >= 0; i--)
    {
        if(!strcmp(error_token[i],closing))
        {
            int found = 1;
            for(int j = i-1 ; j >= 0; j--)
            {
                if(!strcmp(error_token[j],closing))
                {
                    found++;
                }
                else if(!strcmp(error_token[j],opening))
                {
                    found--;
                    if(found==0)
                    {
                        break;
                    }
                }
                else if(!strcmp(error_token_id[j],"kw") && !strcmp(error_token_id[j+1],"id") && !strcmp(error_token[j+2],"(")  )
                {
                    break;
                }
            }
            if(found!=0)
            {
                printf("Misplaced %s at line %d\n", closing,error_token_line_number[i] );
            }
        }
    }

}

void check_if_same()
{
    for(int i = 0 ; i < error_token_tracker-1 ; i++)
    {
        if(!strcmp(error_token_id[i],error_token_id[i+1]) && strcmp(error_token_id[i],"par")
                && strcmp(error_token_id[i],"brc") && strcmp(error_token[i],"else") )
        {
            if( i>2 && !strcmp(error_token[i-2],"for"))
            {

            }
            else
            {
                printf("Duplicate token at %s line %d\n", error_token[i], error_token_line_number[i]);
            }

        }
    }
}


void generate_token_for_error()
{
    FILE *p1;
    char c;
    printf("generate_token_for_error\n\n");
    p1 = fopen("tokenized_file.txt", "r");
    if(!p1)printf("\nTokenized File can't be opened!");
    else
    {
        while((c=fgetc(p1)) != EOF)
        {
            ungetc(c,p1);
            error__read_each_tokens_from_file(p1);
        }
    }
    fclose(p1);
}

void error__read_each_tokens_from_file(FILE *p2)
{
    char c;
    char token[100];
    token[0] = '\0';
    char cToStr[2];
    cToStr[1] = '\0';
    int space_counter = 0;
    while(c=fgetc(p2))
    {
        if(c=='\n')
        {
            error_tokenize_line_counter++;
            break;
        }
        else if(c==' ' && space_counter == 1)
        {
            space_counter=0;
            break;
        }
        else if(c==' ' && space_counter == 0)
        {
            space_counter++;
        }

        cToStr[0] = c;
        strcat(token,cToStr);
    }
    if(strlen(token)!=0)
    {
        printf("%s ", token);
        error_process_token(token);
    }
    else
    {
        error_token_line_number_tracker++;
    }

}

void error_process_token(char *token)
{
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

    strcpy(error_token_id[error_token_tracker],first);
    strcpy(error_token[error_token_tracker],second);
    error_token_line_number[error_token_tracker++] = error_token_line_number_tracker;
}


void error_tokenizer()
{
    char c;
    FILE *p2;
    p2=fopen("stream_separator_file.txt", "r");
    error_identifier_detector = fopen("tokenized_file.txt", "w");
    char reader[100];
    int readerCounter = 0;
    while((c=fgetc(p2)) != EOF)
    {
        if(c=='\n')
        {
            printf("\n");
            fputs("\n", error_identifier_detector);
        }
        else if(c==' ')
        {
            error_detect_word(reader,readerCounter);
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
    fclose(error_identifier_detector);

    printf("\n\n");

}

void error_detect_word(char *word, int length)
{

    char str[length];
    for(int i = 0 ; i < length; i++)
    {
        str[i] = word[i];
    }
    int keyword_detector, numeric_detector, separator_detector;
    keyword_detector = error_detect_keyword(str);

    if(keyword_detector==0)
    {
        numeric_detector = detect_numeric(str);
    }
    if(numeric_detector==0 && keyword_detector==0)
    {
        error_detect_identifier(str);

        // POSSIBLE ERROR, if identifier is found, it should not check separator detector

        separator_detector = error_detect_separator(str);
        if(error_identifier_detector==0 && separator_detector==0)
        {

            //CHANGES : CHANGED HERE
            printf("unkn ");
            fputs("unkn ", error_identifier_detector);

        }
    }


    if(str[0]!='\1') //handling SOH error
    {
        //CHANGES : CHANGED HERE
        printf("%s ", str);
        fputs(str, error_identifier_detector);
        fputs(" ", error_identifier_detector);
    }
}

int error_detect_separator(char *word)
{
    if(strlen(word)==1)
    {
        char c = word[0];
        //CHANGES : changed the print statements a bit
        if(c==',' || c ==';' || c==':' || c=='\'') //detected separator
        {
            printf("sep ");
            fputs("sep ", error_identifier_detector);
            return 1;
        }
        if(c=='(' || c==')' || c=='[' || c==']') //detected paranthesis
        {
            printf("par ");
            fputs("par ", error_identifier_detector);
            return 1;
        }
        if(c=='{' || c=='}') //detected bracket
        {
            printf("brc ");
            fputs("brc ", error_identifier_detector);
            return 1;
        }
        if(c=='+' || c=='-' || c=='*' || c =='/' || c=='=') //detected operator
        {
            printf("op ");
            fputs("op ", error_identifier_detector);
            return 1;
        }

        //CHANGES : ADDED THIS
        if(c=='<' || c=='>') //detected operator
        {
            printf("op ");
            fputs("op ", error_identifier_detector);
            return 1;
        }

    }
    else if(strlen(word)==2)
    {
        char c = word[0];
        char c2 = word[1];
        if( (c=='+' || c=='-' || c=='/' || c=='*' ||
                c=='=' || c=='<' || c=='>' || c=='!' || c=='%')
                && c2=='=' )
        {
            printf("op ");
            fputs("op ", error_identifier_detector);
            return 1;
        }

        //add logical operators code here
    }
    else
    {
        return 0;
    }
}


int error_detect_keyword(char *word)
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

        if(strlen(word) != strlen(keywords[i])) // checking if word size matches with keyword size
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

        if(flag ==1) //keyword match found
        {
             //CHANGES : changed here only
            printf("kw ");
            fputs("kw ", error_identifier_detector);
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
         //CHANGES : changed here only
        s=1;
        printf("num ");
        fputs("num ", error_identifier_detector);
    }
    return s;
}

int error_detect_identifier(char *word)
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

        //CHANGES : changed here only
        printf("id ");
        fputs("id ", error_identifier_detector);
        error_identifier_detector = 1;
    }
    else
    {
        error_identifier_detector = 0;
    }

    return s;
}



void error_perform_separate()
{
    FILE *p1, *p2;
    char c;
    p1 = fopen("removed_extra_spaces.txt", "r");
    p2 = fopen("stream_separator_file.txt", "w");

    if(!p1)printf("\nFile can't be opened!");
    else
    {
        char prev; // saving previous printed character
        int separator = 0; // this separator checks if the previous character is a separator
        // or not. Or else for consecutive separator, multiple spaces gets printed
        while((c=fgetc(p1))!=EOF)
        {

            //add spaces between separators

            //CHANGES : added this if condition
            if(prev=='\n' && (c=='{' || c=='}')){
                fputc(c, p2);
                fputc(' ', p2);
                separator = 1;
                prev = '\n';
                continue;
            }


            if(c=='(' || c==')' || c==',' || c ==';' || c=='{' || c=='}'
                    || c=='*' || c=='+' || c=='/' || c=='-' || c=='='|| c=='\''
                    || c==':' || c=='[' || c==']' || c=='%' || c=='<' || c=='>')
            {
                if(c=='=')
                {
                    if(prev=='+' || prev=='-' || prev=='/' || prev=='*' ||
                            prev=='=' || prev=='<' || prev=='>' || prev=='!' || prev=='%' )
                    {
                        //checking operator
                        fputc(c, p2);
                        fputc(' ', p2);
                        prev = ' ';
                        separator = 1;
                        continue;
                    }
                }
                if(prev!=' ' && separator == 0) //for operators, put space
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
                //for non separator words
                fputc(c,p2);
                prev = c;
                separator = 0;
            }

        }
    }

    fclose(p1);
    fclose(p2);

    printf("\n\n");
    p2=fopen("stream_separator_file.txt", "r");
    while((c=fgetc(p2))  !=  EOF)printf("%c",  c);
    printf("\n\n");
    fclose(p2);

}

void remove_extra_spaces()
{
    FILE *p1, *p2;

    char c,prev='z';
    p1 = fopen("error_remove_comment_and_generate_stream.txt", "r");
    p2 = fopen("removed_extra_spaces.txt", "w");

    int newLine=0;
    if(!p1)printf("\nFile can't be opened!");
    else
    {
        prev = 'a';
        while((c=fgetc(p1))!=EOF)
        {
            if(c==' ')
            {
                if(prev!=' ')
                {
                    fputc(c,p2);
                }
            }
            else
            {
                fputc(c,p2);
            }
            prev = c;
        }
    }

    fclose(p1);
    fclose(p2);

    printf("\n\n");
    p2=fopen("removed_extra_spaces.txt", "r");
    while((c=fgetc(p2))  !=  EOF)printf("%c",  c);
    printf("\n\n");
    fclose(p2);
}


void error_add_number_in_the_file()
{
    FILE *p1, *p2;
    char c;
    p1 = fopen("tokenized_file.txt", "r");
    p2 = fopen("addedNumberOnLines.txt", "w");
    int lineNumber = 0;
    if(!p1)printf("\nFile can't be opened!");
    else
    {
        error_get_number_for_file(++lineNumber,p2);
        while((c=fgetc(p1))!=EOF)
        {
            fputc(c,p2);
            if(c=='\n')
            {
                error_get_number_for_file(++lineNumber,p2);
            }
        }
    }

    fclose(p1);
    fclose(p2);

    p2=fopen("addedNumberOnLines.txt", "r");
    while((c=fgetc(p2)) != EOF)
        printf("%c", c);
    fclose(p2);

}


int error_get_number_for_file(int num, FILE *p)
{
    char converter;

    while(num!=0)
    {
        int lastDigit = num%10;
        num /= 10;
        push(lastDigit);
    }

    while(!isempty())
    {
        int data = pop();
        converter = (char) data-208;
        fputc(converter,p);
    }
    fputc(' ',p);
}



void error_remove_comment_and_generate_stream()
{
    FILE *p1, *p2;

    char c,prev='z';
    p1 = fopen("console_input_to_txt_file.txt", "r");
    p2 = fopen("error_remove_comment_and_generate_stream.txt", "w");

    int newLine=0;
    if(!p1)printf("\nFile can't be opened!  ");
    else
    {
        char prev;

        while((c=fgetc(p1))!=EOF)
        {

            if(c=='/')
            {
                char temp=fgetc(p1);
                if(temp=='/')
                {
                    while((c=fgetc(p1))!='\n')
                    {}  // remove // comment
                    fputc('\n',p2);
                }
                else if(temp=='*')
                {
                    char tempChar = c;
                    while(1)
                    {
                        if(tempChar=='*' && c == '/')
                        {
                            break;
                        }
                        tempChar = c;
                        c = fgetc(p1);
                        if(c=='\n')
                            fputc('\n',p2);
                    }
                }
                else
                {
                    ungetc(temp,p1);
                    fputc('/',p2);
                }
            }
            else
            {
                fputc(c,p2);
            }
            prev = c;
        }
    }

    fclose(p1);
    fclose(p2);

    printf("\n\n");
    p2=fopen("error_remove_comment_and_generate_stream.txt", "r");
    while((c=fgetc(p2))  !=  EOF)printf("%c",  c);
    fclose(p2);
    printf("\n\n");

}



void take_input_from_console()
{
    char ch[100][200];
    char c1;
    char temp[200];
    int i = 0;
    FILE *fp;
    fp = fopen("console_input_to_txt_file.txt", "w");
    int eof_tracker = 0;
    while(1)
    {
        gets(ch[i]);
        if(ch[i][0]=='\0')
        {
            eof_tracker++;
            if(eof_tracker==3) //user input terminated after 3 carriage return
            {
                break;
            }
        }
        else
        {
            eof_tracker = 0;
        }
        for(int j = 0 ; j < strlen(ch[i]); j++)
        {
            if(ch[i][j]!='\0') //represents end of a line
            {
                fputc(ch[i][j],fp);
            }
        }
        i++;
        fputc('\n',fp);

    }

    fclose(fp);

}


